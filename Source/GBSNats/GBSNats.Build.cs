using System.IO;
using System;

namespace UnrealBuildTool.Rules
{

  public class GBSNats : ModuleRules
  {
    public GBSNats(ReadOnlyTargetRules Target) : base(Target)
    {

      //PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
      //PrecompileForTargets = PrecompileTargetsType.Any;

      PrivateIncludePaths.AddRange(

          new string[] {
          "GBSNats/Private",
          "../ThirdParty/nats.c/src"
            // ... add other private include paths required here ...
          });

      PublicDependencyModuleNames.AddRange(

        new string[]
        {
          "Core",
          "CoreUObject",
          "Engine",
          "Json",
          "Projects" // Required by IPluginManager etc (used to get plugin information)
					// ... add other public dependencies that you statically link with here ...
				});

      // Only build Nats if the target platform is Unix
      if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
      {
        Definitions.Add("USE_NATS");
        BuildNats(Target);
      }
    }



    private string ModulePath
    {
      get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(ModulePath,
                                            "../../ThirdParty/"));
      }
    }

    private string CMakeProgram
    {
      get
      {
        return "~/deps/cmake-install/bin/cmake";
      }
    }

    private string CreateCMakeBuildCommand(string buildDirectory,
                                           string buildType)
    {
      // YourGame/Plugins/GBSNats/Source/GBSNats
      var currentDir = ModulePath;
      var rootDirectory = Path.Combine(currentDir,
                                       "..", "..", "..", "..");
      var installPath = Path.Combine(ThirdPartyPath, "generated");
      var sourceDir = Path.Combine(ThirdPartyPath, "nats.c");

      var arguments = " -G \"Unix Makefiles\"" +
                      " -S " + sourceDir +
                      " -B " + buildDirectory +
                      " -DCMAKE_BUILD_TYPE=" + buildType +
                      " -DCMAKE_INSTALL_PREFIX=" + installPath;

      return CMakeProgram + arguments;
    }

    private string CreateCMakeInstallCommand(string buildDirectory,
                                             string buildType)
    {
      return CMakeProgram + " --build " + buildDirectory +
             " --target install --config " + buildType;
    }

    private bool BuildNats(ReadOnlyTargetRules Target)
    {
      const string buildType = "Release";

      var buildDirectory = "nats-build-" + buildType;
      var buildPath = Path.Combine(ThirdPartyPath,
                                   "generated",
                                   buildDirectory);

      var configureCommand = CreateCMakeBuildCommand(buildPath,
                                                     buildType);
      var configureCode = ExecuteCommandSync(configureCommand);
      Console.WriteLine("Configure command: " + configureCommand);

      if (configureCode != 0)
      {
        Console.WriteLine(
            "\nCannot configure CMake project. Exited with code: "
            + configureCode);

        //return false;
      }

      var installCommand = CreateCMakeInstallCommand(buildPath,
                                                     buildType);
      Console.WriteLine("Install command: " + installCommand);

      var buildCode = ExecuteCommandSync(installCommand);
      if (buildCode != 0)
      {
        Console.WriteLine("Cannot build project. Exited with code: " + buildCode);
        //return false;
      }
      return true;
    }

    public int ExecuteCommandSync(object command)
    {
      try
      {
        // create the ProcessStartInfo using "cmd" as the program to be run,
        // and "/c " as the parameters.
        // Incidentally, /c tells cmd that we want it to execute the command that follows,
        // and then exit.
        System.Diagnostics.ProcessStartInfo procStartInfo =
            new System.Diagnostics.ProcessStartInfo("cmd", "/c " + command);

        // The following commands are needed to redirect the standard output.
        // This means that it will be redirected to the Process.StandardOutput StreamReader.
        procStartInfo.RedirectStandardOutput = true;
        procStartInfo.UseShellExecute = false;
        // Do not create the black window.
        procStartInfo.CreateNoWindow = true;
        // Now we create a process, assign its ProcessStartInfo and start it
        System.Diagnostics.Process proc = new System.Diagnostics.Process();
        proc.StartInfo = procStartInfo;
        proc.Start();
        // Get the output into a string
        string result = proc.StandardOutput.ReadToEnd();
        // Display the command output.
        Console.WriteLine(result);
        proc.WaitForExit();
        return proc.ExitCode;
      }
      catch (Exception objException)
      {
        // Log the exception
      }
      return 1;
    }

  }
}

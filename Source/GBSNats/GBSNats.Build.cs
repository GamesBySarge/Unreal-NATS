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
          "../ThirdParty/nats/Binaries/include"
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
        BuildNats(Target);
        Definitions.Add("USE_NATS");
        PublicIncludePaths.Add(NatsIncludePath);
        PublicAdditionalLibraries.Add(NatsLibraryPath + "/libnats_static.a");
        PublicAdditionalLibraries.Add("/usr/lib/x86_64-linux-gnu/libprotobuf-c.a");
      }
    }

    private bool BuildNats(ReadOnlyTargetRules Target)
    {
      Console.WriteLine("Executing " + NatsBuildScript);

      var buildCode = ExecuteCommandSync(NatsBuildScript);

      if (buildCode != 0)
      {
        Console.WriteLine(
            "\nCannot configure CMake project. Exited with code: "
            + buildCode);
        return false;
      }

      return true;
    }

    public int ExecuteCommandSync(string command)
    {
      try
      {
        System.Diagnostics.ProcessStartInfo procStartInfo =
            new System.Diagnostics.ProcessStartInfo(command);
            // For Windows, it should be the following
            // new System.Diagnostics.ProcessStartInfo("cmd", "/c " + command);

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

    private string NatsPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(ThirdPartyPath, "nats"));
      }
    }
    
    private string NatsBuildScript
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsPath, "BUILD.GBS.sh"));
      }
    }

    private string NatsInstallPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsPath, "Binaries"));
      }
    }

    private string NatsIncludePath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsInstallPath, "include"));
      }
    }

    private string NatsLibraryPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsInstallPath, "lib"));
      }
    }


  }
}

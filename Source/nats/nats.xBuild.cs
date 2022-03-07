using System;
using System.IO;

namespace UnrealBuildTool.Rules
{

  public class nats : ModuleRules
  {

    public nats(ReadOnlyTargetRules Target) : base(Target)
    {

      Type = ModuleType.External;

      if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
      {
        BuildNats(Target);

        // PrivateDependencyModuleNames.Add("SSL");
      }
	  else
	  {
        BuildNats(Target);
	  }
    }

    private string ThirdPartyPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(ModulePath,
                                            "..", "..", "ThirdParty"));
      }
    }

    private string ModulePath
    {
      get { return ModuleDirectory; }
    }

    private string NatsPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(ThirdPartyPath, "nats"));
      }
    }

    private string BuildPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsPath, "Intermediate"));
      }
    }

    private string BuildScript
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsPath, "BUILD.GBS.sh"));
      }
    }

    private string EnvFileName
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsPath, "ENV.GBS.sh"));
      }
    }

    private string InstallPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(NatsPath, "Binaries"));
      }
    }

    private string IncludePath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(InstallPath, "include"));
      }
    }

    private string LibraryPath
    {
      get
      {
        return Path.GetFullPath(Path.Combine(InstallPath, "lib"));
      }
    }


  }

}

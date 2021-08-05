using System.IO;

namespace UnrealBuildTool.Rules
{
	public class Nats : ModuleRules
	{
		public Nats(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
			PrecompileForTargets = PrecompileTargetsType.Any;

			PrivateIncludePaths.AddRange(
				new string[] {
					"Nats/Private",
          "../ThirdParty/nats/nats.c/src"
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
		}
	}
}

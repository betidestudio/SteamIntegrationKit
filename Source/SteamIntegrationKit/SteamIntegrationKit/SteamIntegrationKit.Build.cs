// Copyright (c) 2024 Betide Studio. All Rights Reserved.

using System;
using UnrealBuildTool;

public class SteamIntegrationKit : ModuleRules
{
	public SteamIntegrationKit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		bool bUseEngineSteam = false;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"OnlineSubsystem",
				"OnlineSubsystemSteam",
				"OnlineSubsystemUtils",
				"Networking"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"DeveloperSettings",
				"Projects",
				"HTTP",
				"Json",
				"JsonUtilities"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"UnrealEd",
					"ToolMenus",
					"EditorFramework"
				}
			);
		}

		if (bUseEngineSteam)
		{
			PublicDefinitions.Add("WITH_ENGINE_STEAM=1");
			PublicDefinitions.Add("WITH_STEAMKIT=1");
			AddEngineThirdPartyPrivateStaticDependencies(Target, "Steamworks");
		}
		else
		{
			PublicDefinitions.Add("WITH_ENGINE_STEAM=0");
			PublicDependencyModuleNames.Add("SteamSdk");
		}
	}
}

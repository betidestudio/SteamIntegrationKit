// Copyright (c) 2024 Betide Studio. All Rights Reserved.

using System;
using UnrealBuildTool;

public class SteamIntegrationKit : ModuleRules
{
	public SteamIntegrationKit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//Always change this to true if you want to use the engine steam subsystem which you would need normally for using the Github version of the plugin
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
				"CoreOnline",
				"OnlineSubsystem",
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
				"JsonUtilities",
				"OnlineSubsystemSteam",
				"AudioExtensions",
				"AudioMixer"
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
			if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.Mac)
			{
				Console.WriteLine("SteamIntegrationKit: Game build, enabling ONLINESUBSYSTEMSTEAM_PACKAGE");
				PublicDefinitions.Add("ONLINESUBSYSTEMSTEAM_PACKAGE=1");
				AddEngineThirdPartyPrivateStaticDependencies(Target, "Steamworks");
			}
			else
			{
				Console.WriteLine("SteamIntegrationKit: Editor build, disabling ONLINESUBSYSTEMSTEAM_PACKAGE");
				PublicDefinitions.Add("ONLINESUBSYSTEMSTEAM_PACKAGE=0");
			}
		}
		else
		{
			PublicDefinitions.Add("ONLINESUBSYSTEMSTEAM_PACKAGE=1");
			PublicDefinitions.Add("WITH_ENGINE_STEAM=0");
			PublicDependencyModuleNames.Add("SteamSdk");
		}
	}
}

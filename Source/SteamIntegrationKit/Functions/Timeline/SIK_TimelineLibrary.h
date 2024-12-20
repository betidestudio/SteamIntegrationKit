// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_TimelineLibrary.generated.h"

UENUM(BlueprintType)
enum ESIK_TimelineGameMode
{
	ESIK_TimelineGameMode_Invalid = 0 UMETA(DisplayName = "Invalid"),
	//The player is fully loaded into the game and playing.
	ESIK_TimelineGameMode_Playing = 1 UMETA(DisplayName = "Playing"),
	//The player is in a multiplayer lobby.
	ESIK_TimelineGameMode_Staging = 2 UMETA(DisplayName = "Staging"),
	//The player is in the game's main menu or a pause menu.
	ESIK_TimelineGameMode_Menus = 3 UMETA(DisplayName = "Menus"),
	//The player is waiting for a loading screen.
	ESIK_TimelineGameMode_LoadingScreen = 4 UMETA(DisplayName = "Loading Screen"),
};

UENUM(BlueprintType)
enum ESIK_TimelineEventClipPriority
{
	ESIK_TimelineEventClipPriority_Invalid = 0 UMETA(DisplayName = "Invalid"),
	//This event is not appropriate as a clip.
	ESIK_TimelineEventClipPriority_None = 1 UMETA(DisplayName = "None"),
	//The user may want to make a clip around this event.
	ESIK_TimelineEventClipPriority_Standard = 2 UMETA(DisplayName = "Standard"),
	//The player will be likely to want a clip around event, and those clips should be promoted more prominently than clips with the k_ETimelineEventClipPriority_Standard priority.
	ESIK_TimelineEventClipPriority_Featured = 3 UMETA(DisplayName = "Featured"),
};

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_TimelineLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	Sets a description (B) for the current game state in the timeline. These help the user to find specific
	moments in the timeline when saving clips. Setting a new state description replaces any previous
	description.

	Examples could include:
	Where the user is in the world in a single player game
	Which round is happening in a multiplayer game
	The current score for a sports game
	@param pchDescription A localized string in the language returned by SteamUtils()->GetSteamUILanguage()
	@param flTimeDelta The time offset in seconds to apply to this state change. Negative times indicate an event that happened in the past.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Timeline")
	static void SetTimelineStateDescription(FString pchDescription, float flTimeDelta);

	//Clears the previous set game state in the timeline.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Timeline")
	static void ClearTimelineStateDescription(float flTimeDelta);

	/*
	*Use this to mark an event (A) on the Timeline. The event can be instantaneous or take some amount of time to complete, depending on the value passed in flDurationSeconds.

	Examples could include:
	 *a boss battle
	 *a cut scene
	 *a large team fight
	 *picking up a new weapon or ammo
	 *scoring a goal

	The game can nominate an event as being suitable for a clip by passing k_ETimelineEventClipPriority_Standard or k_ETimelineEventClipPriority_Featured to ePossibleClip. Players can make clips of their own at any point, but this lets the game suggest some options to Steam to make that process easier for players.
	 */
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Timeline")
	static void AddTimelineEvent(FString pchIcon, FString pchTitle, FString pchDescription, int32 unPriority, float flStartOffsetSeconds, float flDurationSecondsm, TEnumAsByte<ESIK_TimelineEventClipPriority> ePossibleClip);

	//Changes the color of the timeline bar (C). See ETimelineGameMode for how to use each value.
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Timeline")
	static void SetTimelineGameMode(TEnumAsByte<ESIK_TimelineGameMode> eMode);
};

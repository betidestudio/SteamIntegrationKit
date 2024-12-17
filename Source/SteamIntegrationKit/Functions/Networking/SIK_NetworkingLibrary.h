// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_NetworkingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_NetworkingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool AcceptP2PSessionWithUser(FSIK_SteamId SteamIDRemote);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool AllowP2PPacketRelay(bool Allow);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool CloseP2PChannelWithUser(FSIK_SteamId SteamIDRemote, int32 Channel);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool CloseP2PSessionWithUser(FSIK_SteamId SteamIDRemote);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool GetP2PSessionState(FSIK_SteamId SteamIDRemote, FSIK_P2PSessionState& OutP2PSessionState);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool IsP2PPacketAvailable(int32& MsgSize, int32 Channel);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool ReadP2PPacket(TArray<uint8>& OutMsg, int32 MsgSize, FSIK_SteamId& OutSteamIDRemote, int32 Channel);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Networking")
	static bool SendP2PPacket(FSIK_SteamId SteamIDRemote, const TArray<uint8>& Msg, int32 Channel, TEnumAsByte<ESIK_P2PSend> SendType);

};

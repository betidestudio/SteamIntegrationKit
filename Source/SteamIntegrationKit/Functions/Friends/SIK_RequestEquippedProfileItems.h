// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_FriendsLibrary.h"
#include "SIK_SharedFile.h"
#include "SIK_RequestEquippedProfileItems.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FSIK_OnRequestEquippedProfileItems, const TEnumAsByte<ESIK_Result>&, Result, const FSIK_SteamId&, bHasAnimatedAvatar, bool, bHasAvatarFrame, bool, bHasProfileModifier, bool, bHasProfileBackground, bool, bHasMiniProfileBackground);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RequestEquippedProfileItems : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, DisplayName="Request Equipped Profile Items",meta = (BlueprintInternalUseOnly = "true",Keywords="RequestEquippedProfileItems"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_RequestEquippedProfileItems* RequestEquippedProfileItems(const FSIK_SteamId& SteamId);

	UPROPERTY(BlueprintAssignable)
	FSIK_OnRequestEquippedProfileItems OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSIK_OnRequestEquippedProfileItems OnFailure;
	
private:
	FSIK_SteamId m_SteamId;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	SteamAPICall_t m_CallbackHandle;
#if !WITH_ENGINE_STEAM
	CCallResult<USIK_RequestEquippedProfileItems, EquippedProfileItems_t> m_Callback;
	void OnRequestEquippedProfileItems(EquippedProfileItems_t* EquippedProfileItemsResponse, bool bIOFailure);
#endif
#endif
};

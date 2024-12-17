// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SIK_SharedFile.h"
#include "SIK_InventorySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSteamInventoryDefinitionUpdateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSteamInventoryEligiblePromoItemDefIDsDelegate, TEnumAsByte<ESIK_Result>, Result, FSIK_SteamId, SteamID, int32, ItemDefs, bool, CachedData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamInventoryFullUpdateDelegate, FSIK_SteamInventoryResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamInventoryResultReadyDelegate, FSIK_SteamInventoryResult, Result, TEnumAsByte<ESIK_Result>, ResultType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSteamInventoryStartPurchaseResultDelegate, TEnumAsByte<ESIK_Result>, Result, int64, OrderID, int64, TransID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamInventoryRequestPricesResultDelegate, TEnumAsByte<ESIK_Result>, Result, FString, Currency);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_InventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USIK_InventorySubsystem();
	~USIK_InventorySubsystem();
	//This callback is triggered whenever item definitions have been updated, which could be in response to LoadItemDefinitions or any time new item definitions are available (eg, from the dynamic addition of new item types while players are still in-game).
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Inventory || Callbacks")
	FSteamInventoryDefinitionUpdateDelegate OnSteamInventoryDefinitionUpdate;

	//Returned when you have requested the list of "eligible" promo items that can be manually granted to the given user. These are promo items of type "manual" that won't be granted automatically. An example usage of this is an item that becomes available every week.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Inventory || Callbacks")
	FSteamInventoryEligiblePromoItemDefIDsDelegate OnSteamInventoryEligiblePromoItemDefIDs;

	/*
	Triggered when GetAllItems successfully returns a result which is newer / fresher than the last known result. (It will not trigger if the inventory hasn't changed, or if results from two overlapping calls are reversed in flight and the earlier result is already known to be stale/out-of-date.)
	
	The regular SteamInventoryResultReady_t callback will still be triggered immediately afterwards; this is an additional notification for your convenience.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Inventory || Callbacks")
	FSteamInventoryFullUpdateDelegate OnSteamInventoryFullUpdate;

	//This is fired whenever an inventory result transitions from k_EResultPending to any other completed state, see GetResultStatus for the complete list of states. There will always be exactly one callback per handle.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Inventory || Callbacks")
	FSteamInventoryResultReadyDelegate OnSteamInventoryResultReady;

	//Returned after StartPurchase is called.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Inventory || Callbacks")
	FSteamInventoryStartPurchaseResultDelegate OnSteamInventoryStartPurchaseResult;

	//Returned after RequestPrices is called.
	UPROPERTY(BlueprintAssignable, Category = "Steam Integration Kit || Inventory || Callbacks")
	FSteamInventoryRequestPricesResultDelegate OnSteamInventoryRequestPricesResult;

private:
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	STEAM_CALLBACK_MANUAL(USIK_InventorySubsystem, OnSteamInventoryDefinitionUpdateCallback, SteamInventoryDefinitionUpdate_t, m_CallbackSteamInventoryDefinitionUpdate);
	STEAM_CALLBACK_MANUAL(USIK_InventorySubsystem, OnSteamInventoryEligiblePromoItemDefIDsCallback, SteamInventoryEligiblePromoItemDefIDs_t, m_CallbackSteamInventoryEligiblePromoItemDefIDs);
	STEAM_CALLBACK_MANUAL(USIK_InventorySubsystem, OnSteamInventoryFullUpdateCallback, SteamInventoryFullUpdate_t, m_CallbackSteamInventoryFullUpdate);
	STEAM_CALLBACK_MANUAL(USIK_InventorySubsystem, OnSteamInventoryResultReadyCallback, SteamInventoryResultReady_t, m_CallbackSteamInventoryResultReady);
	STEAM_CALLBACK_MANUAL(USIK_InventorySubsystem, OnSteamInventoryStartPurchaseResultCallback, SteamInventoryStartPurchaseResult_t, m_CallbackSteamInventoryStartPurchaseResult);
	STEAM_CALLBACK_MANUAL(USIK_InventorySubsystem, OnSteamInventoryRequestPricesResultCallback, SteamInventoryRequestPricesResult_t, m_CallbackSteamInventoryRequestPricesResult);
#endif	
};

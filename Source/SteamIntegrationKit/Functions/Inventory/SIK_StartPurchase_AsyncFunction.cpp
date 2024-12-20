// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_StartPurchase_AsyncFunction.h"

#include "Async/Async.h"

USIK_StartPurchase_AsyncFunction* USIK_StartPurchase_AsyncFunction::StartPurchase(TArray<FSIK_SteamItemDef> Items,
                                                                                  TArray<int32> Quantity)
{
	USIK_StartPurchase_AsyncFunction* Node = NewObject<USIK_StartPurchase_AsyncFunction>();
	Node->Items = Items;
	Node->Quantity = Quantity;
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_StartPurchase_AsyncFunction::OnStartPurchaseResult(SteamInventoryStartPurchaseResult_t* SteamInventoryStartPurchaseResult, bool bIOFailure)
{
	auto *RefData = SteamInventoryStartPurchaseResult;
	AsyncTask(ENamedThreads::GameThread, [this, RefData, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0);
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(RefData->m_result);
			OnSuccess.Broadcast(Result, RefData->m_ulOrderID, RefData->m_ulTransID);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_StartPurchase_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	SteamItemDef_t* ItemDefs = new SteamItemDef_t[Items.Num()];
	uint32* Quantities = new uint32[Items.Num()];
	for(int i = 0; i < Items.Num(); i++)
	{
		ItemDefs[i] = Items[i].GetSteamItemDef();
		Quantities[i] = Quantity[i];
	}
	CallbackHandle = SteamInventory()->StartPurchase(ItemDefs, Quantities, Items.Num());
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0);
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallResult.Set(CallbackHandle, this, &USIK_StartPurchase_AsyncFunction::OnStartPurchaseResult);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail, 0, 0);
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestPrices_AsyncFunction.h"

#include "Async/Async.h"

USIK_RequestPrices_AsyncFunction* USIK_RequestPrices_AsyncFunction::RequestPrices()
{
	USIK_RequestPrices_AsyncFunction* Node = NewObject<USIK_RequestPrices_AsyncFunction>();
	return Node;
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestPrices_AsyncFunction::OnPricesReceived(
	SteamInventoryRequestPricesResult_t* SteamInventoryRequestPricesResult, bool bIOFailure)
{
	auto *RefData = SteamInventoryRequestPricesResult;
	AsyncTask(ENamedThreads::GameThread, [this, RefData, bIOFailure]()
	{
		if(bIOFailure)
		{
			OnFailure.Broadcast(ESIK_Result::ResultFail, TEXT(""));
		}
		else
		{
			TEnumAsByte<ESIK_Result> Result = static_cast<ESIK_Result>(RefData->m_result);
			OnSuccess.Broadcast(Result, RefData->m_rgchCurrency);
		}
	});
	SetReadyToDestroy();
	MarkAsGarbage();
}
#endif

void USIK_RequestPrices_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, TEXT(""));
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallbackHandle = SteamInventory()->RequestPrices();
	if(CallbackHandle == k_uAPICallInvalid)
	{
		OnFailure.Broadcast(ESIK_Result::ResultFail, TEXT(""));
		SetReadyToDestroy();
		MarkAsGarbage();
		return;
	}
	CallResult.Set(CallbackHandle, this, &USIK_RequestPrices_AsyncFunction::OnPricesReceived);
#else
	OnFailure.Broadcast(ESIK_Result::ResultFail, TEXT(""));
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

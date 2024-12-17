// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_InventorySubsystem.h"

#include "Async/Async.h"

USIK_InventorySubsystem::USIK_InventorySubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackSteamInventoryDefinitionUpdate.Register(this, &USIK_InventorySubsystem::OnSteamInventoryDefinitionUpdateCallback);
	m_CallbackSteamInventoryEligiblePromoItemDefIDs.Register(this, &USIK_InventorySubsystem::OnSteamInventoryEligiblePromoItemDefIDsCallback);
	m_CallbackSteamInventoryFullUpdate.Register(this, &USIK_InventorySubsystem::OnSteamInventoryFullUpdateCallback);
	m_CallbackSteamInventoryResultReady.Register(this, &USIK_InventorySubsystem::OnSteamInventoryResultReadyCallback);
	m_CallbackSteamInventoryStartPurchaseResult.Register(this, &USIK_InventorySubsystem::OnSteamInventoryStartPurchaseResultCallback);
	m_CallbackSteamInventoryRequestPricesResult.Register(this, &USIK_InventorySubsystem::OnSteamInventoryRequestPricesResultCallback);

 	if(IsRunningDedicatedServer())
 	{
	m_CallbackSteamInventoryDefinitionUpdate.SetGameserverFlag();
	m_CallbackSteamInventoryEligiblePromoItemDefIDs.SetGameserverFlag();
	m_CallbackSteamInventoryFullUpdate.SetGameserverFlag();
	m_CallbackSteamInventoryResultReady.SetGameserverFlag();
	m_CallbackSteamInventoryStartPurchaseResult.SetGameserverFlag();
	m_CallbackSteamInventoryRequestPricesResult.SetGameserverFlag();
}
#endif
}

USIK_InventorySubsystem::~USIK_InventorySubsystem()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	m_CallbackSteamInventoryDefinitionUpdate.Unregister();
	m_CallbackSteamInventoryEligiblePromoItemDefIDs.Unregister();
	m_CallbackSteamInventoryFullUpdate.Unregister();
	m_CallbackSteamInventoryResultReady.Unregister();
	m_CallbackSteamInventoryStartPurchaseResult.Unregister();
	m_CallbackSteamInventoryRequestPricesResult.Unregister();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_InventorySubsystem::OnSteamInventoryDefinitionUpdateCallback(SteamInventoryDefinitionUpdate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSteamInventoryDefinitionUpdate.Broadcast();
	});
}

void USIK_InventorySubsystem::OnSteamInventoryEligiblePromoItemDefIDsCallback(SteamInventoryEligiblePromoItemDefIDs_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> result = static_cast<ESIK_Result>(Param.m_result);
		OnSteamInventoryEligiblePromoItemDefIDs.Broadcast(result, Param.m_steamID.ConvertToUint64(), Param.m_numEligiblePromoItemDefs, Param.m_bCachedData);
	});
}

void USIK_InventorySubsystem::OnSteamInventoryFullUpdateCallback(SteamInventoryFullUpdate_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		OnSteamInventoryFullUpdate.Broadcast(Param.m_handle);
	});
}

void USIK_InventorySubsystem::OnSteamInventoryResultReadyCallback(SteamInventoryResultReady_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> resultType = static_cast<ESIK_Result>(Param.m_result);
		OnSteamInventoryResultReady.Broadcast(Param.m_handle, resultType);
	});
}

void USIK_InventorySubsystem::OnSteamInventoryStartPurchaseResultCallback(SteamInventoryStartPurchaseResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> result = static_cast<ESIK_Result>(Param.m_result);
		OnSteamInventoryStartPurchaseResult.Broadcast(result, Param.m_ulOrderID, Param.m_ulTransID);
	});
}

void USIK_InventorySubsystem::OnSteamInventoryRequestPricesResultCallback(SteamInventoryRequestPricesResult_t* pParam)
{
	auto Param = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Param]()
	{
		TEnumAsByte<ESIK_Result> result = static_cast<ESIK_Result>(Param.m_result);
		OnSteamInventoryRequestPricesResult.Broadcast(result, Param.m_rgchCurrency);
	});
}
#endif
// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_InventoryLibrary.h"

bool USIK_InventoryLibrary::AddPromoItem(FSIK_SteamInventoryResult& InventoryResult, FSIK_SteamItemDef ItemDef)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		UE_LOG(LogTemp, Error, TEXT("SteamInventory() is null"));
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->AddPromoItem(&ResultInventory, ItemDef.GetSteamItemDef());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::AddPromoItems(FSIK_SteamInventoryResult& InventoryResult,
	const TArray<FSIK_SteamItemDef>& ItemDefs)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		UE_LOG(LogTemp, Error, TEXT("SteamInventory() is null"));
		return false;
	}
	TArray<SteamItemDef_t> ItemDefsSteamFormat;
	for(auto& ItemDef : ItemDefs)
	{
		ItemDefsSteamFormat.Add(ItemDef.GetSteamItemDef());
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->AddPromoItems(&ResultInventory, ItemDefsSteamFormat.GetData(), ItemDefs.Num());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::CheckResultSteamID(FSIK_SteamInventoryResult InventoryResult, FSIK_SteamId SteamID)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		UE_LOG(LogTemp, Error, TEXT("SteamInventory() is null"));
		return false;
	}
	return SteamInventory()->CheckResultSteamID(InventoryResult.GetSteamInventoryResult(), SteamID.GetSteamID());
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::ConsumeItem(FSIK_SteamInventoryResult& InventoryResult,
	FSIK_SteamItemInstanceID ItemInstance, int32 Quantity)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		UE_LOG(LogTemp, Error, TEXT("SteamInventory() is null"));
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->ConsumeItem(&ResultInventory, ItemInstance.GetSteamItemInstanceID(), Quantity);
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::DeserializeResult(FSIK_SteamInventoryResult& InventoryResult, const TArray<uint8>& Buffer)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		UE_LOG(LogTemp, Error, TEXT("SteamInventory() is null"));
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->DeserializeResult(&ResultInventory, Buffer.GetData(), Buffer.Num(), false);
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

void USIK_InventoryLibrary::DestroyResult(FSIK_SteamInventoryResult InventoryResult)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return;
	}
	SteamInventory()->DestroyResult(InventoryResult.GetSteamInventoryResult());
#endif
}

bool USIK_InventoryLibrary::ExchangeItems(FSIK_SteamInventoryResult& InventoryResult,
	const TArray<FSIK_SteamItemDef>& ItemDefsToCreate, const TArray<int32>& ArrayGenerateQuantity,
	const TArray<FSIK_SteamItemInstanceID>& ItemDefsToDestroy, const TArray<int32>& DestroyQuantity)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	TArray<SteamItemDef_t> ItemDefsToCreateSteamFormat;
	for(auto& ItemDef : ItemDefsToCreate)
	{
		ItemDefsToCreateSteamFormat.Add(ItemDef.GetSteamItemDef());
	}
	TArray<SteamItemInstanceID_t> ItemDefsToDestroySteamFormat;
	for(auto& ItemDef : ItemDefsToDestroy)
	{
		ItemDefsToDestroySteamFormat.Add(ItemDef.GetSteamItemInstanceID());
	}
	SteamInventoryResult_t ResultInventory;
	TArray<uint32> ArrayGenerateQuantityUint32;
	for (int32 Value : ArrayGenerateQuantity)
	{
		ArrayGenerateQuantityUint32.Add(static_cast<uint32>(Value));
	}
	const uint32* punArrayGenerateQuantity = ArrayGenerateQuantityUint32.GetData();

	TArray<uint32> DestroyQuantityUint32;
	for (int32 Value : DestroyQuantity)
	{
		DestroyQuantityUint32.Add(static_cast<uint32>(Value));
	}
	const uint32* punArrayDestroyQuantity = DestroyQuantityUint32.GetData();
	auto Result = SteamInventory()->ExchangeItems(&ResultInventory, ItemDefsToCreateSteamFormat.GetData(),
		punArrayGenerateQuantity, ItemDefsToCreate.Num(), ItemDefsToDestroySteamFormat.GetData(),
		punArrayDestroyQuantity, ItemDefsToDestroy.Num());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}


bool USIK_InventoryLibrary::GenerateItems(FSIK_SteamInventoryResult& InventoryResult,
                                          const TArray<FSIK_SteamItemDef>& ItemDefs, const TArray<int32>& Quantity)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	TArray<SteamItemDef_t> ItemDefsSteamFormat;
	for(auto& ItemDef : ItemDefs)
	{
		ItemDefsSteamFormat.Add(ItemDef.GetSteamItemDef());
	}
	TArray<uint32> QuantityUint32;
	for (int32 Value : Quantity)
	{
		QuantityUint32.Add(static_cast<uint32>(Value));
	}
	const uint32* punQuantity = QuantityUint32.GetData();
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->GenerateItems(&ResultInventory, ItemDefsSteamFormat.GetData(), QuantityUint32.GetData(),
  QuantityUint32.Num());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetAllItems(FSIK_SteamInventoryResult& InventoryResult)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->GetAllItems(&ResultInventory);
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetEligiblePromoItemDefinitionIDs(FSIK_SteamId SteamID, TArray<FSIK_SteamItemDef>& ItemDefs)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	TArray<SteamItemDef_t> ItemDefsSteamFormat;
	uint32 ItemDefsSteamFormatSize = 0;
	auto Result = SteamInventory()->GetEligiblePromoItemDefinitionIDs(SteamID.GetSteamID(), ItemDefsSteamFormat.GetData(),
		&ItemDefsSteamFormatSize);
	for(auto& ItemDefSteam : ItemDefsSteamFormat)
	{
		ItemDefs.Add(ItemDefSteam);
	}
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetItemDefinitionIDs(TArray<FSIK_SteamItemDef>& ItemDefs)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	TArray<SteamItemDef_t> ItemDefsSteamFormat;
	uint32 ItemDefsSteamFormatSize = 0;
	auto Result = SteamInventory()->GetItemDefinitionIDs(ItemDefsSteamFormat.GetData(), &ItemDefsSteamFormatSize);
	for(auto& ItemDefSteam : ItemDefsSteamFormat)
	{
		ItemDefs.Add(ItemDefSteam);
	}
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetItemDefinitionProperty(FSIK_SteamItemDef ItemDef, const FString& PropertyName,
	FString& Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	char ValueChar[1024];
	uint32 ValueCharSize = 1024;
	auto Result = SteamInventory()->GetItemDefinitionProperty(ItemDef.GetSteamItemDef(), TCHAR_TO_ANSI(*PropertyName),
		ValueChar, &ValueCharSize);
	Value = ValueChar;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetItemsByID(FSIK_SteamInventoryResult& InventoryResult,
	const TArray<FSIK_SteamItemInstanceID>& ItemInstances)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	TArray<SteamItemInstanceID_t> ItemInstancesSteamFormat;
	for(auto& ItemInstance : ItemInstances)
	{
		ItemInstancesSteamFormat.Add(ItemInstance.GetSteamItemInstanceID());
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->GetItemsByID(&ResultInventory, ItemInstancesSteamFormat.GetData(), ItemInstances.Num());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetItemPrice(FSIK_SteamItemDef ItemDef, int64& CurrentPrice, int64& BasePrice)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	uint64 CurrentPriceUint = 0;
	uint64 BasePriceUint = 0;
	auto Result = SteamInventory()->GetItemPrice(ItemDef.GetSteamItemDef(), &CurrentPriceUint, &BasePriceUint);
	CurrentPrice = CurrentPriceUint;
	BasePrice = BasePriceUint;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetItemsWithPrices(TArray<FSIK_SteamItemDef>& ItemDefs, TArray<int64>& CurrentPrices,
	TArray<int64>& BasePrices, int32 ArraySize)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	TArray<SteamItemDef_t> ItemDefsSteamFormat;
	TArray<uint64> CurrentPricesUint;
	TArray<uint64> BasePricesUint;
	ItemDefsSteamFormat.SetNum(ArraySize);
	CurrentPricesUint.SetNum(ArraySize);
	BasePricesUint.SetNum(ArraySize);
	auto Result = SteamInventory()->GetItemsWithPrices(ItemDefsSteamFormat.GetData(), CurrentPricesUint.GetData(),
		BasePricesUint.GetData(), ArraySize);
	for(auto& ItemDefSteam : ItemDefsSteamFormat)
	{
		ItemDefs.Add(ItemDefSteam);
	}
	for(auto& CurrentPriceUint : CurrentPricesUint)
	{
		CurrentPrices.Add(CurrentPriceUint);
	}
	for(auto& BasePriceUint : BasePricesUint)
	{
		BasePrices.Add(BasePriceUint);
	}
	return Result;
#else
	return false;
#endif
}

int32 USIK_InventoryLibrary::GetNumItemsWithPrices()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return 0;
	}
	return SteamInventory()->GetNumItemsWithPrices();
#else
	return 0;
#endif
}

bool USIK_InventoryLibrary::GetResultItemProperty(FSIK_SteamInventoryResult InventoryResult, int32 ItemIndex,
	const FString& PropertyName, FString& Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	char ValueChar[1024];
	uint32 ValueCharSize = 1024;
	auto Result = SteamInventory()->GetResultItemProperty(InventoryResult.GetSteamInventoryResult(), ItemIndex,
		TCHAR_TO_ANSI(*PropertyName), ValueChar, &ValueCharSize);
	Value = ValueChar;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::GetResultItems(FSIK_SteamInventoryResult InventoryResult,
	TArray<FSIK_SteamItemDetails>& ItemInstances)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	uint32 ItemInstancesSteamFormatSize = 0;
	if(SteamInventory()->GetResultItems(InventoryResult.GetSteamInventoryResult(), nullptr, &ItemInstancesSteamFormatSize))
	{
		TArray<SteamItemDetails_t> ItemInstancesSteamFormat;
		ItemInstancesSteamFormat.SetNum(ItemInstancesSteamFormatSize);
		if(SteamInventory()->GetResultItems(InventoryResult.GetSteamInventoryResult(), ItemInstancesSteamFormat.GetData(),
			&ItemInstancesSteamFormatSize))
		{
			for(auto& ItemInstanceSteam : ItemInstancesSteamFormat)
			{
				ItemInstances.Add(ItemInstanceSteam);
			}
			return true;
		}
	}
	return false;
#else
	return false;
#endif
}
	
TEnumAsByte<ESIK_Result> USIK_InventoryLibrary::GetResultStatus(FSIK_SteamInventoryResult InventoryResult)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return ESIK_Result::ResultFail;
	}
	return static_cast<ESIK_Result>(SteamInventory()->GetResultStatus(InventoryResult.GetSteamInventoryResult()));
#else
	return ESIK_Result::ResultFail;
#endif
}

FDateTime USIK_InventoryLibrary::GetResultTimestamp(FSIK_SteamInventoryResult InventoryResult, int32& Timestamp)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return FDateTime();
	}
	Timestamp = SteamInventory()->GetResultTimestamp(InventoryResult.GetSteamInventoryResult());
	return FDateTime::FromUnixTimestamp(Timestamp);
#else
	return FDateTime();
#endif
}

bool USIK_InventoryLibrary::GrantPromoItems(FSIK_SteamInventoryResult& InventoryResult)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->GrantPromoItems(&ResultInventory);
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::LoadItemDefinitions()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	return SteamInventory()->LoadItemDefinitions();
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::SerializeResult(FSIK_SteamInventoryResult InventoryResult, TArray<uint8>& Buffer)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	uint32 BufferSize = 0;
	auto Result = SteamInventory()->SerializeResult(InventoryResult.GetSteamInventoryResult(), Buffer.GetData(), &BufferSize);
	Buffer.SetNum(BufferSize);
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::TransferItemQuantity(FSIK_SteamInventoryResult& InventoryResult,
	FSIK_SteamItemInstanceID ItemInstance, int32 Quantity, FSIK_SteamItemInstanceID itemIdDest)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->TransferItemQuantity(&ResultInventory, ItemInstance.GetSteamItemInstanceID(), Quantity,
		itemIdDest.GetSteamItemInstanceID());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::TriggerItemDrop(FSIK_SteamInventoryResult& InventoryResult, FSIK_SteamItemDef ItemDef)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->TriggerItemDrop(&ResultInventory, ItemDef.GetSteamItemDef());
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

FSIK_SteamInventoryUpdateHandle USIK_InventoryLibrary::StartUpdateProperties()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return FSIK_SteamInventoryUpdateHandle();
	}
	return SteamInventory()->StartUpdateProperties();
#else
	return FSIK_SteamInventoryUpdateHandle();
#endif
}

bool USIK_InventoryLibrary::SubmitUpdateProperties(FSIK_SteamInventoryUpdateHandle UpdateHandle,
	FSIK_SteamInventoryResult& InventoryResult)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	SteamInventoryResult_t ResultInventory;
	auto Result = SteamInventory()->SubmitUpdateProperties(UpdateHandle.GetSteamInventoryUpdateHandle(),
		&ResultInventory);
	InventoryResult = ResultInventory;
	return Result;
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::RemoveProperty(FSIK_SteamInventoryUpdateHandle UpdateHandle,
	FSIK_SteamItemInstanceID ItemInstance, const FString& PropertyName)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	return SteamInventory()->RemoveProperty(UpdateHandle.GetSteamInventoryUpdateHandle(),
	ItemInstance.GetSteamItemInstanceID(), TCHAR_TO_ANSI(*PropertyName));
#else
	return false;
#endif
}

bool USIK_InventoryLibrary::SetProperty(FSIK_SteamInventoryUpdateHandle UpdateHandle,
	FSIK_SteamItemInstanceID ItemInstance, const FString& PropertyName, const FString& Value)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamInventory())
	{
		return false;
	}
	return SteamInventory()->SetProperty(UpdateHandle.GetSteamInventoryUpdateHandle(),
		ItemInstance.GetSteamItemInstanceID(), TCHAR_TO_ANSI(*PropertyName), TCHAR_TO_ANSI(*Value));
#else
	return false;
#endif
}

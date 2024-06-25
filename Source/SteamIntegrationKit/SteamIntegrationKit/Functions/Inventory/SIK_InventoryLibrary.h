// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SIK_InventoryLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_InventoryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/*
	Adds a single promotional item to the inventory.
	@param InventoryResult - The result handle.
	@param ItemDef - The definition of the item to add.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool AddPromoItem(FSIK_SteamInventoryResult& InventoryResult, FSIK_SteamItemDef ItemDef);

	/*
	Adds multiple promotional items to the inventory.
	@param InventoryResult - The result handle.
	@param ItemDefs - The definitions of the items to add.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool AddPromoItems(FSIK_SteamInventoryResult& InventoryResult, const TArray<FSIK_SteamItemDef>& ItemDefs);

	/*
	Checks if the result is associated with the specified Steam ID.
	@param InventoryResult - The result handle.
	@param SteamID - The Steam ID to check against.
	@return - true if the result is associated with the Steam ID, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool CheckResultSteamID(FSIK_SteamInventoryResult InventoryResult, FSIK_SteamId SteamID);

	/*
	Consumes items from the inventory.
	@param InventoryResult - The result handle.
	@param ItemInstance - The instance ID of the item to consume.
	@param Quantity - The quantity to consume.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool ConsumeItem(FSIK_SteamInventoryResult& InventoryResult, FSIK_SteamItemInstanceID ItemInstance, int32 Quantity);

	/*
	Deserializes an inventory result from a buffer.
	@param InventoryResult - The result handle.
	@param Buffer - The buffer containing the serialized data.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool DeserializeResult(FSIK_SteamInventoryResult& InventoryResult, const TArray<uint8>& Buffer);

	/*
	Destroys an inventory result handle.
	@param InventoryResult - The result handle to destroy.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static void DestroyResult(FSIK_SteamInventoryResult InventoryResult);

	/*
	Exchanges items in the inventory.
	@param InventoryResult - The result handle.
	@param ItemDefsToCreate - The definitions of items to create.
	@param ArrayGenerateQuantity - The quantities of items to create.
	@param ItemDefsToDestroy - The instance IDs of items to destroy.
	@param DestroyQuantity - The quantities of items to destroy.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool ExchangeItems(FSIK_SteamInventoryResult& InventoryResult, const TArray<FSIK_SteamItemDef>& ItemDefsToCreate,
		const TArray<int32>& ArrayGenerateQuantity, const TArray<FSIK_SteamItemInstanceID>& ItemDefsToDestroy,
		const TArray<int32>& DestroyQuantity);

	/*
	Generates items in the inventory.
	@param InventoryResult - The result handle.
	@param ItemDefs - The definitions of items to generate.
	@param Quantity - The quantities of items to generate.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GenerateItems(FSIK_SteamInventoryResult& InventoryResult, const TArray<FSIK_SteamItemDef>& ItemDefs,
		const TArray<int32>& Quantity);

	/*
	Gets all items in the inventory.
	@param InventoryResult - The result handle.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetAllItems(FSIK_SteamInventoryResult& InventoryResult);

	/*
	Gets the eligible promotional item definitions IDs for a user.
	@param SteamID - The Steam ID of the user.
	@param ItemDefs - The array to store the item definitions.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetEligiblePromoItemDefinitionIDs(FSIK_SteamId SteamID, TArray<FSIK_SteamItemDef>& ItemDefs);

	/*
	Gets the item definition IDs.
	@param ItemDefs - The array to store the item definitions.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetItemDefinitionIDs(TArray<FSIK_SteamItemDef>& ItemDefs);

	/*
	Gets the property of an item definition.
	@param ItemDef - The definition of the item.
	@param PropertyName - The name of the property.
	@param Value - The value of the property.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetItemDefinitionProperty(FSIK_SteamItemDef ItemDef, const FString& PropertyName, FString& Value);

	/*
	Gets items by their instance IDs.
	@param InventoryResult - The result handle.
	@param ItemInstances - The array of instance IDs.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetItemsByID(FSIK_SteamInventoryResult& InventoryResult, const TArray<FSIK_SteamItemInstanceID>& ItemInstances);

	/*
	Gets the price of an item.
	@param ItemDef - The definition of the item.
	@param CurrentPrice - The current price of the item.
	@param BasePrice - The base price of the item.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetItemPrice(FSIK_SteamItemDef ItemDef, int64& CurrentPrice, int64& BasePrice);

	/*
	Gets items with their prices.
	@param ItemDefs - The array to store the item definitions.
	@param CurrentPrices - The array to store the current prices.
	@param BasePrices - The array to store the base prices.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetItemsWithPrices(TArray<FSIK_SteamItemDef>& ItemDefs, TArray<int64>& CurrentPrices, TArray<int64>& BasePrices, int32 ArraySize = 0);
	
	/*
	Gets the number of items with prices.
	@return - The number of items with prices.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static int32 GetNumItemsWithPrices();

	/*
	Gets a property of an item in the result.
	@param InventoryResult - The result handle.
	@param ItemIndex - The index of the item.
	@param PropertyName - The name of the property.
	@param Value - The value of the property.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetResultItemProperty(FSIK_SteamInventoryResult InventoryResult, int32 ItemIndex, const FString& PropertyName, FString& Value);

	/*
	Gets the items in the result.
	@param InventoryResult - The result handle.
	@param ItemInstances - The array to store the item instances.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GetResultItems(FSIK_SteamInventoryResult InventoryResult, TArray<FSIK_SteamItemDetails>& ItemInstances);

	/*
	Gets the status of the result.
	@param InventoryResult - The result handle.
	@return - The result status as an ESIK_Result enum.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static TEnumAsByte<ESIK_Result> GetResultStatus(FSIK_SteamInventoryResult InventoryResult);

	/*
	Gets the timestamp of the result.
	@param InventoryResult - The result handle.
	@param Timestamp - The timestamp to store the result.
	@return - The timestamp as a FDateTime object.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static FDateTime GetResultTimestamp(FSIK_SteamInventoryResult InventoryResult, int32& Timestamp);

	/*
	Grants promotional items to the user.
	@param InventoryResult - The result handle.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool GrantPromoItems(FSIK_SteamInventoryResult& InventoryResult);

	/*
	Loads the item definitions from the server.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool LoadItemDefinitions();

	/*
	Serializes the result to a buffer.
	@param InventoryResult - The result handle.
	@param Buffer - The buffer to store the serialized data.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool SerializeResult(FSIK_SteamInventoryResult InventoryResult, TArray<uint8>& Buffer);
	
	/*
	Transfers a quantity of an item to another item instance.
	@param InventoryResult - The result handle.
	@param ItemInstance - The instance ID of the item to transfer from.
	@param Quantity - The quantity to transfer.
	@param ItemIdDest - The instance ID of the item to transfer to.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool TransferItemQuantity(FSIK_SteamInventoryResult& InventoryResult, FSIK_SteamItemInstanceID ItemInstance, int32 Quantity, FSIK_SteamItemInstanceID itemIdDest);

	/*
	Triggers an item drop for the user.
	@param InventoryResult - The result handle.
	@param ItemDef - The definition of the item to drop.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool TriggerItemDrop(FSIK_SteamInventoryResult& InventoryResult, FSIK_SteamItemDef ItemDef);

	/*
	Begins an update to item properties.
	@return - The update handle.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static FSIK_SteamInventoryUpdateHandle StartUpdateProperties();

	/*
	Submits the update to item properties.
	@param UpdateHandle - The update handle.
	@param InventoryResult - The result handle.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool SubmitUpdateProperties(FSIK_SteamInventoryUpdateHandle UpdateHandle, FSIK_SteamInventoryResult& InventoryResult);

	/*
	Removes a property from an item.
	@param UpdateHandle - The update handle.
	@param ItemInstance - The instance ID of the item.
	@param PropertyName - The name of the property to remove.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool RemoveProperty(FSIK_SteamInventoryUpdateHandle UpdateHandle, FSIK_SteamItemInstanceID ItemInstance, const FString& PropertyName);

	/*
	Sets a property for an item.
	@param UpdateHandle - The update handle.
	@param ItemInstance - The instance ID of the item.
	@param PropertyName - The name of the property to set.
	@param Value - The value of the property.
	@return - true if successful, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || Inventory")
	static bool SetProperty(FSIK_SteamInventoryUpdateHandle UpdateHandle, FSIK_SteamItemInstanceID ItemInstance, const FString& PropertyName, const FString& Value);
};

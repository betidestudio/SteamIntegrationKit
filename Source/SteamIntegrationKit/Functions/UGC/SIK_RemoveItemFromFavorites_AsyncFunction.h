
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_SharedFile.h"
#include "SIK_RemoveItemFromFavorites_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoveItemFromFavoritesComplete, FSIK_PublishedFileId, PublishedFileId, TEnumAsByte<ESIK_Result>, Result, bool, bWasAddRequest);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_RemoveItemFromFavorites_AsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_RemoveItemFromFavorites_AsyncFunction* RemoveItemFromFavorites(FSIK_AppId AppId, FSIK_PublishedFileId PublishedFileId);

    UPROPERTY(BlueprintAssignable)
    FOnRemoveItemFromFavoritesComplete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnRemoveItemFromFavoritesComplete OnFailure;

private:
    FSIK_AppId Var_AppId;
    FSIK_PublishedFileId Var_PublishedFileId;
    virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
    void OnComplete(UserFavoriteItemsListChanged_t* pParam, bool bIOFailure);
    SteamAPICall_t CallbackHandle;
    CCallResult<USIK_RemoveItemFromFavorites_AsyncFunction, UserFavoriteItemsListChanged_t> CallResult;
#endif
};
        
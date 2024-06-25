import os

def generate_ue5_plugin(functions):
    for func in functions:
        function_name, return_type, args = func['name'], func['return_type'], func['args']
        
        # Generate header content
        header_content = f'''
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include <steam_api.h>
#include "SteamIntegrationKit/SIK_{function_name}_AsyncFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn{function_name}Complete);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_{function_name}_AsyncFunction : public UBlueprintAsyncActionBase
{{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Steam Integration Kit || SDK Functions || UGC")
    static USIK_{function_name}_AsyncFunction* {function_name}({', '.join(args)});

    UPROPERTY(BlueprintAssignable)
    FOn{function_name}Complete OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FOn{function_name}Complete OnFailure;

private:
    void Activate() override;
    void OnComplete(bool bSuccess);
    SteamAPICall_t CallbackHandle;
    CCallResult<U{function_name}_Async, {return_type}> CallResult;
}};
        '''
        
        # Generate source content
        source_content = f'''
#include "SIK_{function_name}_AsyncFunction.h"

USIK_{function_name}_AsyncFunction* USIK_{function_name}_AsyncFunction::{function_name}({', '.join(args)})
{{
    USIK_{function_name}_AsyncFunction* Obj = NewObject<USIK_{function_name}_AsyncFunction>();
    return Obj;
}}

void USIK_{function_name}_AsyncFunction::Activate()
{{
    if(!SteamUGC())
    {{
        OnFailure.Broadcast();
        SetReadyToDestroy();
        return;
    }}
    CallbackHandle = SteamUGC()->{function_name}(...);
    CallResult.Set(CallbackHandle, this, &USIK_{function_name}_AsyncFunction::OnComplete);
}}

void USIK_{function_name}_AsyncFunction::OnComplete(bool bSuccess)
{{
    if (bSuccess)
    {{
        OnSuccess.Broadcast();
    }}
    else
    {{
        OnFailure.Broadcast();
    }}
    SetReadyToDestroy();
}}
        '''
        
        # Create header and source files
        header_file_path = os.path.join(os.getcwd(), f"SIK_{function_name}_AsyncFunction.h")
        source_file_path = os.path.join(os.getcwd(), f"SIK_{function_name}_AsyncFunction.cpp")

        with open(header_file_path, 'w') as file:
            file.write(header_content)
        with open(source_file_path, 'w') as file:
            file.write(source_content)

        print(f"Generated {function_name}_AsyncFunction.h and {function_name}_AsyncFunction.cpp")

# Example functions to generate
functions = [
    {"name": "AddAppDependency", "return_type": "AddAppDependencyResult_t", "args": ["PublishedFileId_t nPublishedFileID", "AppId_t nAppID"]},
    {"name": "AddDependency", "return_type": "AddUGCDependencyResult_t", "args": ["PublishedFileId_t nParentPublishedFileID", "PublishedFileId_t nChildPublishedFileID"]},
    {"name": "AddItemToFavorites", "return_type": "UserFavoriteItemsListChanged_t", "args": ["AppId_t nAppId", "PublishedFileId_t nPublishedFileID"]},
    {"name": "CreateItem", "return_type": "CreateItemResult_t", "args": ["AppId_t nConsumerAppId", "EWorkshopFileType eFileType"]},
    {"name": "DeleteItem", "return_type": "DeleteItemResult_t", "args": ["PublishedFileId_t nPublishedFileID"]},
    {"name": "GetAppDependencies", "return_type": "GetAppDependenciesResult_t", "args": ["PublishedFileId_t nPublishedFileID"]},
    {"name": "GetUserItemVote", "return_type": "GetUserItemVoteResult_t", "args": ["PublishedFileId_t nPublishedFileID"]},
    {"name": "RemoveAppDependency", "return_type": "RemoveAppDependencyResult_t", "args": ["PublishedFileId_t nPublishedFileID", "AppId_t nAppID"]},
    {"name": "RemoveDependency", "return_type": "RemoveUGCDependencyResult_t", "args": ["PublishedFileId_t nParentPublishedFileID", "PublishedFileId_t nChildPublishedFileID"]},
    {"name": "RemoveItemFromFavorites", "return_type": "UserFavoriteItemsListChanged_t", "args": ["AppId_t nAppId", "PublishedFileId_t nPublishedFileID"]},
    {"name": "SetUserItemVote", "return_type": "SetUserItemVoteResult_t", "args": ["PublishedFileId_t nPublishedFileID", "bool bVoteUp"]},
    {"name": "StartPlaytimeTracking", "return_type": "StartPlaytimeTrackingResult_t", "args": ["PublishedFileId_t *pvecPublishedFileID", "uint32 unNumPublishedFileIDs"]},
    {"name": "StopPlaytimeTracking", "return_type": "StopPlaytimeTrackingResult_t", "args": ["PublishedFileId_t *pvecPublishedFileID", "uint32 unNumPublishedFileIDs"]},
    {"name": "StopPlaytimeTrackingForAllItems", "return_type": "StopPlaytimeTrackingResult_t", "args": []},
    {"name": "SubmitItemUpdate", "return_type": "SubmitItemUpdateResult_t", "args": ["UGCUpdateHandle_t handle", "const char *pchChangeNote"]},
    {"name": "SubscribeItem", "return_type": "RemoteStorageSubscribePublishedFileResult_t", "args": ["PublishedFileId_t nPublishedFileID"]},
    {"name": "UnsubscribeItem", "return_type": "RemoteStorageUnsubscribePublishedFileResult_t", "args": ["PublishedFileId_t nPublishedFileID"]},
    {"name": "SendQueryUGCRequest", "return_type": "SteamUGCQueryCompleted_t", "args": ["UGCQueryHandle_t handle"]}
]

# Call the function to generate the files
generate_ue5_plugin(functions)

// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_FriendsLibrary.h"
#include "SIK_SharedFile.h"
#include "SIK_EnumerateFollowingList_AsyncFunction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEnumerateFollowingListDelegate, const TArray<FSIK_SteamId>&, FollowingList, int64, ResultsReturned, int64, TotalResults);
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_EnumerateFollowingList_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Enumerate Steam Following List",meta = (BlueprintInternalUseOnly = "true",Keywords="EnumerateFollowingList"), Category= "Steam Integration Kit || SDK Functions || Friends")
	static USIK_EnumerateFollowingList_AsyncFunction* EnumerateFollowingList(int32 StartIndex);

	UPROPERTY(BlueprintAssignable)
	FEnumerateFollowingListDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEnumerateFollowingListDelegate OnFailure;

private:
	int32 m_StartIndex;
	void OnEnumerateFollowingList(FriendsEnumerateFollowingList_t* FriendsEnumerateFollowings, bool bIOFailure);
	virtual void Activate() override;
	SteamAPICall_t m_CallbackHandle;
	CCallResult<USIK_EnumerateFollowingList_AsyncFunction, FriendsEnumerateFollowingList_t> m_Callback;
};

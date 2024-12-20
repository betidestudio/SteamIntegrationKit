// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SIK_SharedFile.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SIK_UploadLeaderboardScore_AsyncFunction.generated.h"

UENUM(BlueprintType)
enum ESIK_LeaderboardUploadScoreMethod
{
	LeaderboardUploadScoreMethodNone = 0 UMETA(DisplayName = "None"),
	LeaderboardUploadScoreMethodKeepBest = 1 UMETA(DisplayName = "Keep Best"),		// Leaderboard will keep user's best score
	LeaderboardUploadScoreMethodForceUpdate = 2 UMETA(DisplayName = "Force Update"),	// Leaderboard will always update user's score
};

USTRUCT(BlueprintType)
struct FSIK_LeaderboardScoreUploaded
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Steam Integration Kit || User Stats")
	int32 LeaderboardId = 0;

	UPROPERTY(BlueprintReadOnly, Category="Steam Integration Kit || User Stats")
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly, Category="Steam Integration Kit || User Stats")
	bool bScoreChanged = false;

	UPROPERTY(BlueprintReadOnly, Category="Steam Integration Kit || User Stats")
	int32 GlobalRankNew = -1;

	UPROPERTY(BlueprintReadOnly, Category="Steam Integration Kit || User Stats")
	int32 GlobalRankPrevious = -1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderboardScoreUploaded_Delegate, const FSIK_LeaderboardScoreUploaded&, LeaderboardScoreUploaded);

UCLASS()
class STEAMINTEGRATIONKIT_API USIK_UploadLeaderboardScore_AsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Upload Steam Leaderboard Score",meta = (BlueprintInternalUseOnly = "true",Keywords="UploadLeaderboardScore"), Category="Steam Integration Kit || SDK Functions || User Stats")
	static USIK_UploadLeaderboardScore_AsyncFunction* UploadLeaderboardScore(int32 LeaderboardId, TEnumAsByte<ESIK_LeaderboardUploadScoreMethod> UploadScoreMethod, int32 Score);

	UPROPERTY(BlueprintAssignable)
	FLeaderboardScoreUploaded_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLeaderboardScoreUploaded_Delegate OnFailure;
	
private:
	TEnumAsByte<ESIK_LeaderboardUploadScoreMethod> Var_UploadScoreMethod;
	int32 Var_LeaderboardId;
	int32 Var_Score;
	virtual void Activate() override;
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)	
	void OnUploadLeaderboardScore(LeaderboardScoreUploaded_t* LeaderboardScoreUploaded, bool bIOFailure);
	SteamAPICall_t CallbackHandle;
	CCallResult<USIK_UploadLeaderboardScore_AsyncFunction, LeaderboardScoreUploaded_t> OnUploadLeaderboardScoreCallResult;
#endif
};

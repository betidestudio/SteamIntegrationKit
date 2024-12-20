// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_RequestLANServerList_AsyncFunction.h"

#include "SIK_SharedFile.h"
#include "Async/Async.h"

USIK_RequestLANServerList_AsyncFunction* USIK_RequestLANServerList_AsyncFunction::RequestLANServerList(FSIK_AppId AppId, float TimeOut)
{
	USIK_RequestLANServerList_AsyncFunction* BlueprintNode = NewObject<USIK_RequestLANServerList_AsyncFunction>();
	BlueprintNode->VarAppId = AppId;
	BlueprintNode->Var_TimeOut = TimeOut;
	return BlueprintNode;
}

void USIK_RequestLANServerList_AsyncFunction::Activate()
{
	Super::Activate();
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamMatchmakingServers())
	{
		return;
	}
	HServerListRequest Request = SteamMatchmakingServers()->RequestLANServerList(VarAppId.GetAppID(), this);
	FDateTime DateTime = FDateTime::UtcNow();
	StartTime = DateTime.ToUnixTimestamp();
#else
	OnFailure.Broadcast(ESIK_MatchMakingServerResponse::ServerResponded, TArray<FSIK_FoundServers>());
	SetReadyToDestroy();
	MarkAsGarbage();
#endif
}

#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
void USIK_RequestLANServerList_AsyncFunction::ServerResponded(HServerListRequest hRequest, int iServer)
{
	UE_LOG(LogTemp, Warning, TEXT("ServerResponded"));
	//Calculate the time from the start of the request
	FDateTime DateTime = FDateTime::UtcNow();
	const double CurrentTime = DateTime.ToUnixTimestamp();
	const double TimeElapsed = CurrentTime - StartTime;
	if(TimeElapsed >= Var_TimeOut)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time out exceeded with current time: %f"), TimeElapsed);
		SteamMatchmakingServers()->CancelQuery(hRequest);
	}
}

void USIK_RequestLANServerList_AsyncFunction::ServerFailedToRespond(HServerListRequest hRequest, int iServer)
{
	UE_LOG(LogTemp, Warning, TEXT("ServerFailedToRespond"));
	FDateTime DateTime = FDateTime::UtcNow();
	const double CurrentTime = DateTime.ToUnixTimestamp();
	const double TimeElapsed = CurrentTime - StartTime;
	if(TimeElapsed >= Var_TimeOut)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time out exceeded with current time: %f"), TimeElapsed);
		SteamMatchmakingServers()->CancelQuery(hRequest);
	}
}

void USIK_RequestLANServerList_AsyncFunction::RefreshComplete(HServerListRequest hRequest,
	EMatchMakingServerResponse response)
{
	auto Param = response;
	auto hRequestInput = hRequest;
	AsyncTask(ENamedThreads::GameThread, [this, Param, hRequestInput, hRequest]()
	{
		if(SteamMatchmakingServers()->GetServerCount(hRequestInput) == 0)
		{
			OnSuccess.Broadcast(static_cast<TEnumAsByte<ESIK_MatchMakingServerResponse>>(Param), TArray<FSIK_FoundServers>());
		}
		else
		{
			TArray<FSIK_FoundServers> FoundServers;
			for(int32 i = 0; i < SteamMatchmakingServers()->GetServerCount(hRequestInput); i++)
			{
				if(auto gameinfo = SteamMatchmakingServers()->GetServerDetails(hRequestInput,i))
				{
					FoundServers.Add(*gameinfo);
				}
			}
			OnSuccess.Broadcast(static_cast<TEnumAsByte<ESIK_MatchMakingServerResponse>>(Param), FoundServers);
		}
	SteamMatchmakingServers()->ReleaseRequest(hRequest);
	SetReadyToDestroy();
	MarkAsGarbage();
	});
}
#endif
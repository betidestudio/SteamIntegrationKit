// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_NetworkingLibrary.h"

bool USIK_NetworkingLibrary::AcceptP2PSessionWithUser(FSIK_SteamId SteamIDRemote)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	return SteamNetworking()->AcceptP2PSessionWithUser(SteamIDRemote.GetSteamID());
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::AllowP2PPacketRelay(bool Allow)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	return SteamNetworking()->AllowP2PPacketRelay(Allow);
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::CloseP2PChannelWithUser(FSIK_SteamId SteamIDRemote, int32 Channel)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	return SteamNetworking()->CloseP2PChannelWithUser(SteamIDRemote.GetSteamID(), Channel);
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::CloseP2PSessionWithUser(FSIK_SteamId SteamIDRemote)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	return SteamNetworking()->CloseP2PSessionWithUser(SteamIDRemote.GetSteamID());
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::GetP2PSessionState(FSIK_SteamId SteamIDRemote, FSIK_P2PSessionState& OutP2PSessionState)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	P2PSessionState_t SteamP2PSessionState;
	auto Result = SteamNetworking()->GetP2PSessionState(SteamIDRemote.GetSteamID(), &SteamP2PSessionState);
	OutP2PSessionState = SteamP2PSessionState;
	return Result;
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::IsP2PPacketAvailable(int32& MsgSize, int32 Channel)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	uint32 MsgSize32 = 0;
	auto Res = SteamNetworking()->IsP2PPacketAvailable(&MsgSize32, Channel);
	MsgSize = MsgSize32;
	return Res;
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::ReadP2PPacket(TArray<uint8>& OutMsg, int32 MsgSize, FSIK_SteamId& OutSteamIDRemote,
	int32 Channel)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	uint32 MsgSize32 = MsgSize;
	CSteamID SteamIDRemote;
	TArray<uint8> Msg;
	Msg.SetNum(MsgSize32);
	auto Res = SteamNetworking()->ReadP2PPacket(Msg.GetData(), MsgSize32, &MsgSize32, &SteamIDRemote, Channel);
	OutMsg = Msg;
	OutSteamIDRemote = SteamIDRemote;
	return Res;
#else
	return false;
#endif
}

bool USIK_NetworkingLibrary::SendP2PPacket(FSIK_SteamId SteamIDRemote, const TArray<uint8>& Msg, int32 Channel,
	TEnumAsByte<ESIK_P2PSend> SendType)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamNetworking())
	{
		return false;
	}
	return SteamNetworking()->SendP2PPacket(SteamIDRemote.GetSteamID(), Msg.GetData(), Msg.Num(), static_cast<EP2PSend>(SendType.GetValue()), Channel);
#else
	return false;
#endif
}

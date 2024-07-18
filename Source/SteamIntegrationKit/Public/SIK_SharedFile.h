// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineKeyValuePair.h"
THIRD_PARTY_INCLUDES_START
#if WITH_ENGINE_STEAM
#include "steam/steamclientpublic.h"
#include "steam/isteamuserstats.h"
#include "steam/isteaminventory.h"
#include "steam/isteammatchmaking.h"
#include "steam/isteamnetworking.h"
#include "steam/isteamremotestorage.h"
#include "steam/isteamscreenshots.h"
#include "steam/isteamugc.h"
#include "steam/steamnetworkingtypes.h"
#include "steam/isteamapps.h"
#include "steam/steamclientpublic.h"
#else
#include "steamclientpublic.h"
#include "isteamuserstats.h"
#include "isteaminventory.h"
#include "isteammatchmaking.h"
#include "isteamnetworking.h"
#include "isteamremotestorage.h"
#include "isteamscreenshots.h"
#include "isteamugc.h"
#include "steamnetworkingtypes.h"
#include "isteamapps.h"
#include "steamclientpublic.h"
#endif
THIRD_PARTY_INCLUDES_END
#include "OnlineSessionSettings.h"
#include "GameFramework/SaveGame.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "UObject/Object.h"
#include "SIK_SharedFile.generated.h"

UENUM(BlueprintType)
enum ESIK_BeginAuthSessionResult
{
	BeginAuthSessionResultOK = 0 UMETA(DisplayName = "OK"),
	BeginAuthSessionResultInvalidTicket = 1 UMETA(DisplayName = "Invalid Ticket"),
	BeginAuthSessionResultDuplicateRequest = 2 UMETA(DisplayName = "Duplicate Request"),
	BeginAuthSessionResultInvalidVersion = 3 UMETA(DisplayName = "Invalid Version"),
	BeginAuthSessionResultGameMismatch = 4 UMETA(DisplayName = "Game Mismatch"),
	BeginAuthSessionResultExpiredTicket = 5 UMETA(DisplayName = "Expired Ticket"),
	BeginAuthSessionResultFailure = 6 UMETA(DisplayName = "Failure")
};

UENUM(BlueprintType)
enum ESIK_VoiceResult
{
	VoiceResultOK = 0 UMETA(DisplayName = "OK"),
	VoiceResultNotInitialized = 1 UMETA(DisplayName = "Not Initialized"),
	VoiceResultNotRecording = 2 UMETA(DisplayName = "Not Recording"),
	VoiceResultNoData = 3 UMETA(DisplayName = "No Data"),
	VoiceResultBufferTooSmall = 4 UMETA(DisplayName = "Buffer Too Small"),
	VoiceResultDataCorrupted = 5 UMETA(DisplayName = "Data Corrupted"),
	VoiceResultRestricted = 6 UMETA(DisplayName = "Restricted"),
	VoiceResultUnsupportedCodec = 7 UMETA(DisplayName = "Unsupported Codec"),
	VoiceResultReceiverOutOfDate = 8 UMETA(DisplayName = "Receiver Out Of Date"),
	VoiceResultReceiverDidNotAnswer = 9 UMETA(DisplayName = "Receiver Did Not Answer"),
};

USTRUCT(BlueprintType)
struct FSIK_AppId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 AppID = 0;

	FSIK_AppId()
	{
		AppID = 0;
	}
	FSIK_AppId(AppId_t AppID)
	{
		this->AppID = AppID;
	}
	AppId_t GetAppID() const
	{
		return AppID;
	}
};

USTRUCT(BlueprintType)
struct FSIK_DepotId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 DepotID = 0;

	FSIK_DepotId()
	{
		DepotID = 0;
	}
	FSIK_DepotId(DepotId_t DepotID)
	{
		this->DepotID = DepotID;
	}
	DepotId_t GetDepotID() const
	{
		return DepotID;
	}
};

USTRUCT(BlueprintType)
struct FSIK_AccountID
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 AccountID = 0;

	FSIK_AccountID()
	{
		AccountID = 0;
	}
	FSIK_AccountID(AccountID_t AccountID)
	{
		this->AccountID = AccountID;
	}
	AccountID_t GetAccountID() const
	{
		return AccountID;
	}
};

UENUM(BlueprintType)
enum ESIK_Result
{
	ResultNone = 0,							// no result
	ResultOK	= 1,							// success
	ResultFail = 2,							// generic failure 
	ResultNoConnection = 3,					// no/failed network connection
//	ResultNoConnectionRetry = 4,				// OBSOLETE - removed
	ResultInvalidPassword = 5,				// password/ticket is invalid
	ResultLoggedInElsewhere = 6,				// same user logged in elsewhere
	ResultInvalidProtocolVer = 7,			// protocol version is incorrect
	ResultInvalidParam = 8,					// a parameter is incorrect
	ResultFileNotFound = 9,					// file was not found
	ResultBusy = 10,							// called method busy - action not taken
	ResultInvalidState = 11,					// called object was in an invalid state
	ResultInvalidName = 12,					// name is invalid
	ResultInvalidEmail = 13,					// email is invalid
	ResultDuplicateName = 14,				// name is not unique
	ResultAccessDenied = 15,					// access is denied
	ResultTimeout = 16,						// operation timed out
	ResultBanned = 17,						// VAC2 banned
	ResultAccountNotFound = 18,				// account not found
	ResultInvalidSteamID = 19,				// steamID is invalid
	ResultServiceUnavailable = 20,			// The requested service is currently unavailable
	ResultNotLoggedOn = 21,					// The user is not logged on
	ResultPending = 22,						// Request is pending (may be in process, or waiting on third party)
	ResultEncryptionFailure = 23,			// Encryption or Decryption failed
	ResultInsufficientPrivilege = 24,		// Insufficient privilege
	ResultLimitExceeded = 25,				// Too much of a good thing
	ResultRevoked = 26,						// Access has been revoked (used for revoked guest passes)
	ResultExpired = 27,						// License/Guest pass the user is trying to access is expired
	ResultAlreadyRedeemed = 28,				// Guest pass has already been redeemed by account, cannot be acked again
	ResultDuplicateRequest = 29,				// The request is a duplicate and the action has already occurred in the past, ignored this time
	ResultAlreadyOwned = 30,					// All the games in this guest pass redemption request are already owned by the user
	ResultIPNotFound = 31,					// IP address not found
	ResultPersistFailed = 32,				// failed to write change to the data store
	ResultLockingFailed = 33,				// failed to acquire access lock for this operation
	ResultLogonSessionReplaced = 34,
	ResultConnectFailed = 35,
	ResultHandshakeFailed = 36,
	ResultIOFailure = 37,
	ResultRemoteDisconnect = 38,
	ResultShoppingCartNotFound = 39,			// failed to find the shopping cart requested
	ResultBlocked = 40,						// a user didn't allow it
	ResultIgnored = 41,						// target is ignoring sender
	ResultNoMatch = 42,						// nothing matching the request found
	ResultAccountDisabled = 43,
	ResultServiceReadOnly = 44,				// this service is not accepting content changes right now
	ResultAccountNotFeatured = 45,			// account doesn't have value, so this feature isn't available
	ResultAdministratorOK = 46,				// allowed to take this action, but only because requester is admin
	ResultContentVersion = 47,				// A Version mismatch in content transmitted within the Steam protocol.
	ResultTryAnotherCM = 48,					// The current CM can't service the user making a request, user should try another.
	ResultPasswordRequiredToKickSession = 49,// You are already logged in elsewhere, this cached credential login has failed.
	ResultAlreadyLoggedInElsewhere = 50,		// You are already logged in elsewhere, you must wait
	ResultSuspended = 51,					// Long running operation (content download) suspended/paused
	ResultCancelled = 52,					// Operation canceled (typically by user: content download)
	ResultDataCorruption = 53,				// Operation canceled because data is ill formed or unrecoverable
	ResultDiskFull = 54,						// Operation canceled - not enough disk space.
	ResultRemoteCallFailed = 55,				// an remote call or IPC call failed
	ResultPasswordUnset = 56,				// Password could not be verified as it's unset server side
	ResultExternalAccountUnlinked = 57,		// External account (PSN, Facebook...) is not linked to a Steam account
	ResultPSNTicketInvalid = 58,				// PSN ticket was invalid
	ResultExternalAccountAlreadyLinked = 59,	// External account (PSN, Facebook...) is already linked to some other account, must explicitly request to replace/delete the link first
	ResultRemoteFileConflict = 60,			// The sync cannot resume due to a conflict between the local and remote files
	ResultIllegalPassword = 61,				// The requested new password is not legal
	ResultSameAsPreviousValue = 62,			// new value is the same as the old one ( secret question and answer )
	ResultAccountLogonDenied = 63,			// account login denied due to 2nd factor authentication failure
	ResultCannotUseOldPassword = 64,			// The requested new password is not legal
	ResultInvalidLoginAuthCode = 65,			// account login denied due to auth code invalid
	ResultAccountLogonDeniedNoMail = 66,		// account login denied due to 2nd factor auth failure - and no mail has been sent
	ResultHardwareNotCapableOfIPT = 67,		// 
	ResultIPTInitError = 68,					// 
	ResultParentalControlRestricted = 69,	// operation failed due to parental control restrictions for current user
	ResultFacebookQueryError = 70,			// Facebook query returned an error
	ResultExpiredLoginAuthCode = 71,			// account login denied due to auth code expired
	ResultIPLoginRestrictionFailed = 72,
	ResultAccountLockedDown = 73,
	ResultAccountLogonDeniedVerifiedEmailRequired = 74,
	ResultNoMatchingURL = 75,
	ResultBadResponse = 76,					// parse failure, missing field, etc.
	ResultRequirePasswordReEntry = 77,		// The user cannot complete the action until they re-enter their password
	ResultValueOutOfRange = 78,				// the value entered is outside the acceptable range
	ResultUnexpectedError = 79,				// something happened that we didn't expect to ever happen
	ResultDisabled = 80,						// The requested service has been configured to be unavailable
	ResultInvalidCEGSubmission = 81,			// The set of files submitted to the CEG server are not valid !
	ResultRestrictedDevice = 82,				// The device being used is not allowed to perform this action
	ResultRegionLocked = 83,					// The action could not be complete because it is region restricted
	ResultRateLimitExceeded = 84,			// Temporary rate limit exceeded, try again later, different from ResultLimitExceeded which may be permanent
	ResultAccountLoginDeniedNeedTwoFactor = 85,	// Need two-factor code to login
	ResultItemDeleted = 86,					// The thing we're trying to access has been deleted
	ResultAccountLoginDeniedThrottle = 87,	// login attempt failed, try to throttle response to possible attacker
	ResultTwoFactorCodeMismatch = 88,		// two factor code mismatch
	ResultTwoFactorActivationCodeMismatch = 89,	// activation code for two-factor didn't match
	ResultAccountAssociatedToMultiplePartners = 90,	// account has been associated with multiple partners
	ResultNotModified = 91,					// data not modified
	ResultNoMobileDevice = 92,				// the account does not have a mobile device associated with it
	ResultTimeNotSynced = 93,				// the time presented is out of range or tolerance
	ResultSmsCodeFailed = 94,				// SMS code failure (no match, none pending, etc.)
	ResultAccountLimitExceeded = 95,			// Too many accounts access this resource
	ResultAccountActivityLimitExceeded = 96,	// Too many changes to this account
	ResultPhoneActivityLimitExceeded = 97,	// Too many changes to this phone
	ResultRefundToWallet = 98,				// Cannot refund to payment method, must use wallet
	ResultEmailSendFailure = 99,				// Cannot send an email
	ResultNotSettled = 100,					// Can't perform operation till payment has settled
	ResultNeedCaptcha = 101,					// Needs to provide a valid captcha
	ResultGSLTDenied = 102,					// a game server login token owned by this token's owner has been banned
	ResultGSOwnerDenied = 103,				// game server owner is denied for other reason (account lock, community ban, vac ban, missing phone)
	ResultInvalidItemType = 104,				// the type of thing we were requested to act on is invalid
	ResultIPBanned = 105,					// the ip address has been banned from taking this action
	ResultGSLTExpired = 106,					// this token has expired from disuse; can be reset for use
	ResultInsufficientFunds = 107,			// user doesn't have enough wallet funds to complete the action
	ResultTooManyPending = 108,				// There are too many of this thing pending already
	ResultNoSiteLicensesFound = 109,			// No site licenses found
	ResultWGNetworkSendExceeded = 110,		// the WG couldn't send a response because we exceeded max network send size
	ResultAccountNotFriends = 111,			// the user is not mutually friends
	ResultLimitedUserAccount = 112,			// the user is limited
	ResultCantRemoveItem = 113,				// item can't be removed
	ResultAccountDeleted = 114,				// account has been deleted
	ResultExistingUserCancelledLicense = 115,	// A license for this already exists, but cancelled
	ResultCommunityCooldown = 116,			// access is denied because of a community cooldown (probably from support profile data resets)
	ResultNoLauncherSpecified = 117,			// No launcher was specified, but a launcher was needed to choose correct realm for operation.
	ResultMustAgreeToSSA = 118,				// User must agree to china SSA or global SSA before login
	ResultLauncherMigrated = 119,			// The specified launcher type is no longer supported; the user should be directed elsewhere
	ResultSteamRealmMismatch = 120,			// The user's realm does not match the realm of the requested resource
	ResultInvalidSignature = 121,			// signature check did not match
	ResultParseFailure = 122,				// Failed to parse input
	ResultNoVerifiedPhone = 123,				// account does not have a verified phone number
};








UENUM(BlueprintType)
enum class ESMatchType : uint8 {
	MT_MatchMakingSession       UMETA(DisplayName="Matchmaking Session"),
	MT_Lobby					UMETA(DisplayName="Lobby Session"),
};



UENUM(BlueprintType)
enum ESIKAttributeType
{
	String,
	Bool,
	Integer
};

USTRUCT(BlueprintType)
struct FSIKAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIKAttributeType> AttributeType = ESIKAttributeType::String;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	FString StringValue = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	bool BoolValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 IntValue = 0;
	
	FSIKAttribute()
	{
		AttributeType = ESIKAttributeType::String;
		StringValue = "";
		BoolValue = false;
		IntValue = 0;
	}
	FVariantData GetVariantData() const
	{
		FVariantData VariantData;
		switch (AttributeType)
		{
		case ESIKAttributeType::String:
			VariantData.SetValue(StringValue);
			break;
		case ESIKAttributeType::Bool:
			VariantData.SetValue(BoolValue);
			break;
		case ESIKAttributeType::Integer:
			VariantData.SetValue(IntValue);
			break;
		default:
			VariantData.SetValue(StringValue);
			break;
		}
		return VariantData;
	}

	FSIKAttribute(FVariantData VariantData)
	{
		switch (VariantData.GetType())
		{
		case EOnlineKeyValuePairDataType::String:
			AttributeType = ESIKAttributeType::String;
			VariantData.GetValue(StringValue);
			break;
		case EOnlineKeyValuePairDataType::Bool:
			AttributeType = ESIKAttributeType::Bool;
			VariantData.GetValue(BoolValue);
			break;
		case EOnlineKeyValuePairDataType::Int32:
			AttributeType = ESIKAttributeType::Integer;
			VariantData.GetValue(IntValue);
			break;
		default:
			AttributeType = ESIKAttributeType::String;
			VariantData.GetValue(StringValue);
			break;
		}
	}
};


USTRUCT(BlueprintType)
struct FSSessionFindStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="EOS Struct")
	FBlueprintSessionResult SessionResult = FBlueprintSessionResult();

	UPROPERTY(BlueprintReadWrite, Category="EOS Struct")
	TMap<FString, FSIKAttribute> SessionSettings = TMap<FString, FSIKAttribute>();

	UPROPERTY(BlueprintReadWrite, Category="EOS Struct")
	FString SessionName = FString();

	UPROPERTY(BlueprintReadWrite, Category="EOS Struct")
	int32 CurrentNumberOfPlayers = 0;

	UPROPERTY(BlueprintReadWrite, Category="EOS Struct")
	int32 MaxNumberOfPlayers = 0;

	UPROPERTY(BlueprintReadWrite, Category="EOS Struct")
	bool bIsDedicatedServer = false;
};

USTRUCT(BlueprintType)
struct FSIK_SteamId
{
	GENERATED_BODY()

	UPROPERTY()
	int64 Result = 0;

	CSteamID GetSteamID() const
	{
		CSteamID SteamID;
		SteamID.SetFromUint64(Result);
		return SteamID;
	}
	FSIK_SteamId()
	{
		Result = 0;
	}
	FSIK_SteamId(int64 SteamID)
	{
		Result = SteamID;
	}

	FSIK_SteamId(CSteamID SteamID)
	{
		Result = SteamID.ConvertToUint64();
	}

	FSIK_SteamId(FString SteamID)
	{
		Result = FCString::Atoi64(*SteamID);
	}

	CSteamID GetSteamID()
	{
		CSteamID SteamID;
		SteamID.SetFromUint64(Result);
		return SteamID;
	}
};


USTRUCT(BlueprintType)
struct FSIK_AuthTicket
{
	GENERATED_BODY()

	int32 Value = 0;

	FSIK_AuthTicket()
	{
		Value = 0;
	}

	FSIK_AuthTicket(HAuthTicket AuthTicket)
	{
		Value = AuthTicket;
	}

	HAuthTicket GetAuthTicket() const
	{
		return Value;
	}
	
};

UENUM()
enum ESIK_SteamIPType
{
	SteamIPTypeIPv4 = 0 UMETA(DisplayName = "IPv4"),
	SteamIPTypeIPv6 = 1 UMETA(DisplayName = "IPv6"),
};

USTRUCT(BlueprintType)
struct FSIK_FriendsGroupID
{
	GENERATED_BODY()

	int32 Value = 0;

	FSIK_FriendsGroupID()
	{
		Value = 0;
	}

	FSIK_FriendsGroupID(FriendsGroupID_t FriendsGroupID)
	{
		Value = FriendsGroupID;
	}

	FriendsGroupID_t GetFriendsGroupID() const
	{
		return Value;
	}
	
};


USTRUCT(BlueprintType)
struct FSIK_SteamIPAddress
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_SteamIPType> m_eType = ESIK_SteamIPType::SteamIPTypeIPv4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 m_unIPv4 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 m_ipv6Qword;

	FSIK_SteamIPAddress()
	{
		m_eType = ESIK_SteamIPType::SteamIPTypeIPv4;
		m_unIPv4 = 0;
		m_ipv6Qword = 0;
	}
	FSIK_SteamIPAddress(SteamIPAddress_t SteamIPAddress): m_ipv6Qword(0)
	{
		m_eType = (ESIK_SteamIPType)SteamIPAddress.m_eType;
		m_unIPv4 = SteamIPAddress.m_unIPv4;
	}
};


UENUM(BlueprintType)
enum ESIK_DenyReason
{
	DenyInvalid = 0 UMETA(DisplayName = "Invalid"),
	DenyInvalidVersion = 1 UMETA(DisplayName = "Invalid Version"),
	DenyGeneric = 2 UMETA(DisplayName = "Generic"),
	DenyNotLoggedOn = 3 UMETA(DisplayName = "Not Logged On"),
	DenyNoLicense = 4 UMETA(DisplayName = "No License"),
	DenyCheater = 5 UMETA(DisplayName = "Cheater"),
	DenyLoggedInElseWhere = 6 UMETA(DisplayName = "Logged In Elsewhere"),
	DenyUnknownText = 7 UMETA(DisplayName = "Unknown Text"),
	DenyIncompatibleAnticheat = 8 UMETA(DisplayName = "Incompatible Anticheat"),
	DenyMemoryCorruption = 9 UMETA(DisplayName = "Memory Corruption"),
	DenyIncompatibleSoftware = 10 UMETA(DisplayName = "Incompatible Software"),
	DenySteamConnectionLost = 11 UMETA(DisplayName = "Steam Connection Lost"),
	DenySteamConnectionError = 12 UMETA(DisplayName = "Steam Connection Error"),
	DenySteamResponseTimedOut = 13 UMETA(DisplayName = "Steam Response Timed Out"),
	DenySteamValidationStalled = 14 UMETA(DisplayName = "Steam Validation Stalled"),
	DenySteamOwnerLeftGuestUser = 15 UMETA(DisplayName = "Steam Owner Left Guest User"),
};

UENUM(BlueprintType)
enum ESIK_SteamPartyBeaconLocationType
{
	SteamPartyBeaconLocationType_Invalid = 0 UMETA(DisplayName = "Invalid"),
	SteamPartyBeaconLocationType_ChatGroup = 1 UMETA(DisplayName = "Chat Group"),
	SteamPartyBeaconLocationType_Max = 2 UMETA(DisplayName = "Max"),
};

USTRUCT(BlueprintType)
struct FSIK_SteamPartyBeaconLocation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_SteamPartyBeaconLocationType> m_eType = ESIK_SteamPartyBeaconLocationType::SteamPartyBeaconLocationType_Invalid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 m_ulLocationID = 0;

	FSIK_SteamPartyBeaconLocation()
	{
		m_eType = ESIK_SteamPartyBeaconLocationType::SteamPartyBeaconLocationType_Invalid;
		m_ulLocationID = 0;
	}

	FSIK_SteamPartyBeaconLocation(SteamPartyBeaconLocation_t SteamPartyBeaconLocation)
	{
		m_eType = (ESIK_SteamPartyBeaconLocationType)SteamPartyBeaconLocation.m_eType;
		m_ulLocationID = SteamPartyBeaconLocation.m_ulLocationID;
	}

	SteamPartyBeaconLocation_t GetSteamPartyBeaconLocation() const
	{
		SteamPartyBeaconLocation_t SteamPartyBeaconLocation;
		SteamPartyBeaconLocation.m_eType = static_cast<ESteamPartyBeaconLocationType>(m_eType.GetValue());
		SteamPartyBeaconLocation.m_ulLocationID = m_ulLocationID;
		return SteamPartyBeaconLocation;
	}
};

UENUM(BlueprintType)
enum ESIK_LobbyDistanceFilter
{
	LobbyDistanceFilterClose = 0 UMETA(DisplayName = "Close"),
	LobbyDistanceFilterDefault = 1 UMETA(DisplayName = "Default"),
	LobbyDistanceFilterFar = 2 UMETA(DisplayName = "Far"),
	LobbyDistanceFilterWorldwide = 3 UMETA(DisplayName = "Worldwide"),
};

UENUM(BlueprintType)
enum ESIK_LobbyComparisonType
{
	LobbyComparisonEqualToOrLessThan = 0 UMETA(DisplayName = "Equal To Or Less Than"),
	LobbyComparisonLessThan = 1 UMETA(DisplayName = "Less Than"),
	LobbyComparisonEqualTo = 2 UMETA(DisplayName = "Equal To"),
	LobbyComparisonGreaterThan = 3 UMETA(DisplayName = "Greater Than"),
	LobbyComparisonEqualToOrGreaterThan = 4 UMETA(DisplayName = "Equal To Or Greater Than"),
	LobbyComparisonNotEqualTo = 5 UMETA(DisplayName = "Not Equal To"),
};

UENUM(BlueprintType)
enum ESIK_LobbyType
{
	LobbyTypePrivate = 0 UMETA(DisplayName = "Private"),
	LobbyTypeFriendsOnly = 1 UMETA(DisplayName = "Friends Only"),
	LobbyTypePublic = 2 UMETA(DisplayName = "Public"),
	LobbyTypeInvisible = 3 UMETA(DisplayName = "Invisible"),
};

UENUM(BlueprintType)
enum ESIK_LobbyChatEntryType
{
	ChatEntryTypeInvalid = 0 UMETA(DisplayName = "Invalid"),
	ChatEntryTypeChatMsg = 1 UMETA(DisplayName = "Chat Message"),
	ChatEntryTypeTyping = 2 UMETA(DisplayName = "Typing"),
	ChatEntryTypeInviteGame = 3 UMETA(DisplayName = "Invite Game"),
	ChatEntryTypeEmote = 4 UMETA(DisplayName = "Emote"),
	ChatEntryTypeLeftConversation = 6 UMETA(DisplayName = "Left Conversation"),
	ChatEntryTypeEntered = 7 UMETA(DisplayName = "Entered"),
	ChatEntryTypeWasKicked = 8 UMETA(DisplayName = "Was Kicked"),
	ChatEntryTypeWasBanned = 9 UMETA(DisplayName = "Was Banned"),
	ChatEntryTypeDisconnected = 10 UMETA(DisplayName = "Disconnected"),
	ChatEntryTypeHistoricalChat = 11 UMETA(DisplayName = "Historical Chat"),
	ChatEntryTypeLinkBlocked = 14 UMETA(DisplayName = "Link Blocked"),
};

UENUM(BlueprintType)
enum ESIK_ChatRoomEnterResponse
{
	None = 0 UMETA(DisplayName = "None"),
	ChatRoomEnterResponseSuccess = 1 UMETA(DisplayName = "Success"),
	ChatRoomEnterResponseDoesntExist = 2 UMETA(DisplayName = "Doesn't Exist"),
	ChatRoomEnterResponseNotAllowed = 3 UMETA(DisplayName = "Not Allowed"),
	ChatRoomEnterResponseFull = 4 UMETA(DisplayName = "Full"),
	ChatRoomEnterResponseError = 5 UMETA(DisplayName = "Error"),
	ChatRoomEnterResponseBanned = 6 UMETA(DisplayName = "Banned"),
	ChatRoomEnterResponseLimited = 7 UMETA(DisplayName = "Limited"),
	ChatRoomEnterResponseClanDisabled = 8 UMETA(DisplayName = "Clan Disabled"),
	ChatRoomEnterResponseCommunityBan = 9 UMETA(DisplayName = "Community Ban"),
	ChatRoomEnterResponseMemberBlockedYou = 10 UMETA(DisplayName = "Member Blocked You"),
	ChatRoomEnterResponseYouBlockedMember = 11 UMETA(DisplayName = "You Blocked Member"),
	ChatRoomEnterResponseRatelimitExceeded = 15 UMETA(DisplayName = "Ratelimit Exceeded"),
};

UENUM(BlueprintType)
enum ESIK_LobbyChatMemberStateChange
{
	ChatMemberStateChangeEntered = 0 UMETA(DisplayName = "Entered"),
	ChatMemberStateChangeLeft = 1 UMETA(DisplayName = "Left"),
	ChatMemberStateChangeDisconnected = 2 UMETA(DisplayName = "Disconnected"),
	ChatMemberStateChangeKicked = 3 UMETA(DisplayName = "Kicked"),
	ChatMemberStateChangeBanned = 4 UMETA(DisplayName = "Banned"),
};

USTRUCT(BlueprintType)
struct FSIK_SessionFindSettings
{
	GENERATED_BODY()

	
	
};

USTRUCT(BlueprintType)
struct FSIK_ServerNetAddress
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 QueryPort = 0;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 ConnectionPort = 0;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString IP = "";

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString ConnectionAddress = "";

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString QueryAddress = "";

	FSIK_ServerNetAddress()
	{
		QueryPort = 0;
	}
	FSIK_ServerNetAddress(servernetadr_t ServerNetAddress)
	{
		QueryPort = ServerNetAddress.GetQueryPort();
		ConnectionPort = ServerNetAddress.GetConnectionPort();
		IP = FIPv4Address(ServerNetAddress.GetIP()).ToString();
		ConnectionAddress = ServerNetAddress.GetConnectionAddressString();
		QueryAddress = ServerNetAddress.GetQueryAddressString();
	}
};
USTRUCT(BlueprintType)
struct FSIK_FoundServers
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 Ping = 0;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bHadSuccessfulResponse = false;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bDoNotRefresh = false;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString GameDir = "";

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString Map = "";

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString GameDescription = "";

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FSIK_AppId AppID = 0;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 Players;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 MaxPlayers;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 BotPlayers;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bPasswordProtected;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	bool bSecure;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 TimeLastPlayed;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	int32 ServerVersion;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString ServerName;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FString GameTags;

	UPROPERTY(BlueprintReadWrite, Category="Steam Integration Kit")
	FSIK_ServerNetAddress ServerNetAddress;

	FSIK_FoundServers()
	{
		Ping = 0;
		bHadSuccessfulResponse = false;
		bDoNotRefresh = false;
		GameDir = "";
		Map = "";
		GameDescription = "";
		AppID = 0;
		Players = 0;
		MaxPlayers = 0;
		BotPlayers = 0;
		bPasswordProtected = false;
		bSecure = false;
		TimeLastPlayed = 0;
		ServerVersion = 0;
		ServerName = "";
		GameTags = "";
	}

	FSIK_FoundServers(gameserveritem_t ServerItem)
	{
		Ping = ServerItem.m_nPing;
		bHadSuccessfulResponse = ServerItem.m_bHadSuccessfulResponse;
		bDoNotRefresh = ServerItem.m_bDoNotRefresh;
		GameDir = ServerItem.m_szGameDir;
		Map = ServerItem.m_szMap;
		GameDescription = ServerItem.m_szGameDescription;
		AppID = ServerItem.m_nAppID;
		Players = ServerItem.m_nPlayers;
		MaxPlayers = ServerItem.m_nMaxPlayers;
		BotPlayers = Players - ServerItem.m_nPlayers;
		bPasswordProtected = ServerItem.m_bPassword;
		bSecure = ServerItem.m_bSecure;
		TimeLastPlayed = ServerItem.m_ulTimeLastPlayed;
		ServerVersion = ServerItem.m_nServerVersion;
		ServerName = ServerItem.GetName();
		GameTags = ServerItem.m_szGameTags;
	}
};

UENUM(BlueprintType)
enum ESIK_MatchMakingServerResponse
{
	ServerResponded = 0 UMETA(DisplayName = "Server Responded"),
	ServerFailedToRespond = 1 UMETA(DisplayName = "Server Failed To Respond"),
	NoServersListedOnMasterServer = 2 UMETA(DisplayName = "No Servers Listed On Master Server"),
};

UENUM(BlueprintType)
enum ESIK_SteamNetworkingIdentityType
{
	SteamNetworkingIdentityType_Invalid = 0 UMETA(DisplayName = "Invalid"),
	SteamNetworkingIdentityType_SteamID = 16 UMETA(DisplayName = "SteamID"),
	SteamNetworkingIdentityType_IPAddress = 1 UMETA(DisplayName = "IP Address"),
	SteamNetworkingIdentityType_GenericString = 2 UMETA(DisplayName = "Generic String"),
	SteamNetworkingIdentityType_GenericBytes = 3 UMETA(DisplayName = "Generic Bytes"),
	SteamNetworkingIdentityType_InvalidString = 4 UMETA(DisplayName = "Invalid String"),
	SteamNetworkingIdentityType__Force32bit = 0x7fffffff UMETA(DisplayName = "Force 32bit"),
	SteamNetworkingIdentityType_XboxPairwiseID = 18 UMETA(DisplayName = "Xbox Pairwise ID"),
	SteamNetworkingIdentityType_SonyPSN = 19 UMETA(DisplayName = "Sony PSN"),
};

USTRUCT(BlueprintType)
struct FSIK_SteamNetworkingIPAddr
{

	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_SteamIPType> m_eType = ESIK_SteamIPType::SteamIPTypeIPv4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	FString IpV4 = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	FString IpV6 = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 m_port = 0;
	
	FSIK_SteamNetworkingIPAddr()
	{
		m_eType = ESIK_SteamIPType::SteamIPTypeIPv4;
		IpV4 = "";
		IpV6 = "";
		m_port = 0;
	}
	FSIK_SteamNetworkingIPAddr(SteamNetworkingIPAddr SteamNetworkingIPAddr)
	{
		
		if(SteamNetworkingIPAddr.IsIPv4())
		{
			m_eType = ESIK_SteamIPType::SteamIPTypeIPv4;
			FIPv4Address IPv4Address = SteamNetworkingIPAddr.GetIPv4();
			IpV4 = IPv4Address.ToString();
		}
		else
		{
			m_eType = ESIK_SteamIPType::SteamIPTypeIPv6;
		}
		m_port = SteamNetworkingIPAddr.m_port;
	};
};



USTRUCT(BlueprintType)
struct FSIK_SteamNetworkingIdentity 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_SteamNetworkingIdentityType> m_eType = ESIK_SteamNetworkingIdentityType::SteamNetworkingIdentityType_Invalid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_SteamId m_steamID = FSIK_SteamId();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	FString m_szGenericString = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	TArray<uint8> m_szGenericBytes = TArray<uint8>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_SteamNetworkingIPAddr m_ipAddress = FSIK_SteamNetworkingIPAddr();
	

	FSIK_SteamNetworkingIdentity()
	{
		m_eType = ESIK_SteamNetworkingIdentityType::SteamNetworkingIdentityType_Invalid;
		m_steamID = FSIK_SteamId();
		m_szGenericString = "";
		m_szGenericBytes = TArray<uint8>();
		m_ipAddress = FSIK_SteamNetworkingIPAddr();
	}
	FSIK_SteamNetworkingIdentity(SteamNetworkingIdentity SteamNetworkingIdentity)
	{
		m_eType = static_cast<ESIK_SteamNetworkingIdentityType>(SteamNetworkingIdentity.m_eType);
		switch (m_eType)
		{
		case SteamNetworkingIdentityType_Invalid:
			break;
		case SteamNetworkingIdentityType_SteamID:
			m_steamID = SteamNetworkingIdentity.GetSteamID();
			break;
		case SteamNetworkingIdentityType_IPAddress:
			m_ipAddress = SteamNetworkingIdentity.m_ip;
			break;
		case SteamNetworkingIdentityType_GenericString:
			m_szGenericString = SteamNetworkingIdentity.m_szGenericString;
			break;
		case SteamNetworkingIdentityType_GenericBytes:
			for (int i = 0; i < SteamNetworkingIdentity.m_cbSize; i++)
			{
				m_szGenericBytes.Add(SteamNetworkingIdentity.m_genericBytes[i]);
			}
			break;
		case SteamNetworkingIdentityType_InvalidString:
			break;
		case SteamNetworkingIdentityType__Force32bit:
			break;
		case SteamNetworkingIdentityType_XboxPairwiseID:
			break;
		case SteamNetworkingIdentityType_SonyPSN:
			break;
		default: ;
		}

	}

	SteamNetworkingIdentity GetSteamNetworkingIdentity()
	{
		SteamNetworkingIdentity SteamNetworkingIdentity;
		SteamNetworkingIdentity.m_eType = static_cast<ESteamNetworkingIdentityType>(m_eType.GetValue());
		switch (m_eType)
		{
		case SteamNetworkingIdentityType_Invalid:
			break;
		case SteamNetworkingIdentityType_SteamID:
			SteamNetworkingIdentity.SetSteamID(m_steamID.GetSteamID());
			break;
		case SteamNetworkingIdentityType_IPAddress:
			{
				FIPv4Address IPv4Address = FIPv4Address();
				IPv4Address.Parse(m_ipAddress.IpV4, IPv4Address);
				SteamNetworkingIdentity.m_ip.SetIPv4(IPv4Address.Value,m_ipAddress.m_port);
			}
			break;
		case SteamNetworkingIdentityType_GenericString:
			char buf[1024];
			FCStringAnsi::Strcpy(buf, TCHAR_TO_ANSI(*m_szGenericString));
			SteamNetworkingIdentity.SetGenericString(buf);
			break;
		case SteamNetworkingIdentityType_GenericBytes:
			SteamNetworkingIdentity.SetGenericBytes(m_szGenericBytes.GetData(), m_szGenericBytes.Num());
			break;
		default:
			;
		}
		return SteamNetworkingIdentity;
	}
	
};

UENUM(BlueprintType)
enum ESIK_NotificationPosition
{
	PositionTopLeft = 0 UMETA(DisplayName = "Top Left"),
	PositionTopRight = 1 UMETA(DisplayName = "Top Right"),
	PositionBottomLeft = 2 UMETA(DisplayName = "Bottom Left"),
	PositionBottomRight = 3 UMETA(DisplayName = "Bottom Right"),
};

UENUM(BlueprintType)
enum ESIK_SteamItemFlags
{
	SteamItemFlagsNoTrade = 0  UMETA(DisplayName = "No Trade"),
	SteamItemFlagsRemoved = 1 UMETA(DisplayName = "Removed"),
	SteamItemFlagsConsumed = 2 UMETA(DisplayName = "Consumed"),
};

USTRUCT(BlueprintType)
struct FSIK_SteamInventoryResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 Result = 0;

	FSIK_SteamInventoryResult()
	{
		Result = 0;
	}
	FSIK_SteamInventoryResult(SteamInventoryResult_t SteamInventoryResult)
	{
		Result = SteamInventoryResult;
	}
	SteamInventoryResult_t GetSteamInventoryResult() const
	{
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FSIK_SteamItemDef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 Result = 0;

	FSIK_SteamItemDef()
	{
		Result = 0;
	}
	FSIK_SteamItemDef(SteamItemDef_t SteamItemDef)
	{
		Result = SteamItemDef;
	}
	SteamItemDef_t GetSteamItemDef() const
	{
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FSIK_SteamItemInstanceID
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 Result = 0;

	FSIK_SteamItemInstanceID()
	{
		Result = 0;
	}
	FSIK_SteamItemInstanceID(SteamItemInstanceID_t SteamItemInstanceID)
	{
		Result = SteamItemInstanceID;
	}
	SteamItemInstanceID_t GetSteamItemInstanceID() const
	{
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FSIK_SteamInventoryUpdateHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 Result = 0;

	FSIK_SteamInventoryUpdateHandle()
	{
		Result = 0;
	}
	FSIK_SteamInventoryUpdateHandle(SteamInventoryUpdateHandle_t SteamInventoryUpdateHandle)
	{
		Result = SteamInventoryUpdateHandle;
	}
	SteamInventoryUpdateHandle_t GetSteamInventoryUpdateHandle() const
	{
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FSIK_SteamItemDetails
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_SteamItemInstanceID ItemID = FSIK_SteamItemInstanceID();

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_SteamItemDef Definition = FSIK_SteamItemDef();

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_SteamItemFlags> Flags = TEnumAsByte<ESIK_SteamItemFlags>();

	FSIK_SteamItemDetails()
	{
		ItemID = FSIK_SteamItemInstanceID();
		Definition = FSIK_SteamItemDef();
		Quantity = 0;
		Flags = TEnumAsByte<ESIK_SteamItemFlags>();
	}
	FSIK_SteamItemDetails(SteamItemDetails_t SteamItemDetails)
	{
		ItemID = SteamItemDetails.m_itemId;
		Definition = SteamItemDetails.m_iDefinition;
		Quantity = SteamItemDetails.m_unQuantity;
		Flags = static_cast<ESIK_SteamItemFlags>(SteamItemDetails.m_unFlags);
	}
};

UENUM(BlueprintType)
enum ESIK_AudioPlayback_Status
{
	Playback_Undefined = 0 UMETA(DisplayName = "Undefined"),
	Playback_Playing = 1 UMETA(DisplayName = "Playing"),
	Playback_Paused = 2 UMETA(DisplayName = "Paused"),
	Playback_Idle = 3 UMETA(DisplayName = "Idle"),
};

UENUM(BlueprintType)
enum ESIK_SteamNetworkingAvailability
{
	SteamNetworkingAvailability_CannotTry = -102 UMETA(DisplayName = "Cannot Try"),
	SteamNetworkingAvailability_Failed = -101 UMETA(DisplayName = "Failed"),
	SteamNetworkingAvailability_Previously = -100 UMETA(DisplayName = "Previously"),
	SteamNetworkingAvailability_Retrying = -10 UMETA(DisplayName = "Retrying"),
	SteamNetworkingAvailability_NeverTried = 1 UMETA(DisplayName = "Never Tried"),
	SteamNetworkingAvailability_Waiting = 2 UMETA(DisplayName = "Waiting"),
	SteamNetworkingAvailability_Attempting = 3 UMETA(DisplayName = "Attempting"),
	SteamNetworkingAvailability_Current = 100 UMETA(DisplayName = "Current"),
	SteamNetworkingAvailability_Unknown = 0 UMETA(DisplayName = "Unknown"),
	SteamNetworkingAvailability__Force32bit = 0x7fffffff UMETA(DisplayName = "Force 32bit"),
};

USTRUCT(BlueprintType)
struct FSIK_SteamNetworkPingLocation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	TArray<uint8> Data = TArray<uint8>();

	FSIK_SteamNetworkPingLocation()
	{
		Data = TArray<uint8>();
	}
	FSIK_SteamNetworkPingLocation(SteamNetworkPingLocation_t SteamNetworkPingLocation)
	{
		Data = TArray<uint8>();
		for (int i = 0; i < 512; i++)
		{
			Data.Add(SteamNetworkPingLocation.m_data[i]);
		}
	}
	SteamNetworkPingLocation_t GetSteamNetworkPingLocation() const
	{
		SteamNetworkPingLocation_t SteamNetworkPingLocation;
		for (int i = 0; i < 512; i++)
		{
			SteamNetworkPingLocation.m_data[i] = Data[i];
		}
		return SteamNetworkPingLocation;
	}
};

USTRUCT(BlueprintType)
struct FSIK_SteamNetworkingPOPID
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 Value = 0;

	FSIK_SteamNetworkingPOPID()
	{
		Value = 0;
	}
	FSIK_SteamNetworkingPOPID(SteamNetworkingPOPID SteamNetworkingPOPID)
	{
		Value = SteamNetworkingPOPID;
	}
	SteamNetworkingPOPID GetSteamNetworkingPOPID() const
	{
		return Value;
	}
};

UENUM(BlueprintType)
enum ESIK_P2PSessionError
{
	P2PSessionErrorNone = 0 UMETA(DisplayName = "None"),
	P2PSessionErrorNotRunningApp = 1 UMETA(DisplayName = "Not Running App"),
	P2PSessionErrorNoRightsToApp = 2 UMETA(DisplayName = "No Rights To App"),
	P2PSessionErrorDestinationNotLoggedIn = 3 UMETA(DisplayName = "Destination Not Logged In"),
	P2PSessionErrorTimeout = 4 UMETA(DisplayName = "Timeout"),
	P2PSessionErrorMax = 5 UMETA(DisplayName = "Max"),
};

USTRUCT(BlueprintType)
struct FSIK_P2PSessionState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	bool bConnectionActive = false;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	bool bConnecting = false;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_P2PSessionError> P2PSessionError = ESIK_P2PSessionError::P2PSessionErrorNone;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	bool bUsingRelay = false;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 BytesQueuedForSend = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 PacketsQueuedForSend = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FString RemoteIP = "";

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 RemotePort = 0;
	
	
	FSIK_P2PSessionState()
	{
		bConnectionActive = false;
		bConnecting = false;
		P2PSessionError = ESIK_P2PSessionError::P2PSessionErrorNone;
		bUsingRelay = false;
		BytesQueuedForSend = 0;
		PacketsQueuedForSend = 0;
		RemoteIP = "";
		RemotePort = 0;
	}
	FSIK_P2PSessionState(P2PSessionState_t P2PSessionState)
	{
		bConnectionActive = P2PSessionState.m_bConnectionActive != 0;
		bConnecting = P2PSessionState.m_bConnecting != 0;
		P2PSessionError = static_cast<ESIK_P2PSessionError>(P2PSessionState.m_eP2PSessionError);
		bUsingRelay = P2PSessionState.m_bUsingRelay != 0;
		BytesQueuedForSend = P2PSessionState.m_nBytesQueuedForSend;
		PacketsQueuedForSend = P2PSessionState.m_nPacketsQueuedForSend;
		RemoteIP = FIPv4Address(P2PSessionState.m_nRemoteIP).ToString();
		RemotePort = P2PSessionState.m_nRemotePort;
	}

	P2PSessionState_t GetP2PSessionState() const
	{
		P2PSessionState_t P2PSessionState;
		P2PSessionState.m_bConnectionActive = bConnectionActive;
		P2PSessionState.m_bConnecting = bConnecting;
		P2PSessionState.m_eP2PSessionError = static_cast<ESteamNetworkingConnectionState>(P2PSessionError.GetValue());
		P2PSessionState.m_bUsingRelay = bUsingRelay;
		P2PSessionState.m_nBytesQueuedForSend = BytesQueuedForSend;
		P2PSessionState.m_nPacketsQueuedForSend = PacketsQueuedForSend;
		FIPv4Address IPv4Address = FIPv4Address();
		IPv4Address.Parse(RemoteIP, IPv4Address);
		P2PSessionState.m_nRemoteIP = IPv4Address.Value;
		P2PSessionState.m_nRemotePort = RemotePort;
		return P2PSessionState;
	}
	
};

UENUM(BlueprintType)
enum ESIK_P2PSend
{
	P2PSendUnreliable = 0 UMETA(DisplayName = "Unreliable"),
	P2PSendUnreliableNoDelay = 1 UMETA(DisplayName = "Unreliable No Delay"),
	P2PSendReliable = 2 UMETA(DisplayName = "Reliable"),
	P2PSendReliableWithBuffering = 3 UMETA(DisplayName = "Reliable With Buffering"),
};

USTRUCT(BlueprintType)
struct FSIK_PublishedFileId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 PublishedFileId = 0;

	FSIK_PublishedFileId()
	{
		PublishedFileId = 0;
	}

	FSIK_PublishedFileId(PublishedFileId_t Input)
	{
		PublishedFileId = Input;
	}

	PublishedFileId_t GetPublishedFileId() const
	{
		return PublishedFileId;
	}
};


USTRUCT(BlueprintType)
struct FSIK_PublishedFileUpdateHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 PublishedFileUpdateHandle = 0;

	FSIK_PublishedFileUpdateHandle()
	{
		PublishedFileUpdateHandle = 0;
	}

	FSIK_PublishedFileUpdateHandle(PublishedFileUpdateHandle_t Input)
	{
		PublishedFileUpdateHandle = Input;
	}

	PublishedFileUpdateHandle_t GetPublishedFileUpdateHandle() const
	{
		return PublishedFileUpdateHandle;
	}
};

USTRUCT(BlueprintType)
struct FSIK_UGCFileWriteStreamHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 UGCFileWriteStreamHandle = 0;

	FSIK_UGCFileWriteStreamHandle()
	{
		UGCFileWriteStreamHandle = 0;
	}

	FSIK_UGCFileWriteStreamHandle(UGCFileWriteStreamHandle_t Input)
	{
		UGCFileWriteStreamHandle = Input;
	}

	UGCFileWriteStreamHandle_t GetUGCFileWriteStreamHandle() const
	{
		return UGCFileWriteStreamHandle;
	}
};

USTRUCT(BlueprintType)
struct FSIK_UGCHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 UGCHandle = 0;

	FSIK_UGCHandle()
	{
		UGCHandle = 0;
	}

	FSIK_UGCHandle(UGCHandle_t Input)
	{
		UGCHandle = Input;
	}

	UGCHandle_t GetUGCHandle() const
	{
		return UGCHandle;
	}
};

UENUM(BlueprintType)
enum ESIK_RemoteStorageLocalFileChange
{
	RemoteStorageLocalFileChange_Invalid = 0 UMETA(DisplayName = "Invalid"),
	RemoteStorageLocalFileChange_FileUpdated = 1 UMETA(DisplayName = "File Updated"),
	RemoteStorageLocalFileChange_FileDeleted = 2 UMETA(DisplayName = "File Deleted"),
};

UENUM(BlueprintType)
enum ESIK_RemoteStorageFilePathType
{
	RemoteStorageFilePathType_Invalid = 0 UMETA(DisplayName = "Invalid"),
	RemoteStorageFilePathType_Absolute = 1 UMETA(DisplayName = "Absolute"),
	RemoteStorageFilePathType_APIFilename = 2 UMETA(DisplayName = "API Filename"),
};

UENUM(BlueprintType)
enum ESIK_RemoteStoragePlatform
{
	RemoteStoragePlatformNone = 0 UMETA(DisplayName = "None"),
	RemoteStoragePlatformWindows = 1 UMETA(DisplayName = "Windows"),
	RemoteStoragePlatformOSX = 2 UMETA(DisplayName = "Mac OSX"),
	RemoteStoragePlatformPS3 = 4 UMETA(DisplayName = "PS3"),
	RemoteStoragePlatformLinux = 8 UMETA(DisplayName = "Linux"),
	RemoteStoragePlatformReserved2 = 16 UMETA(DisplayName = "Reserved2"),
	RemoteStoragePlatformAll = -1 UMETA(DisplayName = "All"),
};

UENUM(BlueprintType)
enum ESIK_RemoteStoragePublishedFileVisibility
{
	RemoteStoragePublishedFileVisibilityPublic = 0 UMETA(DisplayName = "Public"),
	RemoteStoragePublishedFileVisibilityFriendsOnly = 1 UMETA(DisplayName = "Friends Only"),
	RemoteStoragePublishedFileVisibilityPrivate = 2 UMETA(DisplayName = "Private"),
	ERemoteStoragePublishedFileVisibilityUnlisted = 3 UMETA(DisplayName = "Unlisted"),
};

UENUM(BlueprintType)
enum ESIK_UGCReadAction
{
	UGCRead_ContinueReadingUntilFinished = 0 UMETA(DisplayName = "Continue Reading Until Finished"),
	UGCRead_ContinueReading = 1 UMETA(DisplayName = "Continue Reading"),
	UGCRead_Close = 2 UMETA(DisplayName = "Close"),
};

UENUM(BlueprintType)
enum ESIK_WorkshopEnumerationType
{
	WorkshopEnumerationTypeRankedByVote = 0 UMETA(DisplayName = "Ranked By Vote"),
	WorkshopEnumerationTypeRecent = 1 UMETA(DisplayName = "Recent"),
	WorkshopEnumerationTypeTrending = 2 UMETA(DisplayName = "Trending"),
	WorkshopEnumerationTypeFavoritesOfFriends = 3 UMETA(DisplayName = "Favorites Of Friends"),
	WorkshopEnumerationTypeVotedByFriends = 4 UMETA(DisplayName = "Voted By Friends"),
	WorkshopEnumerationTypeContentByFriends = 5 UMETA(DisplayName = "Content By Friends"),
	WorkshopEnumerationTypeRecentFromFollowedUsers = 6 UMETA(DisplayName = "Recent From Followed Users"),
};


UENUM(BlueprintType)
enum ESIK_WorkshopFileType
{
	WorkshopFileTypeFirst = 0 UMETA(DisplayName = "First"),
	WorkshopFileTypeCommunity = 1 UMETA(DisplayName = "Community"),
	WorkshopFileTypeMicrotransaction = 2 UMETA(DisplayName = "Microtransaction"),
	WorkshopFileTypeCollection = 3 UMETA(DisplayName = "Collection"),
	WorkshopFileTypeArt = 4 UMETA(DisplayName = "Art"),
	WorkshopFileTypeVideo = 5 UMETA(DisplayName = "Video"),
	WorkshopFileTypeScreenshot = 6 UMETA(DisplayName = "Screenshot"),
	WorkshopFileTypeGame = 7 UMETA(DisplayName = "Game"),
	WorkshopFileTypeSoftware = 8 UMETA(DisplayName = "Software"),
	WorkshopFileTypeConcept = 9 UMETA(DisplayName = "Concept"),
	WorkshopFileTypeWebGuide = 10 UMETA(DisplayName = "Web Guide"),
	WorkshopFileTypeIntegratedGuide = 11 UMETA(DisplayName = "Integrated Guide"),
	WorkshopFileTypeMerch = 12 UMETA(DisplayName = "Merch"),
	WorkshopFileTypeControllerBinding = 13 UMETA(DisplayName = "Controller Binding"),
	WorkshopFileTypeSteamworksAccessInvite = 14 UMETA(DisplayName = "Steamworks Access Invite"),
	WorkshopFileTypeSteamVideo = 15 UMETA(DisplayName = "Steam Video"),
	WorkshopFileTypeGameManagedItem = 16 UMETA(DisplayName = "Game Managed Item"),
	WorkshopFileTypeMax = 17 UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum ESIK_VRScreenshotType
{
	VRScreenshotType_None = 0 UMETA(DisplayName = "None"),
	VRScreenshotType_Mono = 1 UMETA(DisplayName = "Mono"),
	VRScreenshotType_Stereo = 2 UMETA(DisplayName = "Stereo"),
	VRScreenshotType_MonoCubemap = 3 UMETA(DisplayName = "Mono Cubemap"),
	VRScreenshotType_MonoPanorama = 4 UMETA(DisplayName = "Mono Panorama"),
	VRScreenshotType_StereoPanorama = 5 UMETA(DisplayName = "Stereo Panorama"),
};

USTRUCT(BlueprintType)
struct FSIK_ScreenshotHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 Result;

	FSIK_ScreenshotHandle()
	{
		Result = 0;
	}
	FSIK_ScreenshotHandle(ScreenshotHandle ScreenshotHandle)
	{
		Result = ScreenshotHandle;
	}
	ScreenshotHandle GetScreenshotHandle() const
	{
		return Result;
	}	
};

UENUM(BlueprintType)
enum ESIK_ItemPreviewType
{
	ItemPreviewType_Image = 0 UMETA(DisplayName = "Image"),
	ItemPreviewType_YouTubeVideo = 1 UMETA(DisplayName = "YouTube Video"),
	ItemPreviewType_Sketchfab = 2 UMETA(DisplayName = "Sketchfab"),
	ItemPreviewType_EnvironmentMap_HorizontalCross = 3 UMETA(DisplayName = "Environment Map Horizontal Cross"),
	ItemPreviewType_EnvironmentMap_LatLong = 4 UMETA(DisplayName = "Environment Map Lat Long"),
	ItemPreviewType_ReservedMax = 255 UMETA(DisplayName = "Reserved Max"),
};

UENUM(BlueprintType)
enum ESIK_ItemState
{
	ItemStateNone = 0 UMETA(DisplayName = "None"),
	ItemStateSubscribed = 1 UMETA(DisplayName = "Subscribed"),
	ItemStateLegacyItem = 2 UMETA(DisplayName = "Legacy Item"),
	ItemStateInstalled = 4 UMETA(DisplayName = "Installed"),
	ItemStateNeedsUpdate = 8 UMETA(DisplayName = "Needs Update"),
	ItemStateDownloading = 16 UMETA(DisplayName = "Downloading"),
	ItemStateDownloadPending = 32 UMETA(DisplayName = "Download Pending"),
};

UENUM(BlueprintType)
enum ESIK_ItemStatistic
{
	ItemStatistic_NumSubscriptions = 0 UMETA(DisplayName = "Num Subscriptions"),
	ItemStatistic_NumFavorites = 1 UMETA(DisplayName = "Num Favorites"),
	ItemStatistic_NumFollowers = 2 UMETA(DisplayName = "Num Followers"),
	ItemStatistic_NumUniqueSubscriptions = 3 UMETA(DisplayName = "Num Unique Subscriptions"),
	ItemStatistic_NumUniqueFavorites = 4 UMETA(DisplayName = "Num Unique Favorites"),
	ItemStatistic_NumUniqueFollowers = 5 UMETA(DisplayName = "Num Unique Followers"),
	ItemStatistic_NumUniqueWebsiteViews = 6 UMETA(DisplayName = "Num Unique Website Views"),
	ItemStatistic_ReportScore = 7 UMETA(DisplayName = "Report Score"),
	ItemStatistic_NumSecondsPlayed = 8 UMETA(DisplayName = "Num Seconds Played"),
	ItemStatistic_NumPlaytimeSessions = 9 UMETA(DisplayName = "Num Playtime Sessions"),
	ItemStatistic_NumComments = 10 UMETA(DisplayName = "Num Comments"),
	ItemStatistic_NumSecondsPlayedDuringTimePeriod = 11 UMETA(DisplayName = "Num Seconds Played During Time Period"),
	ItemStatistic_NumPlaytimeSessionsDuringTimePeriod = 12 UMETA(DisplayName = "Num Playtime Sessions During Time Period"),
};

UENUM(BlueprintType)
enum ESIK_ItemUpdateStatus
{
	ItemUpdateStatusInvalid = 0 UMETA(DisplayName = "Invalid"),
	ItemUpdateStatusPreparingConfig = 1 UMETA(DisplayName = "Preparing Config"),
	ItemUpdateStatusPreparingContent = 2 UMETA(DisplayName = "Preparing Content"),
	ItemUpdateStatusUploadingContent = 3 UMETA(DisplayName = "Uploading Content"),
	ItemUpdateStatusUploadingPreviewFile = 4 UMETA(DisplayName = "Uploading Preview File"),
	ItemUpdateStatusCommittingChanges = 5 UMETA(DisplayName = "Committing Changes"),
};

UENUM(BlueprintType)
enum ESIK_UGCMatchingUGCType
{
	UGCMatchingUGCType_Items = 0 UMETA(DisplayName = "Items"),
	UGCMatchingUGCType_Items_Mtx = 1 UMETA(DisplayName = "Items Mtx"),
	UGCMatchingUGCType_Items_ReadyToUse = 2 UMETA(DisplayName = "Items Ready To Use"),
	UGCMatchingUGCType_Collections = 3 UMETA(DisplayName = "Collections"),
	UGCMatchingUGCType_Artwork = 4 UMETA(DisplayName = "Artwork"),
	UGCMatchingUGCType_Videos = 5 UMETA(DisplayName = "Videos"),
	UGCMatchingUGCType_Screenshots = 6 UMETA(DisplayName = "Screenshots"),
	UGCMatchingUGCType_AllGuides = 7 UMETA(DisplayName = "All Guides"),
	UGCMatchingUGCType_WebGuides = 8 UMETA(DisplayName = "Web Guides"),
	UGCMatchingUGCType_IntegratedGuides = 9 UMETA(DisplayName = "Integrated Guides"),
	UGCMatchingUGCType_UsableInGame = 10 UMETA(DisplayName = "Usable In Game"),
	UGCMatchingUGCType_ControllerBindings = 11 UMETA(DisplayName = "Controller Bindings"),
	UGCMatchingUGCType_GameManagedItems = 12 UMETA(DisplayName = "Game Managed Items"),
	UGCMatchingUGCType_All = -1 UMETA(DisplayName = "All"),
};

UENUM(BlueprintType)
enum ESIK_UGCQuery
{
	UGCQuery_RankedByVote = 0 UMETA(DisplayName = "Ranked By Vote"),
	UGCQuery_RankedByPublicationDate = 1 UMETA(DisplayName = "Ranked By Publication Date"),
	UGCQuery_AcceptedForGameRankedByAcceptanceDate = 2 UMETA(DisplayName = "Accepted For Game Ranked By Acceptance Date"),
	UGCQuery_RankedByTrend = 3 UMETA(DisplayName = "Ranked By Trend"),
	UGCQuery_FavoritedByFriendsRankedByPublicationDate = 4 UMETA(DisplayName = "Favorited By Friends Ranked By Publication Date"),
	UGCQuery_CreatedByFriendsRankedByPublicationDate = 5 UMETA(DisplayName = "Created By Friends Ranked By Publication Date"),
	UGCQuery_RankedByNumTimesReported = 6 UMETA(DisplayName = "Ranked By Num Times Reported"),
	UGCQuery_CreatedByFollowedUsersRankedByPublicationDate = 7 UMETA(DisplayName = "Created By Followed Users Ranked By Publication Date"),
	UGCQuery_NotYetRated = 8 UMETA(DisplayName = "Not Yet Rated"),
	UGCQuery_RankedByTotalVotesAsc = 9 UMETA(DisplayName = "Ranked By Total Votes Asc"),
	UGCQuery_RankedByVotesUp = 10 UMETA(DisplayName = "Ranked By Votes Up"),
	UGCQuery_RankedByTextSearch = 11 UMETA(DisplayName = "Ranked By Text Search"),
	UGCQuery_RankedByTotalUniqueSubscriptions = 12 UMETA(DisplayName = "Ranked By Total Unique Subscriptions"),
	UGCQuery_RankedByPlaytimeTrend = 13 UMETA(DisplayName = "Ranked By Playtime Trend"),
	UGCQuery_RankedByTotalPlaytime = 14 UMETA(DisplayName = "Ranked By Total Playtime"),
	UGCQuery_RankedByAveragePlaytimeTrend = 15 UMETA(DisplayName = "Ranked By Average Playtime Trend"),
	UGCQuery_RankedByLifetimeAveragePlaytime = 16 UMETA(DisplayName = "Ranked By Lifetime Average Playtime"),
	UGCQuery_RankedByPlaytimeSessionsTrend = 17 UMETA(DisplayName = "Ranked By Playtime Sessions Trend"),
	UGCQuery_RankedByLifetimePlaytimeSessions = 18 UMETA(DisplayName = "Ranked By Lifetime Playtime Sessions"),
	UGCQuery_RankedByLastUpdatedDate = 19 UMETA(DisplayName = "Ranked By Last Updated Date"),
};

UENUM(BlueprintType)
enum ESIK_UserUGCList
{
	UserUGCList_Published = 0 UMETA(DisplayName = "Published"),
	UserUGCList_VotedOn = 1 UMETA(DisplayName = "Voted On"),
	UserUGCList_VotedUp = 2 UMETA(DisplayName = "Voted Up"),
	UserUGCList_VotedDown = 3 UMETA(DisplayName = "Voted Down"),
	UserUGCList_WillVoteLater = 4 UMETA(DisplayName = "Will Vote Later"),
	UserUGCList_Favorited = 5 UMETA(DisplayName = "Favorited"),
	UserUGCList_Subscribed = 6 UMETA(DisplayName = "Subscribed"),
	UserUGCList_UsedOrPlayed = 7 UMETA(DisplayName = "Used Or Played"),
	UserUGCList_Followed = 8 UMETA(DisplayName = "Followed"),
};

UENUM(BlueprintType)
enum ESIK_UserUGCListSortOrder
{
	UserUGCListSortOrder_CreationOrderDesc = 0 UMETA(DisplayName = "Creation Order Desc"),
	UserUGCListSortOrder_CreationOrderAsc = 1 UMETA(DisplayName = "Creation Order Asc"),
	UserUGCListSortOrder_TitleAsc = 2 UMETA(DisplayName = "Title Asc"),
	UserUGCListSortOrder_LastUpdatedDesc = 3 UMETA(DisplayName = "Last Updated Desc"),
	UserUGCListSortOrder_SubscriptionDateDesc = 4 UMETA(DisplayName = "Subscription Date Desc"),
	UserUGCListSortOrder_VoteScoreDesc = 5 UMETA(DisplayName = "Vote Score Desc"),
	UserUGCListSortOrder_ForModeration = 6 UMETA(DisplayName = "For Moderation"),
};

UENUM(BlueprintType)
enum ESIK_UGCContentDescriptorID
{
	UserUGCListSortOrder_None = 0 UMETA(DisplayName = "None"),
	UGCContentDescriptor_NudityOrSexualContent = 1 UMETA(DisplayName = "Nudity Or Sexual Content"),
	UGCContentDescriptor_FrequentViolenceOrGore = 2 UMETA(DisplayName = "Frequent Violence Or Gore"),
	UGCContentDescriptor_AdultOnlySexualContent = 3 UMETA(DisplayName = "Adult Only Sexual Content"),
	UGCContentDescriptor_GratuitousSexualContent = 4 UMETA(DisplayName = "Gratuitous Sexual Content"),
	UGCContentDescriptor_AnyMatureContent = 5 UMETA(DisplayName = "Any Mature Content"),
};

USTRUCT(BlueprintType)
struct FSIK_UGCQueryHandle
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 Result;

	FSIK_UGCQueryHandle()
	{
		Result = 0;
	}
	FSIK_UGCQueryHandle(UGCQueryHandle_t UGCQueryHandle)
	{
		Result = UGCQueryHandle;
	}
	UGCQueryHandle_t GetUGCQueryHandle() const
	{
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FSIK_UGCUpdateHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 Result;

	FSIK_UGCUpdateHandle()
	{
		Result = 0;
	}
	FSIK_UGCUpdateHandle(UGCUpdateHandle_t UGCUpdateHandle)
	{
		Result = UGCUpdateHandle;
	}
	UGCUpdateHandle_t GetUGCUpdateHandle() const
	{
		return Result;
	}
};


USTRUCT(BlueprintType)
struct FSIK_SteamUGCDetails
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_PublishedFileId PublishedFileId = FSIK_PublishedFileId();

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_Result> Result = ESIK_Result::ResultFail;
	
	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_WorkshopFileType> FileType = ESIK_WorkshopFileType::WorkshopFileTypeFirst;
	
	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_SteamId Owner = FSIK_SteamId();

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_AppId CreatorAppID = FSIK_AppId();

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_AppId ConsumerAppID = FSIK_AppId();

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FString Title = "";

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FString Description = "";

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 TimeCreate = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 TimeUpdated = 0;
	
	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 TimeAddedToUserList = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	TEnumAsByte<ESIK_RemoteStoragePublishedFileVisibility> Visibility = ESIK_RemoteStoragePublishedFileVisibility::ERemoteStoragePublishedFileVisibilityUnlisted;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	bool bBanned = false;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	bool bAcceptedForUse = false;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	bool bTagsTruncated = false;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FString Tags = "";

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_UGCHandle File;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FSIK_UGCHandle PreviewFile;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FString FileName = "";

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 FileSize = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 PreviewFileSize = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	FString URL = "";

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 VotesUp = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 VotesDown = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	float Score = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int32 NumChildren = 0;

	FSIK_SteamUGCDetails()
	{
		PublishedFileId = FSIK_PublishedFileId();
		Result = ESIK_Result::ResultFail;
		FileType = ESIK_WorkshopFileType::WorkshopFileTypeFirst;
		Owner = FSIK_SteamId();
		CreatorAppID = FSIK_AppId();
		ConsumerAppID = FSIK_AppId();
		Title = "";
		Description = "";
		TimeCreate = 0;
		TimeUpdated = 0;
		TimeAddedToUserList = 0;
		Visibility = ESIK_RemoteStoragePublishedFileVisibility::ERemoteStoragePublishedFileVisibilityUnlisted;
		bBanned = false;
		bAcceptedForUse = false;
		bTagsTruncated = false;
		Tags = "";
		File = FSIK_UGCHandle();
		PreviewFile = FSIK_UGCHandle();
		FileName = "";
		FileSize = 0;
		PreviewFileSize = 0;
		URL = "";
		VotesUp = 0;
		VotesDown = 0;
		Score = 0;
		NumChildren = 0;
	}

	FSIK_SteamUGCDetails (SteamUGCDetails_t SteamUGCDetails)
	{
		PublishedFileId = SteamUGCDetails.m_nPublishedFileId;
		Result = static_cast<ESIK_Result>(SteamUGCDetails.m_eResult);
		FileType = static_cast<ESIK_WorkshopFileType>(SteamUGCDetails.m_eFileType);
		Owner = SteamUGCDetails.m_ulSteamIDOwner;
		CreatorAppID = SteamUGCDetails.m_nCreatorAppID;
		ConsumerAppID = SteamUGCDetails.m_nConsumerAppID;
		Title = SteamUGCDetails.m_rgchTitle;
		Description = SteamUGCDetails.m_rgchDescription;
		TimeCreate = SteamUGCDetails.m_rtimeCreated;
		TimeUpdated = SteamUGCDetails.m_rtimeUpdated;
		TimeAddedToUserList = SteamUGCDetails.m_rtimeAddedToUserList;
		Visibility = static_cast<ESIK_RemoteStoragePublishedFileVisibility>(SteamUGCDetails.m_eVisibility);
		bBanned = SteamUGCDetails.m_bBanned;
		bAcceptedForUse = SteamUGCDetails.m_bAcceptedForUse;
		bTagsTruncated = SteamUGCDetails.m_bTagsTruncated;
		Tags = SteamUGCDetails.m_rgchTags;
		File = SteamUGCDetails.m_hFile;
		PreviewFile = SteamUGCDetails.m_hPreviewFile;
		FileName = SteamUGCDetails.m_pchFileName;
		FileSize = SteamUGCDetails.m_nFileSize;
		PreviewFileSize = SteamUGCDetails.m_nPreviewFileSize;
		URL = SteamUGCDetails.m_rgchURL;
		VotesUp = SteamUGCDetails.m_unVotesUp;
		VotesDown = SteamUGCDetails.m_unVotesDown;
		Score = SteamUGCDetails.m_flScore;
		NumChildren = SteamUGCDetails.m_unNumChildren;
	}
};

USTRUCT(BlueprintType)
struct FSIK_SteamLeaderboardEntries
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 Result = 0;

	FSIK_SteamLeaderboardEntries()
	{
		Result = 0;
	}
	FSIK_SteamLeaderboardEntries(SteamLeaderboardEntries_t SteamLeaderboardEntries)
	{
		Result = SteamLeaderboardEntries;
	}
	
};

USTRUCT(BlueprintType)
struct FSIK_SteamLeaderboard
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Steam Integration Kit")
	int64 Result = 0;

	FSIK_SteamLeaderboard()
	{
		Result = 0;
	}
	FSIK_SteamLeaderboard(SteamLeaderboard_t SteamLeaderboard)
	{
		Result = SteamLeaderboard;
	}
};


UENUM(BlueprintType)
enum ESIK_Universe
{
	UniverseInvalid = 0 UMETA(DisplayName = "Invalid"),
	UniversePublic = 1 UMETA(DisplayName = "Public"),
	UniverseBeta = 2 UMETA(DisplayName = "Beta"),
	UniverseInternal = 3 UMETA(DisplayName = "Internal"),
	UniverseDev = 4 UMETA(DisplayName = "Dev"),
	UniverseMax UMETA(DisplayName = "Max"),
};


USTRUCT(BlueprintType)
struct FSIK_PartyBeaconID
{
	GENERATED_BODY()

	int64 Result = 0;

	FSIK_PartyBeaconID()
	{
		Result = 0;
	}

	FSIK_PartyBeaconID(PartyBeaconID_t PartyBeaconID)
	{
		Result = PartyBeaconID;
	}

	PartyBeaconID_t GetPartyBeaconID() const
	{
		return Result;
	}
};


USTRUCT(BlueprintType)
struct FSIK_GameID
{
	GENERATED_BODY()

	int64 Result = 0;

	FSIK_GameID()
	{
		Result = 0;
	}

	FSIK_GameID(CGameID GameID)
	{
		Result = *GameID.GetUint64Ptr();
	}

	CGameID GetGameID() const
	{
		CGameID LocalId;
		LocalId.Set(Result);
		return LocalId;
	}
};

UENUM(BlueprintType)
enum ESIK_FriendFlags
{
	FriendFlagNone = 0x00 UMETA(DisplayName = "None"),
	FriendFlagBlocked = 0x01 UMETA(DisplayName = "Blocked"),
	FriendFlagFriendshipRequested = 0x02 UMETA(DisplayName = "Friendship Requested"),
	FriendFlagImmediate = 0x04 UMETA(DisplayName = "Immediate"),
	FriendFlagClanMember = 0x08 UMETA(DisplayName = "Clan Member"),
	FriendFlagOnGameServer = 0x10 UMETA(DisplayName = "On Game Server"),
	FriendFlagRequestingFriendship = 0x80 UMETA(DisplayName = "Requesting Friendship"),
	FriendFlagRequestingInfo = 0x100 UMETA(DisplayName = "Requesting Info"),
	FriendFlagIgnored = 0x200 UMETA(DisplayName = "Ignored"),
	FriendFlagIgnoredFriend = 0x400 UMETA(DisplayName = "Ignored Friend"),
	FriendFlagSuggested = 0x800 UMETA(DisplayName = "Suggested"),
	FriendFlagChatMember = 0x1000 UMETA(DisplayName = "Chat Member"),
	FriendFlagFlagAll = 0xFFFF UMETA(DisplayName = "Flag All"),
};

UENUM(BlueprintType)
enum ESIK_EGamepadTextInputLineMode
{
	ESIK_EGamepadTextInputLineModeSingleLine = 0 UMETA(DisplayName = "Single Line"),
	ESIK_EGamepadTextInputLineModeMultipleLines = 1 UMETA(DisplayName = "Multiple Lines"),
};

UENUM(BlueprintType)
enum ESIK_EGamepadTextInputMode
{
	ESIK_EGamepadTextInputModeNormal = 0 UMETA(DisplayName = "Normal"),
	ESIK_EGamepadTextInputModePassword = 1 UMETA(DisplayName = "Password"),
};

UENUM(BlueprintType)
enum ESIK_EFloatingGamepadTextInputMode
{
	//Enter dismisses the keyboard
	ESIK_EFloatingGamepadTextInputModeModeSingleLine = 0 UMETA(DisplayName = "Single Line"),
	//User needs to explicitly dismiss the keyboard
	ESIK_EFloatingGamepadTextInputModeModeMultipleLines = 1 UMETA(DisplayName = "Multiple Lines"),
	//Keyboard is displayed in a special mode that makes it easier to enter emails
	ESIK_EFloatingGamepadTextInputModeModeEmail = 2 UMETA(DisplayName = "Email"),
	//Numeric keypad is shown
	ESIK_EFloatingGamepadTextInputModeModeNumeric = 3 UMETA(DisplayName = "Numeric"),
};

UENUM(BlueprintType)
enum ESIK_ECommunityProfileItemType
{
	ESIK_ECommunityProfileItemType_AnimatedAvatar = 0 UMETA(DisplayName = "Animated avatar image (GIF)"),
	ESIK_ECommunityProfileItemType_AvatarFrame = 1 UMETA(DisplayName = "Avatar frame (may or may not be an animated PNG)"),
	ESIK_ECommunityProfileItemType_ProfileModifier = 2 UMETA(DisplayName = "Special profile modifier item, like Seasonal Profile or Artist Profile"),
	ESIK_ECommunityProfileItemType_ProfileBackground = 3 UMETA(DisplayName = "Profile background image or movie"),
	ESIK_ECommunityProfileItemType_MiniProfileBackground = 4 UMETA(DisplayName = "Background image or movie for the hover flyout for a user"),
};

UENUM(BlueprintType)
enum ESIK_ECommunityProfileItemProperty
{
	ESIK_ECommunityProfileItemProperty_ImageSmall = 0 UMETA(DisplayName = "URL to the small or animated version of the image"),
	ESIK_ECommunityProfileItemProperty_ImageLarge = 1 UMETA(DisplayName = "URL to the large or static version of the image"),
	ESIK_ECommunityProfileItemProperty_InternalName = 2 UMETA(DisplayName = "Internal name entered on the partner site (for debugging)"),
	ESIK_ECommunityProfileItemProperty_Title = 3 UMETA(DisplayName = "Localized name of the item"),
	ESIK_ECommunityProfileItemProperty_Description = 4 UMETA(DisplayName = "Localized description of the item"),
	ESIK_ECommunityProfileItemProperty_AppID = 5 UMETA(DisplayName = "AppID of the item (unsigned integer)"),
	ESIK_ECommunityProfileItemProperty_TypeID = 6 UMETA(DisplayName = "Type id of the item, unique to the appid (unsigned integer)"),
	ESIK_ECommunityProfileItemProperty_Class = 7 UMETA(DisplayName = "Class or type of item (internal value, unsigned integer)"),
	ESIK_ECommunityProfileItemProperty_MovieWebM = 8 UMETA(DisplayName = "URL to the webm video file"),
	ESIK_ECommunityProfileItemProperty_MovieMP4 = 9 UMETA(DisplayName = "URL to the mp4 video file"),
	ESIK_ECommunityProfileItemProperty_MovieWebMSmall = 10 UMETA(DisplayName = "URL to the small webm video file"),
	ESIK_ECommunityProfileItemProperty_MovieMP4Small = 11 UMETA(DisplayName = "URL to the small mp4 video file"),
};


UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SharedFile : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static TArray<uint8> ConvertStringToUint8Array(FString String);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static FString ConvertUint8ArrayToString(TArray<uint8> Array);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static TArray<uint8> ConvertFileToUint8Array(FString FilePath, bool& bSuccess);
	
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static int64 ConvertSteamIdToInt64(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static FSIK_SteamId ConvertInt64ToSteamId(int64 Int64);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static FSIK_AccountID GetAccountID(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || Helper Functions")
	static TEnumAsByte<ESIK_Universe> GetUniverse(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Steam Integration Kit || Helper Functions")
	static bool IsValidSteamId(FSIK_SteamId SteamId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Steam Integration Kit || Helper Functions")
	static bool IsValidGameId(FSIK_GameID GameId);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Steam Integration Kit || Helper Functions")
	static bool IsEqualSteamId(FSIK_SteamId SteamId1, FSIK_SteamId SteamId2);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Steam Integration Kit || Helper Functions")
	static bool IsEqualGameId(FSIK_GameID GameId1, FSIK_GameID GameId2);
	
};

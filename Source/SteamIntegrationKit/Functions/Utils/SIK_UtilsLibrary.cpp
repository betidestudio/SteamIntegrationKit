// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_UtilsLibrary.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/SaveGame.h"
#include "Serialization/MemoryWriter.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"

bool USIK_UtilsLibrary::IsControllerConnected()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	ISteamInput* SteamInputInterface = SteamInput();
	if (!SteamInputInterface)
	{
		return false;
	}

	if (!SteamInputInterface->Init(false))
	{
		return false;
	}

	SteamInputInterface->RunFrame();

	InputHandle_t handlesOut[STEAM_INPUT_MAX_COUNT] = { 0 };

	int numControllers = SteamInputInterface->GetConnectedControllers(handlesOut);

	if (numControllers > 0)
	{
		return true;
	}
	return false;
#else
	return false;
#endif
}
bool USIK_UtilsLibrary::OpenSteamKeyboard(int32 KeyboardMode, int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (SteamUtils())
	{
		return SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(KeyboardMode), TextFieldXPosition, TextFieldYPosition, TextFieldWidth, TextFieldHeight);
	}
	return false;
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::OverlayNeedsPresent()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->BOverlayNeedsPresent();
#else
	return false;
#endif
}

FSIK_AppId USIK_UtilsLibrary::GetAppID()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FSIK_AppId();
	}
	return SteamUtils()->GetAppID();
#else
	return FSIK_AppId();
#endif	
}

int32 USIK_UtilsLibrary::GetCurrentBatteryPower()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetCurrentBatteryPower();
#else
	return 0;
#endif
}

FString USIK_UtilsLibrary::GetEnteredGamepadTextInput()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FString();
	}
	char *	rgchText = new char[128];
	SteamUtils()->GetEnteredGamepadTextInput(rgchText, 128);
	FString result = FString(UTF8_TO_TCHAR(rgchText));
	delete[] rgchText;
	return result;
#else
	return FString();
#endif
}

int32 USIK_UtilsLibrary::GetEnteredGamepadTextLength()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetEnteredGamepadTextLength();
#else
	return 0;
#endif
}

bool USIK_UtilsLibrary::GetImageRGBA(int32 Image, TArray<FColor>& OutData, int32& OutWidth, int32& OutHeight)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if (!SteamUtils())
	{
		return false;
	}
	uint32 Width, Height;
	if (!SteamUtils()->GetImageSize(Image, &Width, &Height))
	{
		return false;
	}
	uint32 Size = Width * Height * 4;
	uint8* rgubDest = new uint8[Size];
	if (!SteamUtils()->GetImageRGBA(Image, rgubDest, Size))
	{
		delete[] rgubDest;
		return false;
	}
	OutData.Empty(Width * Height);
	for (uint32 i = 0; i < Size; i += 4)
	{
		// Rearrange the color channels from BGRA to RGBA
		OutData.Add(FColor(rgubDest[i + 2], rgubDest[i + 1], rgubDest[i], rgubDest[i + 3]));
	}
	delete[] rgubDest;

	// Assign the width and height to the output parameters
	OutWidth = static_cast<int32>(Width);
	OutHeight = static_cast<int32>(Height);
	
	return true;
#else
	return false;
#endif
}

FString USIK_UtilsLibrary::GetIPCountry()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FString();
	}
	return UTF8_TO_TCHAR(SteamUtils()->GetIPCountry());
#else
	return FString();
#endif
}

int32 USIK_UtilsLibrary::GetSecondsSinceAppActive()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetSecondsSinceAppActive();
#else
	return 0;
#endif
}

int32 USIK_UtilsLibrary::GetSecondsSinceComputerActive()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetSecondsSinceComputerActive();
#else
	return 0;
#endif
}

int32 USIK_UtilsLibrary::GetServerRealTime()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return 0;
	}
	return SteamUtils()->GetServerRealTime();
#else
	return 0;
#endif
}

FString USIK_UtilsLibrary::GetSteamUILanguage()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return FString();
	}
	return FString(UTF8_TO_TCHAR(SteamUtils()->GetSteamUILanguage()));
#else
	return FString();
#endif
}

bool USIK_UtilsLibrary::IsOverlayEnabled()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsOverlayEnabled();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamChinaLauncher()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamChinaLauncher();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::InitFilterText()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->InitFilterText();
#else
	return false;
#endif
}

int32 USIK_UtilsLibrary::FilterText(TEnumAsByte<ESIK_TextFilteringContext> Context, FSIK_SteamId SourceSteamId, const FString& InputMessage, FString& OutFilteredText)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		OutFilteredText = InputMessage;
		return 0;
	}
	
	// Convert input to UTF-8
	FTCHARToUTF8 UTF8Input(*InputMessage);
	
	// Allocate buffer for filtered text (same size as input + null terminator)
	TArray<char> FilteredBuffer;
	FilteredBuffer.SetNum(UTF8Input.Length() + 1);
	
	// Call Steam API
	int32 FilteredChars = SteamUtils()->FilterText(
		static_cast<ETextFilteringContext>(Context.GetValue()),
		SourceSteamId.GetSteamID(),
		UTF8Input.Get(),
		FilteredBuffer.GetData(),
		FilteredBuffer.Num()
	);
	
	// Convert result back to FString
	OutFilteredText = UTF8_TO_TCHAR(FilteredBuffer.GetData());
	
	return FilteredChars;
#else
	OutFilteredText = InputMessage;
	return 0;
#endif
}

TArray<uint8> USIK_UtilsLibrary::SaveGameObjectToByteArray(USaveGame* SaveGameObject)
{
	TArray<uint8> ByteArray;
	
	if (!SaveGameObject)
	{
		return ByteArray;
	}

	FMemoryWriter MemWriter(ByteArray, /*bIsPersistent*/ true);
	FObjectAndNameAsStringProxyArchive Ar(MemWriter, /*bLoadIfFindFails*/ true);
	Ar.ArIsSaveGame = true;
	
	SaveGameObject->Serialize(Ar);
	return ByteArray;
}

USaveGame* USIK_UtilsLibrary::ByteArrayToSaveGameObject(const TArray<uint8>& Data, TSubclassOf<USaveGame> SaveGameClass)
{
	if (Data.Num() == 0 || !SaveGameClass)
	{
		return nullptr;
	}

	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromMemory(Data))
	{
		// Check if the loaded object is of the correct class
		if (Loaded && Loaded->GetClass()->IsChildOf(SaveGameClass.Get()))
		{
			return Loaded;
		}
		// If class doesn't match, we'll fall back to manual deserialization
	}

	USaveGame* SaveGameObject = NewObject<USaveGame>((UObject*)GetTransientPackage(), SaveGameClass.Get(), NAME_None, RF_NoFlags, nullptr, false, nullptr);
	if (!SaveGameObject)
	{
		return nullptr;
	}

	FMemoryReader MemReader(Data, /*bIsPersistent*/ true);
	FObjectAndNameAsStringProxyArchive Ar(MemReader, /*bLoadIfFindFails*/ true);
	Ar.ArIsSaveGame = true;

	SaveGameObject->Serialize(Ar);
	return SaveGameObject;
}

// UGC Validation Utilities
bool USIK_UtilsLibrary::IsValidUGCTag(const FString& TagName)
{
	if (TagName.IsEmpty() || TagName.Len() > 255)
	{
		return false;
	}
	
	// Check for invalid characters (commas are not allowed)
	if (TagName.Contains(TEXT(",")))
	{
		return false;
	}
	
	// Check for printable characters only
	for (const TCHAR& Char : TagName)
	{
		if (!FChar::IsPrint(Char))
		{
			return false;
		}
	}
	
	return true;
}

FString USIK_UtilsLibrary::SanitizeUGCTag(const FString& TagName)
{
	FString Sanitized = TagName;
	
	// Remove commas
	Sanitized = Sanitized.Replace(TEXT(","), TEXT(""));
	
	// Remove non-printable characters
	FString Result;
	for (const TCHAR& Char : Sanitized)
	{
		if (FChar::IsPrint(Char))
		{
			Result += Char;
		}
	}
	
	// Truncate to 255 characters
	if (Result.Len() > 255)
	{
		Result = Result.Left(255);
	}
	
	return Result;
}

bool USIK_UtilsLibrary::ValidateUGCTagsArray(const TArray<FString>& Tags, TArray<FString>& InvalidTags)
{
	InvalidTags.Empty();
	
	for (const FString& Tag : Tags)
	{
		if (!IsValidUGCTag(Tag))
		{
			InvalidTags.Add(Tag);
		}
	}
	
	return InvalidTags.Num() == 0;
}

TArray<FString> USIK_UtilsLibrary::SanitizeUGCTagsArray(const TArray<FString>& Tags)
{
	TArray<FString> SanitizedTags;
	
	for (const FString& Tag : Tags)
	{
		FString Sanitized = SanitizeUGCTag(Tag);
		if (!Sanitized.IsEmpty())
		{
			SanitizedTags.Add(Sanitized);
		}
	}
	
	return SanitizedTags;
}

bool USIK_UtilsLibrary::IsSteamInBigPictureMode()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamInBigPictureMode();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamRunningInVR()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamRunningInVR();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsVRHeadsetStreamingEnabled()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsVRHeadsetStreamingEnabled();
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::IsSteamRunningOnSteamDeck()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->IsSteamRunningOnSteamDeck();
#else
	return false;
#endif
}

void USIK_UtilsLibrary::SetOverlayNotificationInset(int32 HorizontalInset, int32 VerticalInset)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetOverlayNotificationInset(HorizontalInset, VerticalInset);
#endif
}

void USIK_UtilsLibrary::SetOverlayNotificationPosition(TEnumAsByte<ESIK_NotificationPosition> NotificationPosition)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetOverlayNotificationPosition(static_cast<ENotificationPosition>(NotificationPosition.GetValue()));
#endif
}

void USIK_UtilsLibrary::SetVRHeadsetStreamingEnabled(bool bEnabled)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetVRHeadsetStreamingEnabled(bEnabled);
#endif
}

bool USIK_UtilsLibrary::ShowGamepadTextInput(TEnumAsByte<ESIK_EGamepadTextInputMode> InputMode,
	TEnumAsByte<ESIK_EGamepadTextInputLineMode> LineInputMode, const FString& Description, int32 CharMax,
	const FString& ExistingText)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->ShowGamepadTextInput(static_cast<EGamepadTextInputMode>(InputMode.GetValue()), static_cast<EGamepadTextInputLineMode>(LineInputMode.GetValue()), TCHAR_TO_ANSI(*Description), CharMax, TCHAR_TO_ANSI(*ExistingText));
#else
	return false;
#endif
}

bool USIK_UtilsLibrary::ShowFloatingGamepadTextInput(TEnumAsByte<ESIK_EFloatingGamepadTextInputMode> KeyboardMode,
	int32 TextFieldXPosition, int32 TextFieldYPosition, int32 TextFieldWidth, int32 TextFieldHeight)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return false;
	}
	return SteamUtils()->ShowFloatingGamepadTextInput(static_cast<EFloatingGamepadTextInputMode>(KeyboardMode.GetValue()), TextFieldXPosition, TextFieldYPosition, TextFieldWidth, TextFieldHeight);
#else
	return false;
#endif
}

void USIK_UtilsLibrary::StartVrDashboard()
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->StartVRDashboard();
#endif
}

void USIK_UtilsLibrary::SetGameLauncherMode(bool bLauncherMode)
{
#if (WITH_ENGINE_STEAM && ONLINESUBSYSTEMSTEAM_PACKAGE) || (WITH_STEAMKIT && !WITH_ENGINE_STEAM)
	if(!SteamUtils())
	{
		return;
	}
	SteamUtils()->SetGameLauncherMode(bLauncherMode);
#endif
}

bool USIK_UtilsLibrary::CheckForSteamLobbyInvite(FSIK_SteamId& OutSteamLobbyId)
{
	// Get the command line
	FString CommandLine = FCommandLine::Get();
	
	// Parse into array (space-delimited, culling empties)
	TArray<FString> CommandLineArgs;
	CommandLine.ParseIntoArray(CommandLineArgs, TEXT(" "), true);
	
	// Find "+connect_lobby" argument
	int32 ConnectLobbyIndex = CommandLineArgs.Find(TEXT("+connect_lobby"));
	
	if (ConnectLobbyIndex != INDEX_NONE && ConnectLobbyIndex + 1 < CommandLineArgs.Num())
	{
		// Get the lobby ID (next token after +connect_lobby)
		FString LobbyIdString = CommandLineArgs[ConnectLobbyIndex + 1];
		
		// Strip any quotes around the ID
		LobbyIdString = LobbyIdString.Replace(TEXT("\""), TEXT(""));
		LobbyIdString = LobbyIdString.Replace(TEXT("'"), TEXT(""));
		
		// Convert to Steam ID
		uint64 LobbyIdInt64 = FCString::Strtoui64(*LobbyIdString, nullptr, 10);
		OutSteamLobbyId = FSIK_SteamId(LobbyIdInt64);
		
		UE_LOG(LogTemp, Log, TEXT("Steam Integration Kit: Found Steam lobby invite: %s (SteamID: %llu)"), *LobbyIdString, LobbyIdInt64);
		return true;
	}
	
	return false;
}

// EasySaveStruct Integration - Generic Helper Functions
bool USIK_UtilsLibrary::ConvertStructToJSONString(const FStructProperty* InStruct, FString& OutJsonString, void* StructPtr)
{
	// Pin check 
	if (!(InStruct && StructPtr))
	{
		UE_LOG(LogTemp, Warning, TEXT("InStruct: %s"), InStruct ? *InStruct->GetName() : TEXT("nullptr"));
		UE_LOG(LogTemp, Warning, TEXT("StructPtr: %p"), StructPtr);
		UE_LOG(LogTemp, Error, TEXT("Input Pin is not a struct."));
		return false;
	}
	
	// Convert struct to JSON string
	return FJsonObjectConverter::UStructToJsonObjectString(InStruct->Struct, StructPtr, OutJsonString);
}

bool USIK_UtilsLibrary::ConvertJSONStringToStruct(const FString& InJsonString, FStructProperty* OutStruct, void* StructPtr)
{
	// Pin check
	if (!(OutStruct && StructPtr))
	{
		UE_LOG(LogTemp, Error, TEXT("Output Pin is not a struct."));
		return false;
	}

	// JSON string deserialize
	const TSharedRef<TJsonReader<>>& Reader = TJsonReaderFactory<>::Create(InJsonString);
	TSharedPtr<FJsonObject> Object;
	if (!(FJsonSerializer::Deserialize(Reader, /*out*/ Object) && Object.IsValid()))
	{
		UE_LOG(LogTemp, Error, TEXT("Input string can not parse to json object, with error code : %s"), *Reader->GetErrorMessage());
		return false;
	}

	// Convert JSON object to struct
	return FJsonObjectConverter::JsonObjectToUStruct(Object.ToSharedRef(), OutStruct->Struct, StructPtr);
}

bool USIK_UtilsLibrary::ConvertStructArrayToJSONString(const FArrayProperty* InArrayProperty, bool ShowLog, FString& OutJsonString, void* StructArrayPtr)
{
	OutJsonString.Empty();
	
	// Check input array property validity
	if (!InArrayProperty || !StructArrayPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid input array property or struct array pointer."));
		return false;
	}
	
	TArray<FString> OutJsonArray;
	FStructProperty* InnerStructProperty = CastField<FStructProperty>(InArrayProperty->Inner);

	if (!InnerStructProperty)
	{
		UE_LOG(LogTemp, Error, TEXT("Inner struct property is null. Input must be an array of USTRUCT types, not basic types like string or int."));
		return false;
	}
	FScriptArrayHelper ArrayHelper(InArrayProperty, StructArrayPtr);
	
	for (int32 Index = 0; Index < ArrayHelper.Num(); ++Index)
	{
		// Get array element address
		void* ElementPtr = ArrayHelper.GetRawPtr(Index);

		// Convert to JSON string
		FString JsonString;
		if (ConvertStructToJSONString(InnerStructProperty, JsonString, ElementPtr))
		{
			// Add to output array
			OutJsonArray.Add(JsonString);
		}
		else
		{
			// Conversion failed, log error
			UE_LOG(LogTemp, Error, TEXT("Failed to convert struct element to JSON. Index: %d"), Index);
		}
	}
	
	OutJsonString.Append(TEXT("["));
	OutJsonString += FString::Join(OutJsonArray, TEXT(","));
	OutJsonString.Append(TEXT("]"));
	
	if (ShowLog)
	{
		UE_LOG(LogTemp, Warning, TEXT("StructArrayToJson=== \n %s"), *OutJsonString);
	}
	
	// Successfully converted all elements
	return true;
}

bool USIK_UtilsLibrary::ConvertJSONStringToStructArray(const FString& InJsonString, bool ShowLog, FArrayProperty* OutStructArray, void* StructArrayPtr)
{
	// Check input array property validity
	if (!OutStructArray || !StructArrayPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid input array property or struct array pointer."));
		return false;
	}

	// Parse JSON string to TArray type
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InJsonString);
	
	if (ShowLog)
	{
		UE_LOG(LogTemp, Warning, TEXT("StringToStructArray=== \n%s"), *InJsonString);
	}
	
	if (!FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON."));
		return false;
	}

	// Get inner struct property
	FStructProperty* InnerStructProperty = CastField<FStructProperty>(OutStructArray->Inner);

	if (!InnerStructProperty)
	{
		UE_LOG(LogTemp, Error, TEXT("Inner struct property is null."));
		return false;
	}
	
	// Set array size
	FScriptArrayHelper ArrayHelper(OutStructArray, StructArrayPtr);
	ArrayHelper.AddUninitializedValues(JsonArray.Num());

	for (int32 Index = 0; Index < JsonArray.Num(); ++Index)
	{
		TSharedPtr<FJsonObject> JsonObject = JsonArray[Index]->AsObject();

		if (JsonObject.IsValid())
		{
			// Create struct instance
			void* StructPtr = ArrayHelper.GetRawPtr(Index);
			InnerStructProperty->InitializeValue(StructPtr);

			// Convert JSON object to struct
			if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), InnerStructProperty->Struct, StructPtr))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to convert JSON object to struct."));
				return false;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid JSON object at index %d."), Index);
			return false;
		}
	}
	return true;
}

// EasySaveStruct Integration - File I/O Functions
FString USIK_UtilsLibrary::ReadTextFile(const FString& FilePath)
{
	if (!DoesFileExist(FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("File does not exist: %s"), *FilePath);
		return FString();
	}
	
	FString Result;
	if (FFileHelper::LoadFileToString(Result, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully read file: %s"), *FilePath);
		return Result;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *FilePath);
		return FString();
	}
}

bool USIK_UtilsLibrary::WriteTextFile(const FString& Content, const FString& FilePath)
{
	bool Result = FFileHelper::SaveStringToFile(Content, *FilePath);
	if (Result)
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully wrote file: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to write file: %s"), *FilePath);
	}
	return Result;
}

bool USIK_UtilsLibrary::DoesFileExist(const FString& FilePath)
{
	bool bExists = FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath);
	if (bExists)
	{
		UE_LOG(LogTemp, Log, TEXT("File exists: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("File does not exist: %s"), *FilePath);
	}
	return bExists;
}

// JSON API Helper Functions
FString USIK_UtilsLibrary::StringArrayToJSON(const TArray<FString>& StringArray)
{
	TArray<FString> EscapedStrings;
	
	for (const FString& Str : StringArray)
	{
		EscapedStrings.Add(TEXT("\"") + EscapeJSONString(Str) + TEXT("\""));
	}
	
	FString Result = TEXT("[");
	Result += FString::Join(EscapedStrings, TEXT(","));
	Result += TEXT("]");
	
	UE_LOG(LogTemp, Log, TEXT("StringArrayToJSON: %s"), *Result);
	
	return Result;
}

TArray<FString> USIK_UtilsLibrary::JSONToStringArray(const FString& JsonString)
{
	TArray<FString> Result;
	
	if (!IsValidJSON(JsonString))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid JSON string provided to JSONToStringArray"));
		return Result;
	}
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	
	if (FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : JsonArray)
		{
			if (Value.IsValid())
			{
				Result.Add(Value->AsString());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON array: %s"), *JsonString);
	}
	
	return Result;
}

FString USIK_UtilsLibrary::BuildJSONObject(const TMap<FString, FString>& KeyValuePairs)
{
	TArray<FString> Pairs;
	
	for (const auto& Pair : KeyValuePairs)
	{
		FString EscapedKey = EscapeJSONString(Pair.Key);
		FString EscapedValue = EscapeJSONString(Pair.Value);
		Pairs.Add(FString::Printf(TEXT("\"%s\":\"%s\""), *EscapedKey, *EscapedValue));
	}
	
	FString Result = TEXT("{");
	Result += FString::Join(Pairs, TEXT(","));
	Result += TEXT("}");
	
	UE_LOG(LogTemp, Log, TEXT("BuildJSONObject: %s"), *Result);
	
	return Result;
}

FString USIK_UtilsLibrary::ParseJSONValue(const FString& JsonString, const FString& Key)
{
	if (!IsValidJSON(JsonString))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid JSON string provided to ParseJSONValue"));
		return FString();
	}
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	TSharedPtr<FJsonObject> Object;
	
	if (FJsonSerializer::Deserialize(Reader, Object) && Object.IsValid())
	{
		FString Result;
		if (Object->TryGetStringField(*Key, Result))
		{
			return Result;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Key '%s' not found in JSON object"), *Key);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON object: %s"), *JsonString);
	}
	
	return FString();
}

FString USIK_UtilsLibrary::EscapeJSONString(const FString& InputString)
{
	FString Escaped = InputString;
	
	// Escape backslashes first (must be done before other escapes)
	Escaped = Escaped.Replace(TEXT("\\"), TEXT("\\\\"));
	
	// Escape double quotes
	Escaped = Escaped.Replace(TEXT("\""), TEXT("\\\""));
	
	// Escape newlines
	Escaped = Escaped.Replace(TEXT("\n"), TEXT("\\n"));
	
	// Escape carriage returns
	Escaped = Escaped.Replace(TEXT("\r"), TEXT("\\r"));
	
	// Escape tabs
	Escaped = Escaped.Replace(TEXT("\t"), TEXT("\\t"));
	
	return Escaped;
}

bool USIK_UtilsLibrary::IsValidJSON(const FString& JsonString)
{
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	TSharedPtr<FJsonValue> Value;
	
	bool bValid = FJsonSerializer::Deserialize(Reader, Value) && Value.IsValid();
	
	if (!bValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid JSON: %s"), *JsonString);
	}
	
	return bValid;
}

// EasySaveStruct Integration - Blueprint Stub Functions (Custom Thunk Handlers)
bool USIK_UtilsLibrary::SerializeStructToJSON(const int32& InStruct, FString& OutJsonString)
{
	// We should never hit this! Stubs to avoid NoExport on the class.
	check(0);
	return false;
}

bool USIK_UtilsLibrary::DeserializeJSONToStruct(const FString& InJsonString, int32& OutStruct)
{
	// We should never hit this! Stubs to avoid NoExport on the class.
	check(0);
	return false;
}

bool USIK_UtilsLibrary::SerializeStructArrayToJSON(const TArray<int32>& InStructArray, FString& OutJsonString)
{
	// We should never hit this! Stubs to avoid NoExport on the class.
	check(0);
	return false;
}

bool USIK_UtilsLibrary::DeserializeJSONToStructArray(const FString& InJsonString, TArray<int32>& InStructArray)
{
	// We should never hit this! Stubs to avoid NoExport on the class.
	check(0);
	return false;
}

// EasySaveStruct Integration - Custom Thunk Function Implementations
DEFINE_FUNCTION(USIK_UtilsLibrary::execSerializeStructToJSON)
{
	// Get input variable
	Stack.StepCompiledIn<FStructProperty>(NULL);
	
	void* StructPtr = Stack.MostRecentPropertyAddress;
	FStructProperty* InStruct = CastField<FStructProperty>(Stack.MostRecentProperty);
	// Get output variable
	P_GET_PROPERTY_REF(FStrProperty, OutJsonString);
	P_FINISH;

	bool bSuccess = false;
	P_NATIVE_BEGIN;
	bSuccess = ConvertStructToJSONString(InStruct, OutJsonString, StructPtr);
	P_NATIVE_END;
	*(bool*)RESULT_PARAM = bSuccess;
}

DEFINE_FUNCTION(USIK_UtilsLibrary::execDeserializeJSONToStruct)
{
	// Get input variable
	P_GET_PROPERTY_REF(FStrProperty, InJsonString);
	// Get output variable
	Stack.StepCompiledIn<FStructProperty>(NULL);
	void* StructPtr = Stack.MostRecentPropertyAddress;
	FStructProperty* OutStruct = CastField<FStructProperty>(Stack.MostRecentProperty);
	P_FINISH;
	
	bool bSuccess = false;
	P_NATIVE_BEGIN;
	bSuccess = ConvertJSONStringToStruct(InJsonString, OutStruct, StructPtr);
	P_NATIVE_END;
	*(bool*)RESULT_PARAM = bSuccess;
}

DEFINE_FUNCTION(USIK_UtilsLibrary::execSerializeStructArrayToJSON)
{
	Stack.StepCompiledIn<FArrayProperty>(NULL);
	void* StructPtr = Stack.MostRecentPropertyAddress;
	FArrayProperty* InArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	// Get output variable
	P_GET_PROPERTY_REF(FStrProperty, OutJsonString);
	P_FINISH;
	
	bool bSuccess = false;
	P_NATIVE_BEGIN;
	bSuccess = ConvertStructArrayToJSONString(InArrayProperty, false, OutJsonString, StructPtr);
	P_NATIVE_END;
	*(bool*)RESULT_PARAM = bSuccess;
}

DEFINE_FUNCTION(USIK_UtilsLibrary::execDeserializeJSONToStructArray)
{
	// Get input variable
	P_GET_PROPERTY_REF(FStrProperty, InJsonString);
	// Get output variable
	Stack.StepCompiledIn<FArrayProperty>(NULL);
	FArrayProperty* InArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	void* StructPtr = Stack.MostRecentPropertyAddress;
	P_FINISH;
	
	bool bSuccess = false;
	P_NATIVE_BEGIN;
	bSuccess = ConvertJSONStringToStructArray(InJsonString, false, InArrayProperty, StructPtr);
	P_NATIVE_END;
	*(bool*)RESULT_PARAM = bSuccess;
}




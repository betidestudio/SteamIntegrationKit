// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundWaveProcedural.h"
#include "SIK_SoundWaveProcedural.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINTEGRATIONKIT_API USIK_SoundWaveProcedural : public USoundWaveProcedural
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Steam Integration Kit || SDK Functions || User", meta = (DisplayName = "Queue Audio"))
	void SIK_QueueAudio(const TArray<uint8>& AudioData);
	
};

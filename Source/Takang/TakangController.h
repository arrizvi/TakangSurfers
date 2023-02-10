// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TakangController.generated.h"

/**
 * 
 */
UCLASS()
class TAKANG_API ATakangController : public APlayerController
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere,BlueprintReadOnly)


	UFUNCTION(BlueprintCallable)
	void SpawnNextFloor();
	
	UFUNCTION(BlueprintCallable)
	void CharacterDead();
	
};

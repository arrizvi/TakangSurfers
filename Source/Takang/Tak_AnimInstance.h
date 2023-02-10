// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Tak_AnimInstance.generated.h"

/**
 * 
 */
UCLASS(Transient,Blueprintable,HideCategories=(AnimInstace),BlueprintType)
class TAKANG_API UTak_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UTak_AnimInstance();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsAlive;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsHoverBoard;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsJetPack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsJumping;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsSliding;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

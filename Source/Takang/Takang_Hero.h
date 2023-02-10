// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.h"
#include "GameFramework/Character.h"
#include "Takang_Hero.generated.h"

UCLASS()
class TAKANG_API ATakang_Hero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATakang_Hero();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USpringArmComponent* SpringArm1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UCameraComponent* Camera1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Board1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Rocket1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UParticleSystemComponent* RocketSparks;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAudioComponent* BackgroundSound;
	
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 CoinScore;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsAliveNow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bisSliding;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanGoToOther;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bJetPack1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHoverBoard1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float NewLoactionofZ;
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<ATrack> TrackRef;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SelectedCharacterNumber;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<USkeletalMesh*> AllCharactersArray;
	UFUNCTION(BlueprintCallable)
	void AddNewMesh();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AddCoins();
	UFUNCTION(BlueprintCallable)
	void JumpAndSlide(float AxisValue);
	void CharacterCrouch();
	void CharacterUnCrouch();
	UFUNCTION(BlueprintCallable)
	void IncreaseSpeed();
	class UCharacterMovementComponent* MovementComponent;
	UFUNCTION(BlueprintCallable)
	void DecreaseSpeed();

	UFUNCTION(BlueprintCallable)
	void JetPackStart();
	void DeActiveJet();
	UFUNCTION(BlueprintCallable)
	void HoverBoardStart();
	void DeActiveHover();
	void HurdleOverlapped();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeath();


	//inputs
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bIsPressed;
	FVector2D TouchStart;
	FVector2D TouchEnd;
	//bool b
	void MovementDecision(float);
	UFUNCTION(BlueprintCallable)
	void FingerPressed();
	UFUNCTION(BlueprintCallable)
	void FingerReleased();
	UFUNCTION(BlueprintCallable)
	void MoveLeft();
	UFUNCTION(BlueprintCallable)
	void MoveRight();

	

	bool bCanExecuteTick=true;
	void VirtualTick();

	int32 Count=0;
	float XValue;
	bool CanMoveRight();
	bool CanMoveLeft();
	float JumpDistance=5000.0f;
	UFUNCTION(BlueprintImplementableEvent)
	float MoveLeftTimeLineValue();
	UFUNCTION(BlueprintImplementableEvent)
	float MoveRIghtTimeLineValue();

	
	
};


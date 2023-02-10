// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EHurdleType.h"
#include "GameFramework/Actor.h"
#include "Hurdles_Parent.generated.h"



UCLASS()
class TAKANG_API AHurdles_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHurdles_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USceneComponent* DefaultScene;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UBoxComponent* Collider;
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EHurdleType MyHurdleType;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	TEnumAsByte<EHurdleType> MyHurdleType;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USoundBase* HurdleSound;
	


	UFUNCTION(BlueprintCallable)
	void StoneOverlaped( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void PrintOverlapped(FString);
	virtual void OnConstruction(const FTransform& Transform) override;
};
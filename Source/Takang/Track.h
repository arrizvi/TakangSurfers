// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hurdles_Parent.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Track.generated.h"

UCLASS()
class TAKANG_API ATrack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Mesh1;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Mesh2;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Mesh3;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UBoxComponent* NextTrigger;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UBoxComponent* DestroyTrigger;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UArrowComponent* NextFloorArrow;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> TrackRefToSpawn;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> HurdleRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> BranchRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> StoneRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> CoinRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> ExtraRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> RocketRef;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AActor> BoardRef;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class USplineComponent* SpawningSpline;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<AActor*> HurdlesArray;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<AActor*> CoinArray;
	

	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	void NextTriggerOverlapped( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable)
	void DestroyTriggerOverlapped( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void ObjectsSpawn(USplineComponent* SplineComponent);
	void SpawnCoins(FVector,FRotator);
	void SpawnRockets(FVector,FRotator, bool);
	void SpawnHurdles(FVector,FRotator,bool);
	UFUNCTION(BlueprintCallable)
	void MoveCoinsUp(bool bShouldSpawn);


	
};



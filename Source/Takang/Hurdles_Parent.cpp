// Fill out your copyright notice in the Description page of Project Settings.


#include "Hurdles_Parent.h"

#include "Takang_Hero.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHurdles_Parent::AHurdles_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultScene=CreateDefaultSubobject<USceneComponent>(TEXT("CoinScene"));
	RootComponent=DefaultScene;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	Mesh->SetupAttachment(DefaultScene);
	Mesh->SetRelativeLocation(FVector(4.0,0,78.54));
	Mesh->SetRelativeRotation(FRotator(90,0,0));
	Mesh->SetRelativeScale3D(FVector(0.09,0.09,0.09));
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionProfileName(FName("NoCollision"),true);

	Collider=CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderSphere"));
	Collider->SetupAttachment(RootComponent);Mesh->SetRelativeLocation(FVector(4.0,0,78.54));
	Collider->SetRelativeLocation(FVector(19.10,19.19,151.37));
	Collider->SetRelativeScale3D(FVector(3.1,0.50,0.38));

}

// Called when the game starts or when spawned
void AHurdles_Parent::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this,&AHurdles_Parent::StoneOverlaped);
}

// Called every frame
void AHurdles_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AHurdles_Parent::StoneOverlaped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATakang_Hero* Character=Cast<ATakang_Hero>(OtherActor);
	if(Character)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),HurdleSound,Mesh->GetComponentLocation());
		switch (MyHurdleType)
		{
		case EHurdleType::Branch:
			Character->HurdleOverlapped();
			break;
		case EHurdleType::Stone:
			Character->HurdleOverlapped();
			break;
		case EHurdleType::Rocket:
			Character->JetPackStart();
			break;
		case EHurdleType::SkateBoard:
			Character->HoverBoardStart();
			break;
		case EHurdleType::Coin:
			Character->AddCoins();
			break;
		default:
			PrintOverlapped("MyHurdleType::Default");
			break;
		}
		Destroy();
	}
}

void AHurdles_Parent::PrintOverlapped(FString Overlapped_Name)
{
	//FString obj=NAME_Enum
	GEngine->AddOnScreenDebugMessage(1,0.5f,FColor::Green,(TEXT("%s Overlapped"),Overlapped_Name));
}

void AHurdles_Parent::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}


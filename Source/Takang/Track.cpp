
// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"


#include "Takang_Hero.h"

#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ATrack::ATrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent=CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent=SceneComponent;
	Mesh1=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh1->SetupAttachment(RootComponent);
	Mesh2=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh2->SetupAttachment(RootComponent);
	Mesh3=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Mesh3->SetupAttachment(RootComponent);
	NextTrigger=CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerNext"));
	NextTrigger->SetupAttachment(RootComponent);
	DestroyTrigger=CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerDestroy"));
	DestroyTrigger->SetupAttachment(RootComponent);

	NextFloorArrow=CreateDefaultSubobject<UArrowComponent>(TEXT("NextSpawnLocation"));
	NextFloorArrow->SetupAttachment(RootComponent);

	SpawningSpline=CreateDefaultSubobject<USplineComponent>(TEXT("SpawnSpline"));
	SpawningSpline->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ATrack::BeginPlay()
{
	Super::BeginPlay();
	NextTrigger->OnComponentBeginOverlap.AddDynamic(this,&ATrack::NextTriggerOverlapped);
	DestroyTrigger->OnComponentBeginOverlap.AddDynamic(this,&ATrack::DestroyTriggerOverlapped);
	this->ObjectsSpawn(SpawningSpline);
}



// Called every frame
void ATrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrack::NextTriggerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ATakang_Hero* Character=Cast<ATakang_Hero>(OtherActor);
	if(Character)
	{
		const FVector SpawnLocation=NextFloorArrow->GetComponentLocation();
		const FRotator SpawnRotation=NextFloorArrow->GetComponentRotation();
		//FActorSpawnParameters param=(FName("MyObject"),nullptr,this);
		GetWorld()->SpawnActor<AActor>(TrackRefToSpawn,SpawnLocation,SpawnRotation);
	}
}



void ATrack::DestroyTriggerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	const ATakang_Hero* Character=Cast<ATakang_Hero>(OtherActor);
	if(Character)
	{
		for(int32 index=0;index<CoinArray.Num();index++)
		{
			if(CoinArray[index]!=nullptr)
			{
				CoinArray[index]->Destroy();
			}
		}
		for(int32 index=0;index<HurdlesArray.Num();index++)
		{
			if(HurdlesArray[index]!=nullptr)
			{
				HurdlesArray[index]->Destroy();
			}
		}
		Destroy();
	}
}

void ATrack::ObjectsSpawn(USplineComponent* SplineRef)
{
	const int32 SplinePoints=SplineRef->GetNumberOfSplinePoints();
	const float val=SplinePoints*1.0f;
	
	
	for (int32 Start=0;Start<SplinePoints;Start++)
	{
//		GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT("No of sppline points: %f"),SplinePoints));
		FVector SplineTransform=SplineRef->GetTransformAtSplinePoint(Start,ESplineCoordinateSpace::World,false).GetLocation();	
		if(FMath::RandBool())
		{
			SplineTransform.X=SplineTransform.X+200.0f;
		}
		else
		{
				SplineTransform.X=SplineTransform.X-250.0f;
		}
//		SplineTransform.Y=SplineTransform.Y;
		SplineTransform.Z=SplineTransform.Z+40.0f;
		
		if(FMath::RandBool())
		{
			if(FMath::RandBool())
			{
				if(FMath::RandBool())
				{
					SpawnHurdles(SplineTransform,FRotator(0,0,0),true);
					continue;
				}
				else
				{
					SpawnHurdles(SplineTransform,FRotator(0,0,0),false);
					continue;
				}
			}
		}
		if(FMath::RandBool())
		{
			if(FMath::RandBool())
			{
				if(FMath::RandBool())
				{
					SpawnRockets(SplineTransform,FRotator(0,0,0),true);
					continue;
				}
				else
				{
					SpawnRockets(SplineTransform,FRotator(0,0,0),false);
					continue;
				}
			}
		}
		SpawnCoins(SplineTransform,FRotator(0,0,0));
	}
	
}

void ATrack::SpawnCoins(FVector SpawnLocation,FRotator SpawnRotation)
{
	if(CoinRef)
	{
		HurdleRef=CoinRef;
		AHurdles_Parent* Obj=GetWorld()->SpawnActor<AHurdles_Parent>(CoinRef,SpawnLocation,SpawnRotation);
		CoinArray.Add(Obj);
		Obj->MyHurdleType=EHurdleType::Coin;
	}
}

void ATrack::SpawnRockets(FVector SpawnLocation,FRotator SpawnRotation, bool Rocket)
{
	if(RocketRef)
	{
		
		//AHurdles_Parent* Obj=(GetWorld()->SpawnActor<AHurdles_Parent>(HurdleRef,SpawnLocation,SpawnRotation));
	//	HurdlesArray.Add(Obj);
	}
	if(Rocket)
	{
		ExtraRef=RocketRef;
	}
	else
	{
		ExtraRef=BoardRef;
	}
	if(ExtraRef)
	{
		
		AHurdles_Parent* Obj=(GetWorld()->SpawnActor<AHurdles_Parent>(ExtraRef,SpawnLocation,SpawnRotation));
		if(Rocket)
		{
			Obj->MyHurdleType=EHurdleType::Rocket;
		}
		else
		{
			Obj->MyHurdleType=EHurdleType::SkateBoard;
		}
		

		
		CoinArray.Add(Obj);
	}
}

void ATrack::SpawnHurdles(FVector SpawnLocation,FRotator SpawnRotation, bool Stone)
{
	if(Stone)
	{
		HurdleRef=StoneRef;
	}
	else
	{
		HurdleRef=BranchRef;
	}
	if(HurdleRef)
	{
		AHurdles_Parent* Obj=(GetWorld()->SpawnActor<AHurdles_Parent>(HurdleRef,SpawnLocation,SpawnRotation));
		if(Stone)
		{
			Obj->MyHurdleType=EHurdleType::Stone;
		}
		else
		{
			Obj->MyHurdleType=EHurdleType::Branch;
		}

		
		HurdlesArray.Add(Obj);
	}
}

void ATrack::MoveCoinsUp(bool bIsJetPack)
{
	/*if(bIsJetPack)
	{
				
		for (int32 Index=0 ; CoinArray.Num();Index++)
		{
			
			if(CoinArray[Index]!=nullptr)
			{
				CoinArray[Index]->SetActorLocation(FVector(CoinArray[Index]->GetActorLocation().X,CoinArray[Index]->GetActorLocation().Y,2000));
			}
		}
	}
	else
	{
		for (int32 Index=0 ; CoinArray.Num();Index++)
		{
			
			if(CoinArray[Index]!=nullptr)
			{
				CoinArray[Index]->SetActorLocation(FVector(CoinArray[Index]->GetActorLocation().X,CoinArray[Index]->GetActorLocation().Y,2000));
			}
		}
	}*/
}

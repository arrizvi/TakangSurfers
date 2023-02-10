// Fill out your copyright notice in the Description page of Project Settings.


#include "Takang_Hero.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATakang_Hero::ATakang_Hero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm1=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm1"));
	SpringArm1->bUsePawnControlRotation=false;
	SpringArm1->TargetArmLength=506.53f;
	SpringArm1->SetRelativeLocation(FVector(0,0,70));	
	SpringArm1->SetupAttachment(GetCapsuleComponent());
	Camera1=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	Camera1->SetupAttachment(SpringArm1);
	Camera1->SetFieldOfView(70);
	Camera1->SetRelativeLocation(FVector(-5.2,0,40));
	Board1=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board1"));
	Board1->SetupAttachment(GetMesh());
	Board1->SetRelativeLocation(FVector(-12.53,-66.85,2.45));
	Board1->SetRelativeRotation(FRotator(0.02,0.02,0.02));
	Board1->SetRelativeScale3D(FVector(0.02,0.02,0.02));
	Board1->SetVisibility(false);
	FName BoardSocketName="HoverBoardSocket";
	//Board1->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BoardSocketName);
	Rocket1=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket1"));
	Rocket1->SetupAttachment(GetMesh());
	Rocket1->SetRelativeLocation(FVector(1.54,12.99,0.113));
	Rocket1->SetRelativeRotation(FRotator(-93.42,-1.31,-348.96));
	Rocket1->SetVisibility(false);
	//FName RocketSocketName="HoverBoardSocket";
	//Rocket1->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RocketSocketName);
	RocketSparks=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RocketSparks"));
	RocketSparks->SetupAttachment(Rocket1);
	RocketSparks->bAutoActivate=false;
	RocketSparks->SetComponentTickEnabled(false);
	GetMesh()->SetRelativeRotation(FRotator(0,0,0));
	
	

}

void ATakang_Hero::AddNewMesh()
{
	GetMesh()->SetSkeletalMesh(AllCharactersArray[SelectedCharacterNumber]);
	
}

// Called when the game starts or when spawned
void ATakang_Hero::BeginPlay()
{
	Super::BeginPlay();

	bisSliding=false;
	bIsAliveNow=true;
	bJetPack1=false;
	bHoverBoard1=false;
	bCanGoToOther=true;
	//UAudioComponent* Sound=BackgroundSound;
	//BackgroundSound->SetVolumeMultiplier(1.0f);
	//BackgroundSound->SetPitchMultiplier(1.0f);
	//BackgroundSound->Play();
	bIsAliveNow=true;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATakang_Hero::AddCoins,2.0f,false);
	MovementComponent=GetCharacterMovement();
}

// Called every frame
void ATakang_Hero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VirtualTick();

	if(bIsAliveNow)
	{
		if(bJetPack1|| bHoverBoard1)
		{
			FVector NewLocation=FVector(GetCapsuleComponent()->GetComponentLocation().X,GetCapsuleComponent()->GetComponentLocation().Y,NewLoactionofZ);
			GetCapsuleComponent()->SetWorldLocation(NewLocation,true,0);
		}
		float ZVal=GetControlRotation().Yaw;
		AddMovementInput(GetActorForwardVector()*1.0f);
	}
}
// Called to bind functionality to input
void ATakang_Hero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("JumpSlide",this,&ATakang_Hero::JumpAndSlide);
	PlayerInputComponent->BindAxis("LeftRightMovement",this,&ATakang_Hero::MovementDecision);
	PlayerInputComponent->BindAction("Finger",IE_Pressed,this,&ATakang_Hero::FingerPressed);
	PlayerInputComponent->BindAction("Finger",IE_Released,this,&ATakang_Hero::FingerReleased);
}
void ATakang_Hero::AddCoins()
{
	if(bIsAliveNow)
	{
		CoinScore=CoinScore+1;
	}
}
void ATakang_Hero::JumpAndSlide(float AxisValue)
{
	if(AxisValue==1)
	{
//		GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" %f"),AxisValue));
		Jump();
	}
	else if(AxisValue==-1)
	{
		CharacterCrouch();
		//GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" %f"),AxisValue));
	}
	else
	{
		
	}
}

void ATakang_Hero::CharacterCrouch()
{
		Crouch();
		bisSliding=true;
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATakang_Hero::CharacterUnCrouch,.075f,false);
}
void ATakang_Hero::CharacterUnCrouch()
{
		UnCrouch();
		bisSliding=false;
}

void ATakang_Hero::IncreaseSpeed()
{
	MovementComponent->MaxWalkSpeed=MovementComponent->MaxWalkSpeed*2.0f;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATakang_Hero::DecreaseSpeed,3.0f,false);
}

void ATakang_Hero::DecreaseSpeed()
{
	MovementComponent->MaxWalkSpeed=MovementComponent->MaxWalkSpeed*0.50f;
}

void ATakang_Hero::JetPackStart()
{
	if(bCanGoToOther)
	{
		bJetPack1=true;
		NewLoactionofZ=2000.0f;
		bCanGoToOther=false;
		Rocket1->SetVisibility(true);
		RocketSparks->SetActive(true);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATakang_Hero::DeActiveJet,5.0f,false);
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATrack::StaticClass(), FoundActors);
		for(int32 Index=0;Index<FoundActors.Num();Index++)
		{
			ATrack* Track=Cast<ATrack>(FoundActors[Index]);
			Track->MoveCoinsUp(true);
		}
	}
}

void ATakang_Hero::DeActiveJet()
{
	Rocket1->SetVisibility(false);
	RocketSparks->SetActive(false);
	GetCapsuleComponent()->SetWorldLocation(FVector(GetCapsuleComponent()->GetComponentLocation().X,GetCapsuleComponent()->GetComponentLocation().Y,1500));
	bJetPack1=false;
	bCanGoToOther=true;
	//ATrack::MoveCoinsUp(false);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATrack::StaticClass(), FoundActors);
	for(int32 Index=0;Index<FoundActors.Num();Index++)
	{
		ATrack* Track=Cast<ATrack>(FoundActors[Index]);
		Track->MoveCoinsUp(false);
	}
}

void ATakang_Hero::HoverBoardStart()
{
	if(bCanGoToOther)
	{
		bHoverBoard1=true;
		NewLoactionofZ=300.0f;
		bCanGoToOther=false;
		Board1->SetVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATakang_Hero::DeActiveJet,5.0f,false);
	}
}

void ATakang_Hero::DeActiveHover()
{
	bHoverBoard1=false;
	Board1->SetVisibility(false);
	NewLoactionofZ=145.0f;
	bCanGoToOther=true;
}

void ATakang_Hero::HurdleOverlapped()
{
	if(bCanGoToOther)
	{
		bIsAliveNow=false;
		PlayDeath();
	}
}

void ATakang_Hero::MovementDecision(float Val)
{
	if(Val==1)
	{
		//GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" %f"),Val));
		MoveRight();
	}
	else if(Val==-1)
	{
	//	GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" %f"),Val));
		MoveLeft();
	}
	else
	{
		
	}
}

void ATakang_Hero::FingerPressed()
{
	bIsPressed=true;
	//ETouchIndex::Type FingerIndex;
	//FVector Location;
	bool bInd=false;
	GetWorld()->GetFirstPlayerController()->GetInputTouchState(ETouchIndex::Touch1,TouchStart.X,TouchStart.Y,bInd);
	if(!(GetCharacterMovement()->IsFalling()))
	{
		FingerReleased();
	}
}

void ATakang_Hero::FingerReleased()
{
	bIsPressed=false;
	bCanExecuteTick=true;
	
}

void ATakang_Hero::VirtualTick()
{
	if(bIsPressed)
	{
//		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bInd;
		GetWorld()->GetFirstPlayerController()->GetInputTouchState(ETouchIndex::Touch1,TouchEnd.X,TouchEnd.Y,bInd);
		FVector2D finalVector=TouchStart-TouchEnd;
		float VectorLength=finalVector.Size();
		if(VectorLength>100)
		{
			if(bCanExecuteTick)
			{
				
				if(FMath::Abs(finalVector.X)>FMath::Abs(finalVector.Y))
				{
					if(finalVector.X>0)
					{
						MoveLeft();
					}
					else
					{
						MoveRight();
					}
				}
				else
				{
					if(finalVector.Y>0)
					{
						Jump();
					}
					else
					{
						Crouch();
					}
				}
				bCanExecuteTick=false;
			} 
		}
	}
}
bool ATakang_Hero::CanMoveRight()
{
	if(Count>=0)
	{
		GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" Moving Right")));
		return false;
	}
	return true;
}
bool ATakang_Hero::CanMoveLeft()
{
	if(Count<=-1)
	{
		return false;
	}
	return true;
}
void ATakang_Hero::MoveLeft()
{
	if(CanMoveLeft())
	{
		GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" Moving Right")));
		Jump();
		FVector CharacterLocation=GetActorLocation();
		//something
		XValue=CharacterLocation.X;
		float LerpValue;
		XValue=CharacterLocation.X;
		bool bDoOnce=true;
		if(bDoOnce)
		{
			LerpValue=CharacterLocation.X;
			bDoOnce=false;
		}
		//Make the time line and do all these in that
		{
			LerpValue=FMath::Lerp(XValue,XValue+JumpDistance,0.08f);
		SetActorLocation(FVector(LerpValue,CharacterLocation.Y,CharacterLocation.Z));
		StopJumping();
	}		

		Count-=1;
		
		bDoOnce=true;
	}
}
void ATakang_Hero::MoveRight()
{
	if(CanMoveRight())
	{
		GEngine->AddOnScreenDebugMessage(1,15.0f,FColor::Green,FString::Printf(TEXT(" Moving Right")));
		Jump();
		FVector CharacterLocation=GetActorLocation();
		float LerpValue;
		XValue=CharacterLocation.X;
		bool bDoOnce=true;
		if(bDoOnce)
		{
			LerpValue=CharacterLocation.X;
			bDoOnce=false;
		}
		//Make the time line and do all these in that
		{
			LerpValue=FMath::Lerp(XValue,XValue-JumpDistance,0.08f);
			SetActorLocation(FVector(LerpValue,CharacterLocation.Y,CharacterLocation.Z));
			StopJumping();
		
		}
		Count+=1;
		bDoOnce=true;
	}
}



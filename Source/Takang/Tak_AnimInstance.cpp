// Fill out your copyright notice in the Description page of Project Settings.


#include "Tak_AnimInstance.h"

#include "Takang_Hero.h"

UTak_AnimInstance::UTak_AnimInstance()
{
	bIsAlive=true;
	bIsHoverBoard=false;
	bIsJetPack=false;
	bIsJumping=false;
	bIsSliding=false;
}

void UTak_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	Super::NativeUpdateAnimation(DeltaSeconds);
	AActor* OwningActor=GetOwningActor();
	if(OwningActor!=nullptr)
	{
		ATakang_Hero* TakCharacter=Cast<ATakang_Hero>(OwningActor);
		if(TakCharacter)
		{
			bIsAlive=TakCharacter->bIsAliveNow;
			bIsHoverBoard=TakCharacter->bHoverBoard1;
			bIsJetPack=TakCharacter->bJetPack1;
			bIsJumping=TakCharacter->bPressedJump;
			bIsSliding=TakCharacter->bisSliding;
		}
	}
}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Takang_Menu.generated.h"

/**
 * 
 */
UCLASS()
class TAKANG_API UTakang_Menu : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UCanvasPanel* MainCanvas;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* BackButton;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* BackgroundImage;
	

	//Main Screen
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* CharacterSelectionBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* SettingsBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* PlayBtnMain;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* LogoName;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* PointsImgBG;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* Points;

	//InGame Screen
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* PauseBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* SettingBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* Coins;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* PointsImgBGInGame;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* TotalPoints;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* CoinsImgInGame;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* TotalCoinsInGame;
	
	//Character Selection Screen
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* ForwadButton;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* BackwardButton;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* CharacterSelectoinImage;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* CharacterImage;


	//Game Over
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* GameOverImageBG;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* GameCoinsBG;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* GamePointsBG;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* GamePoints;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* GameCoins;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* RestartButton;

	//Settings Screen
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* GameSettingsImgBG;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UCheckBox* MusicCheckBox;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UCheckBox* SoundCheckBox;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* MusicBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* SoundBtn;
	
	//Pause Game Screen


	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* PauseGameScreenBG;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* PlayBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* HomeBtn;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* RestartBtn;
};

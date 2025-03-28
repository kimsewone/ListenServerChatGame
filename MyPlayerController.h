// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/DelegateCombinations.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartProgressBar);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnStartProgressBar, float, CloseTime, float, FixStartTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStartProgressBar, float, TimeLength, float, FixStartTime);

UCLASS()
class SAMPLECHAT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	AMyPlayerController();
	void BeginPlay() override;


	UPROPERTY( BlueprintReadWrite, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))//
	bool  bGameStartTime;

	UPROPERTY(BlueprintAssignable)//UPROPERTY(BlueprintAssignable)
	FOnStartProgressBar OnStartProgressBarDelegate;

	//UPROPERTY( BlueprintReadWrite, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))//
	//	bool  bNGameStart;


	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void CloseProgressBarEvent2();

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void StartProgressBar();

protected:

};



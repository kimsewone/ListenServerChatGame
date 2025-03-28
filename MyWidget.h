// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.generated.h"


class UTextBlock;
class UProgressBar;
class UImage;
UCLASS()
class SAMPLECHAT_API UMyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void SetProgressBar(float CurrentHealth, float MaxHealth);
	//void SetTestText(int CurrentAmmo);

	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void StartProgressBarTime(float CloseTime, float FixStartTime);

	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void StopProgressBar();

	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void ShowOutImage(bool Result);
	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void ShowWinImage();

	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void ChangeImageZOrder(UImage* TargetImage, int32 NewZOrder);

	

	UFUNCTION(BlueprintCallable, Category = "GamePlayUi")
	void SetImageByPath(int32 lmgIdx);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OutImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlayUi")
	bool bOut;

	//UPROPERTY(EditAnywhere, meta = (BindWidget))
	//UTextBlock* TestText;

private:
	void LoadTextureFromPath();

	TArray<TObjectPtr<UTexture2D>> TextureArray;

	float ProgressBarTime = 0.f;
	float ProgressBarCloseTime = 0.f;
	bool bProgressBarTime = false;
	float TickDelay = 0.1f;  
	float TickElapsed = 0.f;
	FTimerHandle ProgressBarTimerHandler;
};

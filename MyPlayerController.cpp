// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyWidget.h"

AMyPlayerController::AMyPlayerController()
{
	
}
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

}
void AMyPlayerController::StartProgressBar()
{
	OnStartProgressBarDelegate.Broadcast(10.f, 0.f);
}
void AMyPlayerController::CloseProgressBarEvent2()
{
	bGameStartTime = false;
}

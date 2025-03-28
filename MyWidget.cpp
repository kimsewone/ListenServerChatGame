// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "MyPlayerController.h"
#include <Components/Image.h>
//#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Styling/SlateBrush.h"

void UMyWidget::NativeConstruct()
{
    Super::NativeConstruct();

    AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetOwningPlayer());
    if (MyPC)
    {
        MyPC->OnStartProgressBarDelegate.AddDynamic(this, &UMyWidget::StartProgressBarTime);
    }
    bOut = false;
    LoadTextureFromPath();
}
void UMyWidget::SetProgressBar(float CurrentHealth, float MaxHealth)
{
	if(ProgressBar)
		ProgressBar->SetPercent(CurrentHealth / MaxHealth);
}

void UMyWidget::StartProgressBarTime(float CloseTime, float FixStartTime)
{
    ProgressBarCloseTime = CloseTime;
    ProgressBarTime = CloseTime;
    TickDelay = 0.05f;
    TickElapsed = 0.f;
    bProgressBarTime = true;

    return;
    /*
    GetWorld()->GetTimerManager().SetTimer(
        ProgressBarTimerHandler, ([this,CloseTime]() {
            float Delta = GetWorld()->GetDeltaSeconds();
            ProgressBarTime -= Delta;

            if (0.f >= ProgressBarTime)
            {
                APlayerController* PC = GetOwningPlayer();
                if (PC)
                {
                    AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
                    if (MyPC)
                        MyPC->CloseProgressBarEvent2();
                }
                GetWorld()->GetTimerManager().ClearTimer(ProgressBarTimerHandler);
            }
            else
            {
                float BarValue = FMath::Clamp(ProgressBarTime/CloseTime, 0.f, 1.f);
                ProgressBar->SetPercent(BarValue);//SetPercent(FMath::Clamp( 1.f - GetWorld()->GetDeltaSeconds(), 0.f, 1.f) );
                UE_LOG(LogTemp, Warning, TEXT("BarValue! : %f, DeltaTime : %f"), BarValue, Delta);
            }
            
            }), 0.01f, true);
            */

}

void UMyWidget::StopProgressBar()
{
    bProgressBarTime = false;
}

void UMyWidget::ShowOutImage(bool Result)
{
    bOut = Result;
    if (OutImage)
    {
        float Alpha = 1.f;
        if (!bOut)
        {
            Alpha = 0.f;
            ChangeImageZOrder(OutImage ,-1);
        }
        else
        {
            SetImageByPath(0);
            ChangeImageZOrder(OutImage, 10);
        }
    
        FLinearColor NewColor = OutImage->ColorAndOpacity;
        NewColor.A = Alpha;
        OutImage->SetColorAndOpacity(NewColor);
    }
}
void UMyWidget::ShowWinImage( )
{
    SetImageByPath(1);
    ChangeImageZOrder(OutImage, 10);

    float Alpha = 1.f;
    FLinearColor NewColor = OutImage->ColorAndOpacity;
    NewColor.A = Alpha;
    OutImage->SetColorAndOpacity(NewColor);
}
void UMyWidget::ChangeImageZOrder(UImage* TargetImage, int32 NewZOrder)
{
    if (!TargetImage) return;

    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TargetImage->Slot))
    {
        CanvasSlot->SetZOrder(NewZOrder);
    }
}
void UMyWidget::LoadTextureFromPath()
{
    FString Paths[] = 
    {
        TEXT("/Game/OUT.OUT"),
        TEXT("/Game/WIN.WIN")
    };
    for (int32 i = 0; i < UE_ARRAY_COUNT(Paths);++i)
    {
        UTexture2D* LoadImg = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *Paths[i]));
       if(LoadImg)
            TextureArray.Add(LoadImg);
    }
   // return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *Path));
}
void UMyWidget::SetImageByPath( int32 lmgIdx)
{
    UTexture2D* Texture =TextureArray[lmgIdx];
    if (Texture && OutImage)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(Texture);
        OutImage->SetBrush(Brush);
    }
}
void UMyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (!bProgressBarTime || bOut)
        return;

    TickElapsed += InDeltaTime;
    if (TickElapsed < TickDelay)
        return;

    ProgressBarTime -= TickElapsed;
    TickElapsed = 0.f;

    if (0.f >= ProgressBarTime)
    {
        APlayerController* PC = GetOwningPlayer();
        if (PC)
        {
            AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
            if (MyPC)
                MyPC->CloseProgressBarEvent2();
        }
        bProgressBarTime = false;
    }
    else
    {
        float BarValue = FMath::Clamp(ProgressBarTime / ProgressBarCloseTime, 0.f, 1.f);
        ProgressBar->SetPercent(BarValue);//SetPercent(FMath::Clamp( 1.f - GetWorld()->GetDeltaSeconds(), 0.f, 1.f) );
       // UE_LOG(LogTemp, Warning, TEXT("BarValue! : %f, DeltaTime : %f"), BarValue, InDeltaTime);
    }

}
//void UMyWidget::SetTestText(int CurrentAmmo)
//{
//	if (TestText)
//		TestText->SetText(FText::FromString(FString::Printf(TEXT("%u"), CurrentAmmo)));
//}

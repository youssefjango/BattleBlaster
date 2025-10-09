// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessageUI.h"

void UScreenMessageUI::SetMessageUI(FString Message)
{
	FText MessageText = FText::FromString(Message);
	CountDownTxt->SetText(MessageText);
}

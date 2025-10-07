// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UBattleBlasterGameInstance::LoadNextLevel()
{
	if (CurrentLevelIndex <= TotalNumOfLevels) {
		ChangeLevel(CurrentLevelIndex + 1);
	}
	else {
		RestartGame();
	}
}
void UBattleBlasterGameInstance::RestartGame()
{
	ChangeLevel(1);
}
void UBattleBlasterGameInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrentLevelIndex);
}







void UBattleBlasterGameInstance::ChangeLevel(int32 Index)
{
	if (Index > 0 && Index <= TotalNumOfLevels) {
		CurrentLevelIndex = Index;

		FString LevelName = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
	}
}

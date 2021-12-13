// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;
	void InitGame();
	void EndGame(bool WonGame);
	void ProcessGuess(const FString &Guess);
	static bool IsIsogram(const FString &Word);
	void GetBullCows(const FString &Guess) const;

	// Your declarations go below!
private:
	FString HiddenWord;
	FString GuessWord;
	int32 NumLives;
	int32 RandomNum;
	bool bGameOver;
	TArray<FString> SecretWords;
	TArray<FString> Isograms;

	void ReduceNumLives();
	int32 GetNumLives();
	// void GetValidWords(const TArray<FString> &WordList);
};

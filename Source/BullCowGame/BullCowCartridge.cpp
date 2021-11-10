// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine("Hello. Welcome to the \"Bulls and Cows\" game");
    PrintLine("Please enter a word");
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("Alien");
    // PrintLine(HiddenWord);
}

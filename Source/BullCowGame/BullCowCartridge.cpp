// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame(); // Set up the game
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
    else
    {

        if (Input == HiddenWord)
        {
            PrintLine(TEXT("Congrats! You guessed the hidden word"));
            EndGame();
        }
        else
        {
            ReduceNumLives();
            PrintLine(TEXT("You did not guess the hidden word"));
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i letters long. Try again"), HiddenWord.Len());
            }
            PrintLine(TEXT("You have %i lives left"), GetNumLives());

            if (GetNumLives() == 0)
            {
                EndGame();
            }
        }
    }
    // }
    // PrintLine(TEXT("You have run out of lives"));
}

void UBullCowCartridge::InitGame()
{
    PrintLine(TEXT("Hello. Welcome to the \"Bulls and Cows\" game"));

    NumLives = 5;                  // Set Lives
    HiddenWord = TEXT("Alienbro"); // Set Hidden Word
    bGameOver = false;             // Set GameOver to false;

    PrintLine(TEXT("You have %i lives left"), GetNumLives());
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Please enter a word as your guess"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::GameLoop()
{
}

void UBullCowCartridge::ReduceNumLives()
{
    NumLives--;
}
int UBullCowCartridge::GetNumLives()
{
    return NumLives;
}

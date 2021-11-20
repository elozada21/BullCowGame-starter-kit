// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(SecretWords, *WordListPath);

    GetValidWords(SecretWords);

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
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    PrintLine(TEXT("Hello. \nWelcome to the \"Bulls and Cows\" game"));
    RandomNum = rand() % ValidWords.Num();

    HiddenWord = ValidWords[RandomNum]; // Set Hidden Word
    NumLives = HiddenWord.Len();        // Set Lives
    bGameOver = false;                  // Set GameOver to false;

    PrintLine(TEXT("You have %i lives left"), GetNumLives());
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Please enter a word as your guess"));
}

void UBullCowCartridge::EndGame(bool Won)
{
    bGameOver = true;
    ClearScreen();
    if (Won)
    {
        PrintLine(TEXT("Congrats! You guessed the hidden word"));
    }
    else
    {
        PrintLine(TEXT("You have run out of lives."));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
    }
    ValidWords.RemoveAt(RandomNum);
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::ReduceNumLives()
{
    NumLives--;
}

int UBullCowCartridge::GetNumLives()
{
    return NumLives;
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (Guess == HiddenWord)
    {
        EndGame(true);
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long. Try again"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("This guess is not an isogram"));
        return;
    }

    //Check how many letters are in the correct position and correct letters in wrong position

    ReduceNumLives();
    PrintLine(TEXT("You have lost a life"));

    if (GetNumLives() == 0)
    {
        EndGame(false);
        return;
    }

    PrintLine(TEXT("Guess again, you have %i lives left"), GetNumLives());
}

bool UBullCowCartridge::IsIsogram(const FString Word) const
{
    bool Letters[26] = {false};

    TCHAR Letter;
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        Letter = tolower(Word[Index]);

        if (!isalpha(Letter) || Letters[(Letter - 'a')])
        {
            return false;
        }
        Letters[Letter - 'a'] = true;
    }
    return true;
}

void UBullCowCartridge::GetValidWords(TArray<FString> WordList)
{
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace((Word));
        }
    }
}

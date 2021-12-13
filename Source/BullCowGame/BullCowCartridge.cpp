// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString &Word)
                                                    { return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word); });

    // GetValidWords(SecretWords);

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
    RandomNum = FMath::RandRange(0, Isograms.Num() - 1);

    HiddenWord = Isograms[RandomNum]; // Set Hidden Word
    NumLives = HiddenWord.Len();      // Set Lives
    bGameOver = false;                // Set GameOver to false;

    PrintLine(TEXT("You have %i lives left"), GetNumLives());
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Please enter a word as your guess"));
}

void UBullCowCartridge::EndGame(bool WonGame)
{
    bGameOver = true;
    ClearScreen();
    if (WonGame)
    {
        PrintLine(TEXT("Congrats! You guessed the hidden word"));
    }
    else
    {
        PrintLine(TEXT("You have run out of lives."));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
    }
    Isograms.RemoveAt(RandomNum);
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

    ReduceNumLives();
    PrintLine(TEXT("You have lost a life"));

    if (GetNumLives() == 0)
    {
        EndGame(false);
        return;
    }

    //Check how many letters are in the correct position and correct letters in wrong position
    GetBullCows(Guess);

    PrintLine(TEXT("Guess again, you have %i lives left"), GetNumLives());
}

void UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    bool Letters[26] = {false};

    TCHAR Letter;
    int32 CorrectSpots = 0;
    int32 CorrectLetters = 0;
    for (int32 Index = 0; Index < HiddenWord.Len(); Index++)
    {
        Letter = tolower(HiddenWord[Index]);
        Letters[Letter - 'a'] = true;
    }

    for (int32 Index = 0; Index < HiddenWord.Len(); Index++)
    {
        Letter = tolower(Guess[Index]);

        if (Letter == tolower(HiddenWord[Index]))
        {
            CorrectSpots++;
        }
        else if (Letters[Letter - 'a'])
        {
            CorrectLetters++;
        }
    }

    PrintLine(TEXT("There are %i Bull(s)"), CorrectSpots);
    PrintLine(TEXT("and %i Cow(s)."), CorrectLetters);
}

bool UBullCowCartridge::IsIsogram(const FString &Word)
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

// void UBullCowCartridge::GetValidWords(const TArray<FString> &WordList)
// {
//     for (FString Word : WordList)
//     {
//         if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
//         {
//             Isograms.Emplace((Word));
//         }
//     }
// }

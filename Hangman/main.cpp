//----------------------------------------------------
// File:        Hangman.cpp
// By:          Tyson Drake
// Date:        03 November 2022
// This program runs a version of hangman with 10 preset words.

//----------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>

using namespace std;

//Function prototype
void printProgress(int correct_letters,
                   int incorrect_letters,
                   vector<char> finalGuess,
                   vector <char> incorrectGuesses);

int main()
{
    //Initialize variables
    int correct, incorrect;         //Sets both counters to 0 at the start of the game
    char guess, underscore('_');    //Guess is the letter the player guesses, underscore is underscore
    bool playGame = true;           //When true, the game is played
    string playAgain;               //Players answer for if they want to play again
    string word;                    //Word selected by the program

    vector <char> finalGuess;            //Printed word. First as blanks then it gets filled in
    vector <char> incorrectGuesses;     //Incorrect Guesses

    //Define playable words
    vector <string> words{"GIZMO",
                          "ICEBOX",
                          "PAJAMAS",
                          "JIGSAW",
                          "VOLLEYBALL",
                          "SPACESHIP",
                          "KANGAROO",
                          "LAWNMOWER",
                          "LIBRARY",
                          "JACKET"};

    while(playGame == true)
    {
       //Sets counters to 0
        correct = 0;
        incorrect = 0;
        incorrectGuesses.clear();

       //Welcome user to the game
        cout << "Welcome to Hangman!" << endl;
        sleep(1);
        cout << "The rules are simple: Guess one letter at a time to try and guess the word." << endl;
        cout << "You must enter each letter as an uppercase letter or it will count as an" << endl;
        cout << "incorrect letter automatically." << endl;
        sleep(4);
        cout << "Let's play!" << "\n\n";
        sleep(1);

        //Program selects a random word
        srand(time(NULL));
        int word_number = (rand() % 10)+1;
        word = words.at(word_number-1);


        //Indicate how many letters in the word
        int N = word.length();
        finalGuess.resize(N);
        cout << "This word has " << N << " letters:" << endl;
        for (int i = 0; i < N ; i++)
        {
            finalGuess[i] = '_';
        }

        //Print progress
        printProgress(correct, incorrect, finalGuess, incorrectGuesses);

        //If the word has not been guessed
        while(find(finalGuess.begin(), finalGuess.end(),underscore) != finalGuess.end())
        {
            //Prompt user to guess a letter
            cout << "Your guess (Please enter all guesses as uppercase letters) -> ";
            cin >> guess;
            cout << "\n" << "--------------------------------------------------------------" << "\n\n";

            //When letter guessed correctly fill in the blanks
            size_t letter = word.find(guess);
            if(letter != string::npos)
            {
                finalGuess[letter] = guess;
                for(int i = 0 ; i < N ; i++ )
                {
                    letter = word.find(guess, letter+1);
                    if (letter != string::npos)
                    {
                        finalGuess[letter] = guess;
                    }
                }
                correct++;
                printProgress(correct, incorrect, finalGuess, incorrectGuesses);
            }

            //When letter guessed incorrectly, place in incorrect section
            else
            {
                incorrect++;
                incorrectGuesses.push_back(guess);
                printProgress(correct, incorrect, finalGuess, incorrectGuesses);
            }
        }

        //List the total guesses and prompt user if they want to play again
        cout << "Congratulations you guessed the word in " << correct+incorrect << " guesses!" << "\n\n";
        sleep(1);
        cout << "Would you like to play again? (Please enter YES or NO)" << endl;
        cin >> playAgain;
        if (playAgain == "YES")
        {
            playGame = true;
            cout << "\n";
        }
        else
        {
            playGame = false;
            cout << "\n" << "Thanks for Playing!";
        }
    }

    return 0;
}

//Function to print out word progress and guess counts
void printProgress(int correct_letters,int incorrect_letters,vector<char> finalGuess,vector <char> incorrectGuesses)
{
    int N = finalGuess.size();
    int Z = incorrectGuesses.size();
    for (int i = 0; i < N; i++)
    {
        cout << finalGuess[i];
    }
    cout << "\n\n" << "Correct Guesses: " << correct_letters << endl;
    cout << "Incorrect Guesses: " << incorrect_letters << endl;
    cout << "Incorrect Letters: ";
    for (int i = 0; i < Z; i++)
    {
        cout << incorrectGuesses[i] << " ";
    }
    cout << "\n\n";
}

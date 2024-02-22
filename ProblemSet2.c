// Upper Case Program:
// ctype.h,string.h
// scrabble
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int score_tempelate[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int score_calculator(string word);
int main(void)
{
    string word_of_player_1 = get_string("Player 1: ");
    string word_of_player_2 = get_string("Player 2: ");

    int score_of_player_1 = score_calculator(word_of_player_1);
    int score_of_player_2 = score_calculator(word_of_player_2);

    if (score_of_player_1 > score_of_player_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score_of_player_2 > score_of_player_1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score_calculator(string word)
{
    int score = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        if (isupper(word[i]))
        {
            score += score_tempelate[word[i] - 'A'];
        }
        if (islower(word[i]))
        {
            score += score_tempelate[word[i] - 'a'];
        }
    }
    return score;
}

// Readability
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int letter_calculator(string User_given_text);
int sentence_calculator(string User_given_text);
int word_calculator(string User_given_text);

int main(void)
{
    string User_given_text = get_string("Text: ");

    float L = (float)letter_calculator(User_given_text) / (float)word_calculator(User_given_text) * 100;
    float S = (float)sentence_calculator(User_given_text) / (float)word_calculator(User_given_text) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int rounded_index = round(index);

    if (rounded_index > 1 && rounded_index < 16)
    {
        printf("\nGrade %i\n", rounded_index);
    }
    else if (round(index) >= 16)
    {
        printf("\nGrade 16+\n");
    }
    else
    {
        printf("\nBefore Grade 1\n");
    }
}

int letter_calculator(string User_given_text)
{
    int length = strlen(User_given_text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(User_given_text[i]))
        {
            count++;
        }
    }
    return count;
}

int sentence_calculator(string User_given_text)
{
    int length = strlen(User_given_text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (User_given_text[i] == '.' || User_given_text[i] == '!' || User_given_text[i] == '?')
        {
            if (User_given_text[i] == '.' && User_given_text[i + 1] == '.')
            {
                continue;
            }
            else
            {
                count++;
            }
        }
    }
    return count;
}

int word_calculator(string User_given_text)
{
    int length = strlen(User_given_text);
    int count = 0;
    bool dot_encountered = false;
    for (int i = 0; i < length; i++)
    {
        if (User_given_text[i] == ' ' || User_given_text[i] == '.')
        {
            if (User_given_text[i] == '.' && User_given_text[i + 1] == '.')
            {
                if (User_given_text[i - 1] == '.')
                {
                    count++;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                count++;
            }
        }
    }
    return count;
}

// Ceasar Cipher
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char ciphered_character(char Character, int key);
bool only_digits(string keys);

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (argc == 2)
    {
        if (only_digits(argv[1]) == true)
        {
            int key = atoi(argv[1]);
            string plaintext = get_string("Plain text: ");
            int length_of_text = strlen(plaintext);
            char ciphertext[length_of_text + 1];
            for (int i = 0; i < length_of_text; i++)
            {
                if (isalpha(plaintext[i]))
                {
                    ciphertext[i] = ciphered_character(plaintext[i], key);
                }
                else
                {
                    ciphertext[i] = plaintext[i];
                }
            }
            ciphertext[length_of_text] = '\0';
            printf("ciphertext: %s\n", ciphertext);
        }
        else
        {
            printf("string\n");
            return 1;
        }
    }
}

bool only_digits(string keys)
{
    int length = strlen(keys);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(keys[i]))
        {
            return false;
        }
    }
    return true;
}

char ciphered_character(char Character, int key)
{
    char ciphered_char;
    if (isupper(Character))
    {
        ciphered_char = ((Character - 'A' + key) % 26 + 'A');
    }
    else
    {
        ciphered_char = ((Character - 'a' + key) % 26 + 'a');
    }
    return ciphered_char;
}

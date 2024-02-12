// Contacts Program
#include <cs50.h>
#include <stdio.h>
int main(void)
{
    string first_name = get_string("give me first name: ");
    string last_name = get_string("give me last name: ");
    int age = get_int("give me your age: ");
    string Phone_num = get_string("give me phone-number: ");

    printf("Name,%s %s\nage: %i\n Phone:%s\n", first_name, last_name, age, Phone_num);
}

// Left-Align Pyramid
#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int n = get_int("give me an integer: ");
    int i = 1;
    while (i <= n)
    {
        for (int j = 0; j < i; j++)
        {
            printf("$");
        }
        printf("\n");
        i++;
    }
}

// Square
#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int n = 4;
    int j = 0;
    while (j < n)
    {
        for (int i = 0; i < n; i++)
        {
            printf("#");
        }
        printf("\n");
        j++;
    }
}

// Problem-Set-1
// Mario

//        #--7
//       ##--6
//      ###--5
//     ####--4
//    #####--3
//   ######--2
//  #######--1
// ########--0

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height_Of_Tree = get_int("Height: ");
    while (Height_Of_Tree < 1)
    {
        Height_Of_Tree = get_int("Height: ");
    }
    for (int i = 1; i <= Height_Of_Tree; i++)
    {
        for (int j = 0; j < Height_Of_Tree - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Cash
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int amount_of_user = get_int("Change owed: ");
    while (amount_of_user < 1)
    {
        amount_of_user = get_int("Change owed: ");
    }
    int count_of_coins = 0;

    while (amount_of_user > 0)
    {
        if (amount_of_user >= 25)
        {
            amount_of_user = amount_of_user - 25;
            count_of_coins += 1;
        }
        else if (amount_of_user >= 10)
        {
            amount_of_user = amount_of_user - 10;
            count_of_coins += 1;
        }
        else if (amount_of_user >= 5)
        {
            amount_of_user = amount_of_user - 5;
            count_of_coins += 1;
        }
        else
        {
            amount_of_user = amount_of_user - 1;
            count_of_coins += 1;
        }
    }
    printf("%i\n", count_of_coins);
}
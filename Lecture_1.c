// Contacts Program 
#include<cs50.h>
#include<stdio.h>
int main (void){
    string first_name  = get_string("give me first name: ");
    string last_name  = get_string("give me last name: ");
    int age  = get_int("give me your age: ");
    string Phone_num = get_string("give me phone-number: ");


    printf("Name,%s %s\nage: %i\n Phone:%s\n",first_name,last_name,age,Phone_num);
}

// Left-Align Pyramid
#include<cs50.h>
#include<stdio.h>
int main (void){
    int n = get_int("give me an integer: ");
    int i = 1;
    while(i<=n){
    for(int j=0;j<i;j++){
        printf("$");
    }
    printf("\n");
    i++;}
}

// Square
#include<cs50.h>
#include<stdio.h>
int main (void){
    int n = 4;
    int j = 0;
    while(j<n){
        for(int i = 0; i<n; i++)
        {
        printf("#");}
        printf("\n");
        j++;}
}

// Problem-Set-1
    
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 100 

struct  Account
{
    char accountNumber[20];
    char holderName[MAX_NAME_LENGTH];
    double balance;
};

struct  Account* createAccount(const char* accountNumber, const char* holderName);
void deposit (struct Account* account, double amount );
void withdraw(struct Account* account, double amount);
void displayAccount(const struct Account* account);

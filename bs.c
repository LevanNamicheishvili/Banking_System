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

int main()
{ 
    int numAccounts = 0;
    struct Account** accounts = (struct Account**)malloc(0);

    while(1) 
    { 
        printf("\n1. Create Account\n");
        printf("2. Login \n");
        printf("3. Exit\n");
        printf("Enter Your Choice : ");

        char option; 
        scanf("%c, &option");

        switch(option)
        {
            case '1' : 
            { 
                char accountNumber[20];
                char holderName[MAX_NAME_LENGTH];

                printf("Enter account number : ");
                scanf("%s", accountNumber);

                printf("Enter account holder number: "); 
                getchar();
                fgets(holderName, sizeof(holderName), stdin);
                holderName[strcspn(holderName, "\n")] = '\0';

                struct Account* newAccount = createAccount(accountNumber, holderName);
                if (newAccount) {
                    accounts = (struct Account**)realloc(accounts, (numAccounts + 1) * sizeof(struct Account*));
                    accounts[numAccounts] = newAccount;
                    numAccounts++;
                    printf("Account created successfully!\n");
                } else {
                    printf("Error: Maximum number of accounts reached.\n");
                }
                break;
            }
        }
    }
}

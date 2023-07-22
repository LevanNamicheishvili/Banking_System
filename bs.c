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

          switch (option) {
            case '1': {
                char accountNumber[20];
                char holderName[MAX_NAME_LENGTH];

                printf("Enter account number: ");
                scanf("%s", accountNumber);

                printf("Enter account holder name: ");
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
            case '2': {
                char accountNumber[20];
                printf("Enter account number: ");
                scanf("%s", accountNumber);

                struct Account* foundAccount = NULL;
                for (int i = 0; i < numAccounts; i++) {
                    if (strcmp(accountNumber, accounts[i]->accountNumber) == 0) {
                        foundAccount = accounts[i];
                        break;
                    }
                }

                if (foundAccount) {
                    printf("Login successful!\n");
                    loggedInMenu(foundAccount);
                } else {
                    printf("Invalid account number. Login failed.\n");
                }
                break;
            }
            case '3':
                printf("Exiting...\n");
                for (int i = 0; i < numAccounts; i++) {
                    free(accounts[i]);
                }
                free(accounts);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

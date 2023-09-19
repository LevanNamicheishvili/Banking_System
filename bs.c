#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

struct Account {
    char accountNumber[20];
    char holderName[MAX_NAME_LENGTH];
    double balance;
};

struct Account* createAccount(const char* accountNumber, const char* holderName);
void deposit(struct Account* account, double amount);
void withdraw(struct Account* account, double amount);
void displayAccount(const struct Account* account);
void loggedInMenu(struct Account* account);

int main() {
    int numAccounts = 0;
    struct Account** accounts = (struct Account**)malloc(0);

    while (1) {
        printf("\n1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter Your Choice : ");

        char option;
        scanf(" %c", &option);

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

struct Account* createAccount(const char* accountNumber, const char* holderName) {

    struct Account* newAccount = (struct Account*)malloc(sizeof(struct Account));
    if (newAccount) {
        strncpy(newAccount->accountNumber, accountNumber, sizeof(newAccount->accountNumber) - 1);
        strncpy(newAccount->holderName, holderName, sizeof(newAccount->holderName) - 1);
        newAccount->accountNumber[sizeof(newAccount->accountNumber) - 1] = '\0';
        newAccount->holderName[sizeof(newAccount->holderName) - 1] = '\0';
        newAccount->balance = 0.0;
        return newAccount;
    }
    return NULL;
}

void deposit(struct Account* account, double amount) {
    account->balance += amount;
}

void withdraw(struct Account* account, double amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
    } else {
        printf("Insufficient balance to withdraw.\n");
    }
}

void displayAccount(const struct Account* account) {
    printf("Account Number: %s\n", account->accountNumber);
    printf("Holder Name: %s\n", account->holderName);
    printf("Balance: %.2lf\n", account->balance);
}

void loggedInMenu(struct Account* account) {
    while (1) {
        printf("\nLogged In Menu\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Display Account\n");
        printf("4. Logout\n");
        printf("Enter Your Choice : ");

        char option;
        scanf(" %c", &option);

        switch (option) {
            case '1': {
                double amount;
                printf("Enter the amount to deposit: ");
                scanf("%lf", &amount);
                deposit(account, amount);
                printf("Deposit successful!\n");
                break;
            }
            case '2': {
                double amount;
                printf("Enter the amount to withdraw: ");
                scanf("%lf", &amount);
                withdraw(account, amount);
                break;
            }
            case '3':
                displayAccount(account);
                break;
            case '4':
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

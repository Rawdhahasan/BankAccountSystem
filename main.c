/* main.c - Member 1 (Alif): Menus */
#include "bank.h"

struct Account accounts[MAX_ACCOUNTS];
int account_count = 0;
struct Transaction *logs[MAX_ACCOUNTS];

int main()
{
    int choice;
    int i;

    load_from_file();

    while (1) {
        printf("\n===== BANK MAIN MENU =====\n");
        printf("1. Open new account\n");
        printf("2. Login\n");
        printf("0. Exit\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');      /* throw away the wrong input */
            printf("Please enter a number.\n");
            continue;
        }

        switch (choice) {
        case 1:
            open_account();
            break;
        case 2:
            i = login();
            if (i != -1)
                account_menu(i);            /* only reached with the correct PIN */
            break;
        case 0:
            save_to_file();
            free_logs();
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void account_menu(int i)
{
    int choice;

    while (1) {
        printf("\n--- Account %u | %s | Balance: %.2f ---\n",
               accounts[i].acc_no, accounts[i].holder_name, accounts[i].balance);
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Transfer\n");
        printf("4. Print statement\n");
        printf("0. Logout\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Please enter a number.\n");
            continue;
        }

        switch (choice) {
        case 1:
            deposit(i);
            break;
        case 2:
            withdraw(i);
            break;
        case 3:
            transfer_funds(i);
            break;
        case 4:
            print_statement(i);
            break;
        case 0:
            printf("Logged out.\n");
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

/* account.c - Member 2 (Jumma): Accounts and PIN */
#include "bank.h"

/* Turns the PIN into a number so the real PIN is never saved */
void hash_pin(unsigned int acc_no, char pin[], char result[])
{
    unsigned int hash;
    int k;

    hash = acc_no;
    for (k = 0; pin[k] != '\0'; k++)
        hash = hash * 31 + pin[k];

    sprintf(result, "%u", hash);
}

/* Returns the position of the account in the array, or -1 if not found */
int find_account(unsigned int acc_no)
{
    int i;

    for (i = 0; i < account_count; i++) {
        if (accounts[i].acc_no == acc_no)
            return i;
    }
    return -1;
}

void open_account()
{
    char pin[10];
    double amount = 0;
    int i, k;

    if (account_count == MAX_ACCOUNTS) {
        printf("Bank is full.\n");
        return;
    }

    i = account_count;
    accounts[i].acc_no = 1001 + i;

    printf("Enter full name: ");
    scanf(" %49[^\n]", accounts[i].holder_name);   /* reads the whole line, spaces too */

    printf("Choose a 4-digit PIN: ");
    scanf("%9s", pin);
    if (strlen(pin) != 4) {
        printf("PIN must be exactly 4 digits.\n");
        return;
    }
    for (k = 0; k < 4; k++) {
        if (pin[k] < '0' || pin[k] > '9') {
            printf("PIN must be digits only.\n");
            return;
        }
    }

    printf("Opening deposit: ");
    scanf("%lf", &amount);
    if (amount < 0) {
        printf("Amount cannot be negative.\n");
        return;
    }

    accounts[i].balance = amount;
    hash_pin(accounts[i].acc_no, pin, accounts[i].pin_hash);
    logs[i] = NULL;                  /* new account starts with an empty list */
    account_count++;

    add_transaction(i, "Opening", amount, amount);
    save_to_file();

    printf("Account created! Your account number is %u\n", accounts[i].acc_no);
}

/* Returns the account position if login works, or -1 */
int login()
{
    unsigned int acc_no = 0;
    char pin[10];
    char hash[65];
    int i, tries;

    printf("Account number: ");
    scanf("%u", &acc_no);

    i = find_account(acc_no);
    if (i == -1) {
        printf("Account not found.\n");
        return -1;
    }

    for (tries = 3; tries > 0; tries--) {
        printf("PIN: ");
        scanf("%9s", pin);
        hash_pin(acc_no, pin, hash);

        if (strcmp(hash, accounts[i].pin_hash) == 0) {
            printf("Welcome, %s!\n", accounts[i].holder_name);
            return i;
        }
        printf("Wrong PIN. Tries left: %d\n", tries - 1);
    }

    printf("Too many wrong tries.\n");
    return -1;
}

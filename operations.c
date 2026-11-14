/* operations.c - Member 3 (Nadia): Deposit, withdraw, transfer */
#include "bank.h"

void deposit(int i)
{
    double amount = 0;

    printf("Amount to deposit: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("Amount must be more than 0.\n");
        return;
    }

    accounts[i].balance = accounts[i].balance + amount;
    add_transaction(i, "Deposit", amount, accounts[i].balance);
    save_to_file();
    printf("Done. New balance: %.2f\n", accounts[i].balance);
}

void withdraw(int i)
{
    double amount = 0;

    printf("Amount to withdraw: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("Amount must be more than 0.\n");
        return;
    }
    if (amount > accounts[i].balance) {          /* insufficient-funds check */
        printf("Not enough money. Balance: %.2f\n", accounts[i].balance);
        return;
    }

    accounts[i].balance = accounts[i].balance - amount;
    add_transaction(i, "Withdraw", amount, accounts[i].balance);
    save_to_file();
    printf("Done. New balance: %.2f\n", accounts[i].balance);
}

void transfer_funds(int i)
{
    unsigned int to_acc = 0;
    double amount = 0;
    char type[30];
    int j;

    printf("Transfer to account number: ");
    scanf("%u", &to_acc);

    j = find_account(to_acc);
    if (j == -1) {
        printf("Account not found.\n");
        return;
    }
    if (j == i) {
        printf("Cannot transfer to your own account.\n");
        return;
    }

    printf("Amount to transfer: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("Amount must be more than 0.\n");
        return;
    }
    if (amount > accounts[i].balance) {
        printf("Not enough money. Balance: %.2f\n", accounts[i].balance);
        return;
    }

    accounts[i].balance = accounts[i].balance - amount;
    accounts[j].balance = accounts[j].balance + amount;

    sprintf(type, "Sent-to-%u", accounts[j].acc_no);
    add_transaction(i, type, amount, accounts[i].balance);
    sprintf(type, "Received-from-%u", accounts[i].acc_no);
    add_transaction(j, type, amount, accounts[j].balance);

    save_to_file();
    printf("Transferred %.2f to account %u\n", amount, accounts[j].acc_no);
}

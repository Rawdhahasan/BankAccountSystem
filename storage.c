/* storage.c - Member 5 (Izaz): Saving and loading */
#include "bank.h"

void save_to_file()
{
    FILE *fp;
    struct Transaction *t;
    int i;

    /* accounts.txt: one account per line */
    fp = fopen("accounts.txt", "w");
    if (fp == NULL) {
        printf("Could not save accounts.\n");
        return;
    }
    for (i = 0; i < account_count; i++) {
        fprintf(fp, "%u %s %.2f %s\n", accounts[i].acc_no, accounts[i].holder_name,
                accounts[i].balance, accounts[i].pin_hash);
    }
    fclose(fp);

    /* transactions.txt: one transaction per line */
    fp = fopen("transactions.txt", "w");
    if (fp == NULL) {
        printf("Could not save transactions.\n");
        return;
    }
    for (i = 0; i < account_count; i++) {
        t = logs[i];
        while (t != NULL) {
            fprintf(fp, "%u %s %.2f %.2f\n", accounts[i].acc_no,
                    t->type, t->amount, t->balance_after);
            t = t->next;
        }
    }
    fclose(fp);
}

void load_from_file()
{
    FILE *fp;
    unsigned int acc_no;
    char type[30];
    double amount, balance_after;
    int i;

    /* read the accounts */
    fp = fopen("accounts.txt", "r");
    if (fp != NULL) {
        while (account_count < MAX_ACCOUNTS &&
               fscanf(fp, "%u %49s %lf %64s",
                      &accounts[account_count].acc_no,
                      accounts[account_count].holder_name,
                      &accounts[account_count].balance,
                      accounts[account_count].pin_hash) == 4) {
            logs[account_count] = NULL;
            account_count++;
        }
        fclose(fp);
    }

    /* read the transactions and rebuild each linked list */
    fp = fopen("transactions.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%u %29s %lf %lf", &acc_no, type, &amount, &balance_after) == 4) {
            i = find_account(acc_no);
            if (i != -1)
                add_transaction(i, type, amount, balance_after);
        }
        fclose(fp);
    }
}

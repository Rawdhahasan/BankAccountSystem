/* transaction.c - Member 4 (Hasan): Transaction log (linked list) */
#include "bank.h"

/* Adds a new node at the END of account i's list */
void add_transaction(int i, char type[], double amount, double balance_after)
{
    struct Transaction *node;
    struct Transaction *last;

    node = (struct Transaction *) malloc(sizeof(struct Transaction));
    if (node == NULL) {
        printf("Out of memory.\n");
        return;
    }

    strcpy(node->type, type);
    node->amount = amount;
    node->balance_after = balance_after;
    node->next = NULL;

    if (logs[i] == NULL) {
        logs[i] = node;                  /* list was empty: node is the first */
    } else {
        last = logs[i];
        while (last->next != NULL)       /* walk to the last node */
            last = last->next;
        last->next = node;
    }
}

void print_statement(int i)
{
    struct Transaction *t;
    int number = 1;

    printf("\n================= ACCOUNT STATEMENT =================\n");
    printf("Account: %u\n", accounts[i].acc_no);
    printf("Name:    %s\n", accounts[i].holder_name);
    printf("-----------------------------------------------------\n");
    printf("No  %-22s %12s %12s\n", "Type", "Amount", "Balance");

    t = logs[i];
    while (t != NULL) {
        printf("%-3d %-22s %12.2f %12.2f\n", number, t->type, t->amount, t->balance_after);
        number++;
        t = t->next;
    }

    printf("-----------------------------------------------------\n");
    printf("Current balance: %.2f\n", accounts[i].balance);
}

/* Gives back the memory of every node before the program ends */
void free_logs()
{
    struct Transaction *t;
    struct Transaction *next;
    int i;

    for (i = 0; i < account_count; i++) {
        t = logs[i];
        while (t != NULL) {
            next = t->next;
            free(t);
            t = next;
        }
        logs[i] = NULL;
    }
}

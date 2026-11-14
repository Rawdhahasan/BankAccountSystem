/* bank.h - shared by all 5 files.
   Every .c file starts with  #include "bank.h"  so it can use these. */


/* ---------- Link section ---------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ---------- Definition section ---------- */
#define MAX_ACCOUNTS 150


/* ---------- Structures ---------- */

/* One bank account (exactly as given in the brief) */
struct Account
{
    unsigned int acc_no;
    char holder_name[50];
    double balance;
    char pin_hash[65];
};

/* One transaction (one node of the linked list) */
struct Transaction
{
    char type[30];
    double amount;
    double balance_after;
    struct Transaction *next;
};


/* ---------- Global declaration section ---------- */
/* These are created in main.c.
   "extern" means: this variable is made in another file, use that one. */
extern struct Account accounts[MAX_ACCOUNTS];
extern int account_count;
extern struct Transaction *logs[MAX_ACCOUNTS];


/* ---------- Function prototypes ---------- */

/* main.c        (Member 1 - Alif) */
void account_menu(int i);

/* account.c     (Member 2 - Jumma) */
void hash_pin(unsigned int acc_no, char pin[], char result[]);
int  find_account(unsigned int acc_no);
void open_account();
int  login();

/* operations.c  (Member 3 - Nadia) */
void deposit(int i);
void withdraw(int i);
void transfer_funds(int i);

/* transaction.c (Member 4 - Hasan) */
void add_transaction(int i, char type[], double amount, double balance_after);
void print_statement(int i);
void free_logs();

/* storage.c     (Member 5 - Izaz) */
void save_to_file();
void load_from_file();

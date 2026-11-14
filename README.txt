BANK ACCOUNT MANAGEMENT SYSTEM
CSE114 Project 12 - written in C


WORK DIVISION (5 members, 5 files)
----------------------------------
main.c          Member 1: Alif             Main menu and account menu
account.c       Member 2: Jumma            Open account, PIN login, PIN hashing
operations.c    Member 3: Nadia            Deposit, withdraw, transfer
transaction.c   Member 4: Hasan            Transaction log (linked list), statement
storage.c       Member 5: Izaz             Save and load data

bank.h          Shared by all 5 files (structs and function list)
DESIGN.txt      Design document (transaction log and PIN hashing)


FEATURES
--------
- Open an account (numbers start at 1001, up to 150 accounts)
- Name must be one word, e.g. Alice or Alice_Khan
- Log in with account number and 4-digit PIN (3 tries)
- PIN is saved as a hash, never as the real PIN
- Deposit, withdraw, and transfer money
- No negative balance and no overdraft
- Each account has its own linked list of transactions
- Print an account statement
- Data is saved in accounts.txt and transactions.txt


HOW TO RUN
----------
1. Open a terminal inside the BankAccountSystem folder.
2. Compile:
       gcc main.c account.c operations.c transaction.c storage.c -o bank
3. Run:
       ./bank          (Mac / Linux)
       bank.exe        (Windows)

No GCC? Go to onlinegdb.com, choose C, add all 6 files
(bank.h and the 5 .c files) with the "+" button, and press Run.


HOW TO USE
----------
Main menu:   1. Open new account   2. Login   0. Exit
After login: 1. Deposit  2. Withdraw  3. Transfer  4. Print statement  0. Logout


CONCEPTS USED
-------------
Structures, arrays, functions, header files, linked lists,
malloc/free, and file handling.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bank Management System: This project involves creating a system that manages
// banking transactions, including account creation, deposit, withdrawal, and
// balance inquiry. It can also include features like transaction history,
// account transfer, and password protection.


typedef struct {
  char username[15];
  int accountNum;
  int money;
  char password[15];
} account;

typedef struct {
  account **accounts;
  int totalCapital;
  int numAccounts;
} bank;

void initialize_bank (bank *ptr) {
  ptr->numAccounts = 0;
  ptr->totalCapital = 0;
  ptr->accounts = malloc(sizeof(account*) * 10);
  for (int i=0; i < 10; i++) {
    ptr->accounts[i] = malloc(sizeof(account));
    memset(ptr->accounts[i], 0, sizeof(account));
  }
}

void createAccount(bank *b) {
  int numAccounts = b->numAccounts;

  printf("Bank currently has %d active accounts.\n", numAccounts);

  if (numAccounts == 10) {
    printf("sorry, no more accounts may be created at this time.\n");
    return;
  }
  account *newAccount = malloc(sizeof(account));

  printf("Welcome to account creation. Please enter your desired username. \n");
  scanf_s("%14s", newAccount->username);
  printf("Please enter your desired password. \n");
  scanf_s("%14s", newAccount->password);
  
  newAccount->accountNum = numAccounts+1;
  newAccount->money = 0;

  account *account_ptr = (b->accounts[numAccounts]);
  
  *account_ptr = *newAccount;
  printf("account placed in bank system.\n\n");

  printf("Account creation successful. Your new username is: %s\n Your new password is: %s\n",
         b->accounts[numAccounts]->username, b->accounts[numAccounts]->password);
  printf("Initial balance $0.\n");
  int *accountNumPtr = &(b->numAccounts);
  *accountNumPtr += 1;
  printf("\n");
  return;
}

void balanceCheck(bank *b) {
  char usr[15];
  char pwd[15];
  int numAccts = b->numAccounts;

  if (numAccts == 0) {
    printf("There are no accounts to check.");
    return;
  }

  printf("Please enter your username.\n");
  scanf_s("%14s", &usr);
  printf("%s Entered. Checking...\n\n", usr);
  bool acctFound = false;
  int acctNum;

  for (int i = 0; i < numAccts; i++) {
    account *currentAcct = b->accounts[i];
    char *pUsn = currentAcct->username;
    if (strcmp(pUsn, usr) == 0) {
      acctFound = true;
      acctNum = i;
      break;
    }
  }
  if (acctFound) {
  
    account *thisAcct = b->accounts[acctNum];
    printf("Please enter your password.\n");
    scanf_s("%14s", &pwd);

    if (strcmp(thisAcct->password, pwd) == 0) {
      int balance = b->accounts[acctNum]->money;
      printf("Current Account Balance $%d\n", balance);
      return;
    } else {
      printf("Incorrect password. Access Denied.\n");
      return;
    }
  }
  else
    printf("Account not found.");
  
  printf("\n");
}

void displayMenu() {
  printf("_____MENU_____\n");
  printf("1. CREATE ACCT\n");
  printf("2. BALANCE CHK\n");
  printf("3. WITHDRAWALS\n");
  printf("4. DEPOSITS   \n");
  printf("5. ----QUIT---\n");
}

void deposit(bank *b) {

  printf("Welcomet to deposit. Please enter your username for your account.\n");
  char usr[15];
  scanf_s("%14s", &usr);

  for (int i = 0; i < 10; i++) {
    account *currentAcct = b->accounts[i];
    char *pUsn = currentAcct->username;
    printf("We are checking account %d of 10.\n", i+1);
    if (strcmp(pUsn, usr) == 0) {
      int amount;
      printf("Found account %14s. How much money would you like to deposit today?\n", usr);
      scanf_s("%d", &amount);
      int* curntActMuns = &(currentAcct->money);
      *curntActMuns += amount;
      printf("$%d deposited in account.\n\n", amount);
      return;
    }
  }

  printf("Sorry, we didn't find an account with that username.\n");
  printf("\n");

}

void withdraw(bank *b) {

  char usr[15];
  char pwd[15];
  int numAccts = b->numAccounts;

  if (numAccts == 0) {
    printf("There are no accounts to check.");
    return;
  }

  printf("Please enter your username.\n");
  scanf_s("%14s", &usr);
  printf("%s Entered. Checking...\n\n", usr);
  bool acctFound = false;
  int acctNum;

  for (int i = 0; i < numAccts; i++) {
    account *currentAcct = b->accounts[i];
    char *pUsn = currentAcct->username;
    if (strcmp(pUsn, usr) == 0) {
      acctFound = true;
      acctNum = i;
      break;
    }
  }
  if (acctFound) {
    account *thisAcct = b->accounts[acctNum];
    printf("Please enter your password.\n");
    scanf_s("%14s", &pwd);

    if (strcmp(thisAcct->password, pwd) == 0) {
      int balance = thisAcct->money;
      printf("Current Account Balance $%d\n", balance);
      int withdraw;
      printf("How much would you like to take out today?\n");
      scanf_s("%d", &withdraw);

      while(withdraw > balance) {
        printf("Withdrawl exceeds balance. Please try again.\n");
        scanf_s("%d", &withdraw);
      }

      int* balptr = &thisAcct->money;
      *balptr -= withdraw;
      printf("Remaining account balance: $%d\n", *balptr);
      return;
    } else {
      printf("Incorrect password. Access Denied.\n");
      return;
    }
  }
  else
    printf("Account not found.");
}

void test(bank *b) {

    int acctNum = b->numAccounts;
    printf("Replit bank has %d accounts.", acctNum);
    if (acctNum == 0)
      return;


    for (int i = 0; i < 9; i++) {
        account *currentAcct = b->accounts[i];
        printf("We are checking account %d of 10.\n", i+1);
        printf("Current acct: %s\n", currentAcct->username);
        printf("Current acct pwd: %s\n", currentAcct->password);
        printf("Current acct: %d\n", currentAcct->accountNum);
        printf("Current acct bal: %d\n\n", currentAcct->money);
  }
}



int main(void) {
  bank* b = malloc(sizeof(bank));
  printf("Bank created.\n");
  initialize_bank(b);

  displayMenu();
  int choice;
  int *choiceptr = &choice;
  scanf_s("%d", choiceptr);
  while (choice < 5 && choice > 0) {
    switch (choice) {

    case 1: {
      char *ptr;
      createAccount(b);
      break;
    }
    case 2: {
      balanceCheck(b);
      break;
    }
    case 3: {
      withdraw(b);
      break;
    }
    case 4: {
      deposit(b);
      break;
    }
    case 5: {
      free(b);
      break;
    }
    case 6:{
      test(b);
    }

    default:
      printf("PLEASE MAKE VALID INPUT.\n");
    }
    printf("\n");
    displayMenu();
    scanf_s("%d", choiceptr);
  }
}
#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX 100

typedef struct {
    char username[20];
    char password[20];
    char role[10]; // student/teacher/admin
} Account;

extern Account accounts[MAX];
extern int accountCount;

void loadAccounts();
void saveAccounts();
void registerAccount();
void changePassword();
Account* login();
void exportAccountsToFile();
void importAccountsFromFile();

#endif
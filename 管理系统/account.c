#include <stdio.h>
#include <string.h>
#include "account.h"

Account accounts[MAX];
int accountCount = 0;

void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (!fp) return;
    while (fscanf(fp, "%s %s %s", accounts[accountCount].username,
                  accounts[accountCount].password,
                  accounts[accountCount].role) != EOF) {
        accountCount++;
    }
    fclose(fp);
}

void saveAccounts() {
    FILE* fp = fopen("accounts.txt", "w");
    for (int i = 0; i < accountCount; i++) {
        fprintf(fp, "%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
    }
    fclose(fp);
}

void exportAccountsToFile() {
    FILE* fp = fopen("exported_accounts.txt", "w");
    for (int i = 0; i < accountCount; i++) {
        fprintf(fp, "%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
    }
    fclose(fp);
    printf("账号信息已导出到 exported_accounts.txt\n");
}

void importAccountsFromFile() {
    FILE* fp = fopen("import_accounts.txt", "r");
    if (!fp) {
        printf("未找到导入文件。\n");
        return;
    }
    while (fscanf(fp, "%s %s %s", accounts[accountCount].username, accounts[accountCount].password, accounts[accountCount].role) != EOF) {
        accountCount++;
    }
    fclose(fp);
    saveAccounts();
    printf("账号信息已从 import_accounts.txt 导入。\n");
}

void registerAccount() {
    Account acc;
    printf("请输入用户名: ");
    scanf("%s", acc.username);
    printf("请输入密码: ");
    scanf("%s", acc.password);
    printf("请输入角色 (student/teacher/admin): ");
    scanf("%s", acc.role);

    accounts[accountCount++] = acc;
    saveAccounts();
    printf("注册成功！\n");
}

void changePassword() {
    char username[20], oldpass[20], newpass[20];
    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入旧密码: ");
    scanf("%s", oldpass);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, oldpass) == 0) {
            printf("请输入新密码: ");
            scanf("%s", newpass);
            strcpy(accounts[i].password, newpass);
            saveAccounts();
            printf("密码修改成功！\n");
            return;
        }
    }
    printf("用户名或密码错误！\n");
}

Account* login() {
    char username[20], password[20];
    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("以 %s 身份登录成功！\n", accounts[i].role);
            return &accounts[i];
        }
    }
    printf("登录失败！\n");
    return NULL;
}
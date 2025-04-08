#include <stdio.h>
#include <string.h>
#include "account.h"
#include "student.h"
#include "file.h"

int main() {
    loadAccounts();
    loadStudentsFromFile();
    int choice;
    while (1) {
        printf("1. 注册账号\n2. 修改密码\n3. 登录\n0. 退出\n请选择操作: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        else if (choice == 1) registerAccount();
        else if (choice == 2) changePassword();
        else if (choice == 3) {
            Account* acc = login();
            if (acc) {
                if (strcmp(acc->role, "student") == 0) {
                    int sc;
                    printf("1. 查询自己的成绩\n2. 查看班级成绩\n请选择: ");
                    scanf("%d", &sc);
                    if (sc == 1) queryOwnScore(acc->username);
                    else queryClassScores();
                } else if (strcmp(acc->role, "teacher") == 0) {
                    int tc;
                    printf("1. 添加学生\n2. 分页查看学生\n3. 修改学生信息\n4. 删除学生信息\n5. 成绩分析\n请选择: ");
                    scanf("%d", &tc);
                    if (tc == 1) addStudent();
                    else if (tc == 2) listStudents(5);
                    else if (tc == 3) modifyStudent();
                    else if (tc == 4) deleteStudent();
                    else if (tc == 5) analyzeScores();
                } else if (strcmp(acc->role, "admin") == 0) {
                    int ad;
                    printf("1. 注册新账号\n2. 修改密码\n3. 查看所有账号\n4. 导出账号信息\n5. 导入账号信息\n请选择: ");
                    scanf("%d", &ad);
                    if (ad == 1) registerAccount();
                    else if (ad == 2) changePassword();
                    else if (ad == 3) {
                        for (int i = 0; i < accountCount; i++)
                            printf("%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
                    } else if (ad == 4) exportAccountsToFile();
                    else if (ad == 5) importAccountsFromFile();
                }
            }
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char username[20];
    char password[20];
    char role[10]; // 学生、教师、管理员
} Account;

typedef struct Student {
    char id[10];
    char name[20];
    int score;
    struct Student* prev;
    struct Student* next;
} Student;

Account accounts[MAX];
int accountCount = 0;

Student* head = NULL;
Student* tail = NULL;

void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (!fp) return;
    while (fscanf(fp, "%s %s %s", accounts[accountCount].username, accounts[accountCount].password, accounts[accountCount].role) != EOF) {
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

void saveStudentsToFile() {
    FILE* fp = fopen("students.txt", "w");
    Student* cur = head;
    while (cur) {
        fprintf(fp, "%s %s %d\n", cur->id, cur->name, cur->score);
        cur = cur->next;
    }
    fclose(fp);
    printf("学生数据已保存。\n");
}

void loadStudentsFromFile() {
    FILE* fp = fopen("students.txt", "r");
    if (!fp) return;
    Student* s;
    while (!feof(fp)) {
        s = (Student*)malloc(sizeof(Student));
        if (fscanf(fp, "%s %s %d", s->id, s->name, &s->score) != 3) break;
        s->next = NULL;
        s->prev = tail;
        if (tail) tail->next = s;
        else head = s;
        tail = s;
    }
    fclose(fp);
    printf("学生数据已加载。\n");
}

void addStudent() {
    Student* s = (Student*)malloc(sizeof(Student));
    printf("请输入学生学号: ");
    scanf("%s", s->id);
    printf("请输入学生姓名: ");
    scanf("%s", s->name);
    printf("请输入学生成绩: ");
    scanf("%d", &s->score);

    s->next = NULL;
    s->prev = tail;
    if (tail) tail->next = s;
    else head = s;
    tail = s;
    printf("学生添加成功。\n");
    saveStudentsToFile();
}

void modifyStudent() {
    char id[10];
    printf("请输入要修改的学生学号: ");
    scanf("%s", id);
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->id, id) == 0) {
            printf("请输入新姓名: ");
            scanf("%s", cur->name);
            printf("请输入新成绩: ");
            scanf("%d", &cur->score);
            saveStudentsToFile();
            printf("学生信息已更新。\n");
            return;
        }
        cur = cur->next;
    }
    printf("未找到该学生。\n");
}

void deleteStudent() {
    char id[10];
    printf("请输入要删除的学生学号: ");
    scanf("%s", id);
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->id, id) == 0) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;
            free(cur);
            saveStudentsToFile();
            printf("学生信息已删除。\n");
            return;
        }
        cur = cur->next;
    }
    printf("未找到该学生。\n");
}

void analyzeScores() {
    Student* cur = head;
    printf("成绩分布图：\n");
    while (cur) {
        printf("%s (%s): %d | ", cur->id, cur->name, cur->score);
        for (int i = 0; i < cur->score / 5; i++) printf("=");
        printf("\n");
        cur = cur->next;
    }
}

void listStudents(int pageSize) {
    Student* cur = head;
    int count = 0;
    while (cur) {
        printf("%s %s %d\n", cur->id, cur->name, cur->score);
        count++;
        if (count % pageSize == 0) {
            char ch;
            printf("按 n 查看下一页，q 退出: ");
            scanf(" %c", &ch);
            if (ch == 'q') break;
        }
        cur = cur->next;
    }
}

void queryOwnScore(char* username) {
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->id, username) == 0) {
            printf("你的成绩是: %d\n", cur->score);
            return;
        }
        cur = cur->next;
    }
    printf("未找到你的成绩。\n");
}

void queryClassScores() {
    Student* cur = head;
    while (cur) {
        printf("%s %s %d\n", cur->id, cur->name, cur->score);
        cur = cur->next;
    }
}

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

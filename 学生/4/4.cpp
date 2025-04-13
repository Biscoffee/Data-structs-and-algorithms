#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 20
#define MAX_LINE_LEN 100
#define MAX_ACCOUNTS 100
#define PAGE_SIZE 5
#define MIN_SCORE 0
#define MAX_SCORE 100

typedef struct Account {
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
    char role[MAX_STR_LEN]; // student / teacher / admin
} Account;

typedef struct Student {
    char username[MAX_STR_LEN]; // 以用户名为主键
    char name[MAX_STR_LEN];
    int score;
    struct Student* prev;
    struct Student* next;
} Student;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

Student* head = NULL;
Student* tail = NULL;

// 工具函数
void clearBuffer() {
    while (getchar() != '\n');
}

void safeInput(char* str, int len, const char* prompt) {
    printf("%s", prompt);
    fgets(str, len, stdin);
    str[strcspn(str, "\n")] = '\0';
}

int safeInputInt(const char* prompt, int min, int max) {
    int val;
    char line[MAX_LINE_LEN];
    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) && sscanf(line, "%d", &val) == 1 && val >= min && val <= max)
            return val;
        printf("无效输入，请输入 %d 到 %d 之间的整数。\n", min, max);
    }
}

// 账户系统
void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (!fp) return;
    while (fscanf(fp, "%s %s %s", accounts[accountCount].username, accounts[accountCount].password, accounts[accountCount].role) == 3)
        accountCount++;
    fclose(fp);
}

void saveAccounts() {
    FILE* fp = fopen("accounts.txt", "w");
    for (int i = 0; i < accountCount; i++)
        fprintf(fp, "%s %s %s\n", accounts[i].username, accounts[i].password, accounts[i].role);
    fclose(fp);
}

int registerAccount() {
    Account acc;
    safeInput(acc.username, MAX_STR_LEN, "用户名: ");
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, acc.username) == 0) {
            printf("用户名已存在。\n");
            return -1;
        }
    }
    safeInput(acc.password, MAX_STR_LEN, "密码: ");
    safeInput(acc.role, MAX_STR_LEN, "角色（student/teacher/admin）: ");
    accounts[accountCount++] = acc;
    saveAccounts();
    printf("注册成功。\n");
    return 0;
}

Account* login() {
    char username[MAX_STR_LEN], password[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "用户名: ");
    safeInput(password, MAX_STR_LEN, "密码: ");
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0)
            return &accounts[i];
    }
    printf("登录失败，用户名或密码错误。\n");
    return NULL;
}

// 学生管理
Student* findStudentById(const char* username) {
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void saveStudentsToFile() {
    FILE* fp = fopen("students.txt", "w");
    if (!fp) {
        printf("无法保存学生数据！\n");
        return;
    }
    Student* cur = head;
    while (cur) {
        fprintf(fp, "%s %s %d\n", cur->username, cur->name, cur->score);
        cur = cur->next;
    }
    fclose(fp);
}

void loadStudentsFromFile() {
    FILE* fp = fopen("students.txt", "r");
    if (!fp) return;
    while (!feof(fp)) {
        Student* s = (Student*)malloc(sizeof(Student));
        if (fscanf(fp, "%s %s %d", s->username, s->name, &s->score) != 3) {
            free(s);
            break;
        }
        if (findStudentById(s->username)) {
            free(s);
            continue;
        }
        s->next = NULL;
        s->prev = tail;
        if (tail) tail->next = s; else head = s;
        tail = s;
    }
    fclose(fp);
}

void addStudent() {
    char username[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "请输入学生用户名（已注册的学生账号）: ");
    int found = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].role, "student") == 0) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("未找到该用户名对应的学生账号，请先注册！\n");
        return;
    }
    if (findStudentById(username)) {
        printf("该学生已有成绩记录！\n");
        return;
    }

    Student* s = (Student*)malloc(sizeof(Student));
    strcpy(s->username, username);
    safeInput(s->name, MAX_STR_LEN, "学生姓名: ");
    s->score = safeInputInt("成绩: ", MIN_SCORE, MAX_SCORE);

    s->next = NULL;
    s->prev = tail;
    if (tail) tail->next = s; else head = s;
    tail = s;

    saveStudentsToFile();
    printf("成绩添加成功！\n");
}

void displayStudents(int page) {
    int count = 0;
    Student* cur = head;
    while (cur) {
        count++;
        cur = cur->next;
    }
    if (count == 0) {
        printf("暂无学生信息。\n");
        return;
    }
    int totalPages = (count + PAGE_SIZE - 1) / PAGE_SIZE;
    if (page < 1 || page > totalPages) {
        printf("页码超出范围，共 %d 页。\n", totalPages);
        return;
    }
    printf("\n-- 第 %d/%d 页 --\n", page, totalPages);
    int start = (page - 1) * PAGE_SIZE, end = start + PAGE_SIZE;
    int i = 0;
    cur = head;
    while (cur && i < end) {
        if (i >= start)
            printf("用户名: %s, 姓名: %s, 成绩: %d\n", cur->username, cur->name, cur->score);
        cur = cur->next;
        i++;
    }
}

void modifyStudent() {
    char username[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "要修改的学生用户名: ");
    Student* target = findStudentById(username);
    if (!target) {
        printf("未找到该学生！\n");
        return;
    }
    safeInput(target->name, MAX_STR_LEN, "新姓名: ");
    target->score = safeInputInt("新成绩: ", MIN_SCORE, MAX_SCORE);
    saveStudentsToFile();
    printf("信息已更新！\n");
}

void deleteStudent() {
    char username[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "要删除的学生用户名: ");
    Student* target = findStudentById(username);
    if (!target) {
        printf("未找到该学生！\n");
        return;
    }
    if (target->prev) target->prev->next = target->next;
    else head = target->next;
    if (target->next) target->next->prev = target->prev;
    else tail = target->prev;
    free(target);
    saveStudentsToFile();
    printf("学生删除成功！\n");
}

// 主程序
void menu(Account* user) {
    int choice, page = 1;
    if (strcmp(user->role, "teacher") == 0 || strcmp(user->role, "admin") == 0) {
        do {
            printf("\n【1】添加学生成绩\n【2】查看学生信息\n【3】修改学生信息\n【4】删除学生\n【5】下一页\n【6】上一页\n【0】退出\n");
            choice = safeInputInt("请选择操作: ", 0, 6);
            switch (choice) {
                case 1: addStudent(); break;
                case 2: displayStudents(page); break;
                case 3: modifyStudent(); break;
                case 4: deleteStudent(); break;
                case 5: page++; displayStudents(page); break;
                case 6: if (page > 1) page--; displayStudents(page); break;
            }
        } while (choice != 0);
    } else if (strcmp(user->role, "student") == 0) {
        Student* s = findStudentById(user->username);
        if (s) printf("你的成绩: %d\n", s->score);
        else printf("尚未录入成绩。\n");
    }
}

int main() {
    loadAccounts();
    loadStudentsFromFile();
    int opt;
    do {
        printf("\n【1】注册\n【2】登录\n【0】退出\n");
        opt = safeInputInt("请选择操作: ", 0, 2);
        if (opt == 1) registerAccount();
        else if (opt == 2) {
            Account* user = login();
            if (user) menu(user);
        }
    } while (opt != 0);
    return 0;
}
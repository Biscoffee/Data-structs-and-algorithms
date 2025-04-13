#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACCOUNTS 100
#define MAX_STR_LEN 20
#define MIN_SCORE 0
#define MAX_SCORE 100
typedef struct {
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
    char role[MAX_STR_LEN]; 
} Account;
typedef struct Student {
    char id[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    int score;
    struct Student* prev;
    struct Student* next;
} Student;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

Student* head = NULL;
Student* tail = NULL;

/* 安全输入函数 */
void safeInput(char* buffer, int maxLen, const char* prompt) {
    printf("%s", prompt);
    if (fgets(buffer, maxLen, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0'; // 去除换行符
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // 清空输入缓冲区
}

int safeInputInt(const char* prompt, int min, int max) {
    char input[20];
    int value;
    while (1) {
        safeInput(input, sizeof(input), prompt);
        if (sscanf(input, "%d", &value) == 1 && value >= min && value <= max) return value;
        printf("输入无效，请输入 %d~%d 之间的整数\n", min, max);
    }
}

void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (!fp) {
        printf("账号文件不存在，将创建新文件\n");
        return;
    }
    while (accountCount < MAX_ACCOUNTS && 
           fscanf(fp, "%19s %19s %19s", 
                  accounts[accountCount].username,
                  accounts[accountCount].password,
                  accounts[accountCount].role) == 3) {
        accountCount++;
    }
    fclose(fp);
}

void saveAccounts() {
    FILE* fp = fopen("accounts.txt", "w");
    if (!fp) {
        printf("无法保存账号信息！\n");
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        fprintf(fp, "%s %s %s\n", 
                accounts[i].username, 
                accounts[i].password, 
                accounts[i].role);
    }
    fclose(fp);
}

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("系统用户已达上限！\n");
        return;
    }

    Account acc;
    while (1) {
        safeInput(acc.username, MAX_STR_LEN, "请输入学号(用户名): ");
        int exists = 0;
        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].username, acc.username) == 0) {
                exists = 1;
                break;
            }
        }
        if (!exists) break;
        printf("用户名已存在！\n");
    }

    safeInput(acc.password, MAX_STR_LEN, "请输入密码: ");
    while (1) {
        safeInput(acc.role, MAX_STR_LEN, "请输入角色 (student/teacher/admin): ");
        if (strcmp(acc.role, "student") == 0 || strcmp(acc.role, "teacher") == 0 || strcmp(acc.role, "admin") == 0)
            break;
        printf("角色无效！\n");
    }

    accounts[accountCount++] = acc;
    saveAccounts();
    printf("注册成功！\n");
}

void changePassword() {
    char username[MAX_STR_LEN], oldpass[MAX_STR_LEN], newpass[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "请输入用户名: ");
    safeInput(oldpass, MAX_STR_LEN, "请输入旧密码: ");

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, oldpass) == 0) {
            safeInput(newpass, MAX_STR_LEN, "请输入新密码: ");
            strcpy(accounts[i].password, newpass);
            saveAccounts();
            printf("密码修改成功！\n");
            return;
        }
    }
    printf("用户名或密码错误！\n");
}

Account* login() {
    char username[MAX_STR_LEN], password[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "用户名: ");
    safeInput(password, MAX_STR_LEN, "密码: ");
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("欢迎 %s！\n", accounts[i].role);
            return &accounts[i];
        }
    }
    printf("登录失败！\n");
    return NULL;
}

Student* findStudentById(const char* id) {
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->id, id) == 0) return cur;
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
        fprintf(fp, "%s %s %d\n", cur->id, cur->name, cur->score);
        cur = cur->next;
    }
    fclose(fp);
}

void loadStudentsFromFile() {
    FILE* fp = fopen("students.txt", "r");
    if (!fp) {
        printf("学生数据文件不存在，将创建新文件\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        Student* s = (Student*)malloc(sizeof(Student));
        if (sscanf(line, "%19s %19s %d", s->id, s->name, &s->score) != 3) {
            free(s);
            continue;
        }
        if (findStudentById(s->id)) {
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
    char id[MAX_STR_LEN];
    safeInput(id, MAX_STR_LEN, "请输入学生学号（已注册的学生账号）: ");
    int found = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, id) == 0 && strcmp(accounts[i].role, "student") == 0) {
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("未找到该学号对应的学生账号，请先注册！\n");
        return;
    }
    if (findStudentById(id)) {
        printf("该学生已有成绩记录！\n");
        return;
    }

    Student* s = (Student*)malloc(sizeof(Student));
    strcpy(s->id, id);
    safeInput(s->name, MAX_STR_LEN, "学生姓名: ");
    s->score = safeInputInt("成绩: ", MIN_SCORE, MAX_SCORE);

    s->next = NULL;
    s->prev = tail;
    if (tail) tail->next = s; else head = s;
    tail = s;

    saveStudentsToFile();
    printf("成绩添加成功！\n");
}

void modifyStudent() {
    char id[MAX_STR_LEN];
    safeInput(id, MAX_STR_LEN, "要修改的学生学号: ");
    
    Student* target = findStudentById(id);
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
    if (!head) {
        printf("学生列表为空！\n");
        return;
    }
    
    char id[MAX_STR_LEN];
    safeInput(id, MAX_STR_LEN, "要删除的学号: ");
    
    Student* target = findStudentById(id);
    if (!target) {
        printf("未找到该学生！\n");
        return;
    }
    
    // 调整链表指针
    if (target->prev) target->prev->next = target->next;
    else head = target->next;
    
    if (target->next) target->next->prev = target->prev;
    else tail = target->prev;
    
    free(target);
    saveStudentsToFile();
    printf("学生删除成功！\n");
}

void analyzeScores() {
    if (!head) {
        printf("没有学生记录！\n");
        return;
    }
    
    int total = 0, count = 0;
    Student* cur = head;
    while (cur) {
        total += cur->score;
        count++;
        printf("%-8s | %-20s | %3d | ", cur->id, cur->name, cur->score);
        for (int i = 0; i < cur->score/5; i++) printf("█");
        printf("\n");
        cur = cur->next;
    }
    printf("\n平均成绩: %.1f\n", (float)total/count);
}

void listStudents(int pageSize) {
    if (!head) {
        printf("没有学生记录！\n");
        return;
    }
    
    Student* cur = head;
    int count = 0, page = 1;
    while (cur) {
        printf("%-8s | %-20s | %3d\n", cur->id, cur->name, cur->score);
        count++;
        
        if (count % pageSize == 0) {
            printf("--- 第 %d 页 (共 %d 条) ---\n", page++, count);
            printf("[n]下一页  [q]返回: ");
            char cmd;
            scanf(" %c", &cmd);
            while (getchar() != '\n'); // 清空缓冲区
            if (tolower(cmd) == 'q') break;
        }
        cur = cur->next;
    }
    printf("---------- 列表结束 ----------\n");
}

/* 菜单系统 */
void studentMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 学生菜单 ===\n");
        printf("1. 查询成绩\n");
        printf("2. 查看全班成绩\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 2);
        
        switch(choice) {
            case 1: {
                Student* s = findStudentById(acc->username);
                s ? printf("你的成绩: %d\n", s->score) : 
                    printf("未找到你的成绩记录！\n");
                break;
            }
            case 2: 
                listStudents(10);
                break;
        }
    } while (choice != 0);
}

void teacherMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 教师菜单 ===\n");
        printf("1. 添加学生\n");
        printf("2. 分页查看\n");
        printf("3. 修改信息\n");
        printf("4. 删除学生\n");
        printf("5. 成绩分析\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 5);
        
        switch(choice) {
            case 1: addStudent(); break;
            case 2: listStudents(5); break;
            case 3: modifyStudent(); break;
            case 4: deleteStudent(); break;
            case 5: analyzeScores(); break;
        }
    } while (choice != 0);
}

void adminMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 管理员菜单 ===\n");
        printf("1. 注册账号\n");
        printf("2. 修改密码\n");
        printf("3. 查看所有账号\n");
        printf("4. 导出账号\n");
        printf("5. 导入账号\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 5);
        
        switch(choice) {
            case 1: registerAccount(); break;
            case 2: changePassword(); break;
            case 3: 
                for (int i = 0; i < accountCount; i++) 
                    printf("%-15s [%s]\n", accounts[i].username, accounts[i].role);
                break;
            case 4: 
                saveAccounts();
                printf("账号数据已保存到 accounts.txt\n");
                break;
            case 5: 
                loadAccounts();
                printf("账号数据已重新加载\n");
                break;
        }
    } while (choice != 0);
}

int main() {
    loadAccounts();
    loadStudentsFromFile();
    
    int choice;
    do {
        printf("\n=== 主菜单 ===\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("3. 修改密码\n");
        printf("0. 退出\n");
        choice = safeInputInt("请选择: ", 0, 3);
        
        switch(choice) {
            case 1: 
                registerAccount(); 
                break;
            case 2: {
                Account* acc = login();
                if (acc) {
                    if (strcmp(acc->role, "student") == 0) studentMenu(acc);
                    else if (strcmp(acc->role, "teacher") == 0) teacherMenu(acc);
                    else if (strcmp(acc->role, "admin") == 0) adminMenu(acc);
                }
                break;
            }
            case 3: 
                changePassword(); 
                break;
        }
    } while (choice != 0);
    
    printf("系统已安全退出\n");
    return 0;
}
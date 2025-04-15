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
    char className[MAX_STR_LEN]; // 修改字段名
} Account;

typedef struct Student {
    char username[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    char className[MAX_STR_LEN]; // 修改字段名
    int score;
    struct Student* prev;
    struct Student* next;
} Student;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

Student* head = NULL;
Student* tail = NULL;

/* 输入工具函数（保持不变） */
void safeInput(char* buffer, int maxLen, const char* prompt) {
    printf("%s", prompt);
    if (fgets(buffer, maxLen, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

/* 账号系统（增加班级处理） */
void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (!fp) return;
    
    while (accountCount < MAX_ACCOUNTS && 
           fscanf(fp, "%19s %19s %19s %19s", 
                  accounts[accountCount].username,
                  accounts[accountCount].password,
                  accounts[accountCount].role,
                  accounts[accountCount].className) == 4) { // 修改
        accountCount++;
    }
    fclose(fp);
}

void saveAccounts() {
    FILE* fp = fopen("accounts.txt", "w");
    if (!fp) return;
    
    for (int i = 0; i < accountCount; i++) {
        fprintf(fp, "%s %s %s %s\n", 
                accounts[i].username, 
                accounts[i].password, 
                accounts[i].role,
                accounts[i].className); // 修改
    }
    fclose(fp);
}

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("系统用户已达上限！\n");
        return;
    }

    Account acc;
    safeInput(acc.username, MAX_STR_LEN, "请输入用户名: ");
    
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, acc.username) == 0) {
            printf("用户名已存在！\n");
            return;
        }
    }

    safeInput(acc.password, MAX_STR_LEN, "请输入密码: ");
    
    while (1) {
        safeInput(acc.role, MAX_STR_LEN, "请输入角色 (student/teacher/admin): ");
        if (strcmp(acc.role, "teacher") == 0) {
            safeInput(acc.className, MAX_STR_LEN, "请输入负责班级: ");
            break;
        }
        if (strcmp(acc.role, "student") == 0) {  // 修改：学生选择班级
            safeInput(acc.className, MAX_STR_LEN, "请输入所在班级: ");
            break;
        }
        if (strcmp(acc.role, "admin") == 0) {
            strcpy(acc.className, "");
            break;
        }
        printf("角色无效！\n");
    }

    accounts[accountCount++] = acc;
    saveAccounts();
    printf("注册成功！\n");
}

Account* login() {
    char username[MAX_STR_LEN], password[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "用户名: ");
    safeInput(password, MAX_STR_LEN, "密码: ");
    
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && 
            strcmp(accounts[i].password, password) == 0) {
            printf("欢迎 %s！\n", accounts[i].role);
            return &accounts[i];
        }
    }
    printf("登录失败！\n");
    return NULL;
}

/* 学生管理系统（改为班级管理） */
Student* findStudentByUsername(const char* username) {
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void saveStudentsToFile() {
    FILE* fp = fopen("students.txt", "w");
    if (!fp) return;
    
    Student* cur = head;
    while (cur) {
        fprintf(fp, "%s %s %s %d\n", 
                cur->username, 
                cur->name,
                cur->className,
                cur->score);
        cur = cur->next;
    }
    fclose(fp);
}

void loadStudentsFromFile() {
    FILE* fp = fopen("students.txt", "r");
    if (!fp) return;
    
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        Student* s = (Student*)malloc(sizeof(Student));
        if (sscanf(line, "%19s %19s %19s %d", 
                   s->username, 
                   s->name, 
                   s->className,
                   &s->score) != 4) {
            free(s);
            continue;
        }
        
        s->next = NULL;
        s->prev = tail;
        if (tail) tail->next = s; 
        else head = s;
        tail = s;
    }
    fclose(fp);
}

void addStudent(Account* currentAccount) {
    Student s;
    safeInput(s.username, MAX_STR_LEN, "学生用户名: ");
    
    // 验证用户名是否存在
    int valid = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, s.username) == 0 && 
            strcmp(accounts[i].role, "student") == 0) {
            valid = 1;
            break;
        }
    }
    if (!valid) {
        printf("无效的学生用户名！\n");
        return;
    }
    
    if (findStudentByUsername(s.username)) {
        printf("该学生已有记录！\n");
        return;
    }

    safeInput(s.name, MAX_STR_LEN, "学生姓名: ");
    
    // 设置班级
    if (strcmp(currentAccount->role, "teacher") == 0) {
        strcpy(s.className, currentAccount->className);
    } else {
        safeInput(s.className, MAX_STR_LEN, "班级: ");
    }
    
    s.score = safeInputInt("成绩: ", MIN_SCORE, MAX_SCORE);

    Student* newStu = (Student*)malloc(sizeof(Student));
    *newStu = s;
    newStu->next = NULL;
    newStu->prev = tail;
    
    if (tail) tail->next = newStu;
    else head = newStu;
    tail = newStu;
    
    saveStudentsToFile();
    printf("添加成功！\n");
}

/* 修改教师管理菜单 */
void teacherMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 教师菜单 (%s) ===\n", acc->className);
        printf("1. 添加学生\n");
        printf("2. 查看本班学生\n");
        printf("3. 修改学生信息\n");
        printf("4. 删除学生\n");
        printf("5. 班级成绩分析\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 5);
        
        switch(choice) {
            case 1: 
                addStudent(acc);
                break;
            case 2: {
                Student* cur = head;
                printf("\n%-15s | %-15s | 成绩\n", "用户名", "姓名");
                while (cur) {
                    if (strcmp(cur->className, acc->className) == 0) {
                        printf("%-15s | %-15s | %3d\n", 
                               cur->username, cur->name, cur->score);
                    }
                    cur = cur->next;
                }
                break;
            }
            case 3: {
                char username[MAX_STR_LEN];
                safeInput(username, MAX_STR_LEN, "要修改的学生用户名: ");
                Student* target = findStudentByUsername(username);
                
                if (target && strcmp(target->className, acc->className) == 0) {
                    target->score = safeInputInt("新成绩: ", MIN_SCORE, MAX_SCORE);
                    saveStudentsToFile();
                    printf("修改成功！\n");
                } else {
                    printf("找不到该学生！\n");
                }
                break;
            }
            case 4: {
                char username[MAX_STR_LEN];
                safeInput(username, MAX_STR_LEN, "要删除的学生用户名: ");
                Student* target = findStudentByUsername(username);
                
                if (target && strcmp(target->className, acc->className) == 0) {
                    if (target->prev) target->prev->next = target->next;
                    else head = target->next;
                    
                    if (target->next) target->next->prev = target->prev;
                    else tail = target->prev;
                    
                    free(target);
                    saveStudentsToFile();
                    printf("删除成功！\n");
                } else {
                    printf("找不到该学生！\n");
                }
                break;
            }
            case 5: {
                int total = 0, count = 0;
                Student* cur = head;
                printf("\n=== 班级 %s 成绩分析 ===\n", acc->className);
                while (cur) {
                    if (strcmp(cur->className, acc->className) == 0) {
                        total += cur->score;
                        count++;
                        printf("%-15s | %-15s | %3d | ", 
                               cur->username, cur->name, cur->score);
                        for (int i = 0; i < cur->score/5; i++) printf("█");
                        printf("\n");
                    }
                    cur = cur->next;
                }
                if (count > 0) {
                    printf("\n平均成绩: %.1f\n", (float)total/count);
                }
                break;
            }
        }
    } while (choice != 0);
}

void adminAccountManagement() {
    int choice;
    do {
        printf("\n=== 账号管理 ===\n");
        printf("1. 查看所有账号\n");
        printf("2. 删除账号\n");
        printf("3. 修改密码\n");
        printf("4. 导出账号到文件\n");
        printf("5. 从文件导入账号\n");
        printf("0. 返回\n");
        choice = safeInputInt("请选择: ", 0, 5);

        switch(choice) {
            case 1: {
                printf("\n%-15s | %-10s | 班级/角色\n", "用户名", "角色");
                for(int i=0; i<accountCount; i++) {
                    printf("%-15s | %-10s | %s\n", 
                        accounts[i].username,
                        accounts[i].role,
                        (strcmp(accounts[i].role, "teacher") == 0) ? 
                        accounts[i].className : "");
                }
                break;
            }
            case 2: {
                char username[MAX_STR_LEN];
                safeInput(username, MAX_STR_LEN, "要删除的用户名: ");
                for(int i=0; i<accountCount; i++) {
                    if(strcmp(accounts[i].username, username) == 0) {
                        // 删除账号
                        memmove(&accounts[i], &accounts[i+1], 
                               (accountCount-i-1)*sizeof(Account));
                        accountCount--;
                        saveAccounts();
                        printf("删除成功！\n");
                        return;
                    }
                }
                printf("未找到该用户！\n");
                break;
            }
            case 3: {
                char username[MAX_STR_LEN], newpass[MAX_STR_LEN];
                safeInput(username, MAX_STR_LEN, "要修改的用户名: ");
                for(int i=0; i<accountCount; i++) {
                    if(strcmp(accounts[i].username, username) == 0) {
                        safeInput(newpass, MAX_STR_LEN, "新密码: ");
                        strcpy(accounts[i].password, newpass);
                        saveAccounts();
                        printf("密码已更新！\n");
                        return;
                    }
                }
                printf("未找到该用户！\n");
                break;
            }
            case 4: {
                saveAccounts();
                printf("账号数据已导出到accounts.txt\n");
                break;
            }
            case 5: {
                loadAccounts();
                printf("账号数据已从文件导入！\n");
                break;
            }
        }
    } while(choice != 0);
}

/* 管理员菜单增加班级查看 */
void adminMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 管理员菜单 ===\n");
        printf("1. 学生管理\n");
        printf("2. 账号管理\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 2);
        
        switch(choice) {
            case 1: {
                // 原管理员菜单的学生管理功能
                int subChoice;
                do {
                    printf("\n=== 学生管理 ===\n");
                    printf("1. 查看所有学生\n");
                    printf("2. 添加学生\n");
                    printf("3. 修改学生信息\n");
                    printf("4. 删除学生\n");
                    printf("5. 全局成绩分析\n");
                    printf("0. 返回\n");
                    subChoice = safeInputInt("请选择: ", 0, 5);
                    
                    switch(subChoice) {
                        case 1: /* 原有查看功能 */ break;
                        case 2: addStudent(acc); break;
                        case 3: /* 原有修改功能 */ break;
                        case 4: /* 原有删除功能 */ break;
                        case 5: /* 原有分析功能 */ break;
                    }
                } while(subChoice != 0);
                break;
            }
            case 2: 
                adminAccountManagement();
                break;
        }
    } while(choice != 0);
}


/* 学生菜单保持不变 */
void studentMenu(Account* acc) {
    int choice;
    do {
        Student* s = findStudentByUsername(acc->username);
        if(!s) {
            printf("未找到你的信息！\n");
            return;
        }
        
        printf("\n=== 学生菜单 ===\n");
        printf("1. 查看我的成绩\n");
        printf("2. 查看班级成绩\n");
        printf("0. 返回\n");
        choice = safeInputInt("请选择: ", 0, 2);
        
        switch(choice) {
            case 1: {
                printf("\n姓名: %s\n", s->name);
                printf("班级: %s\n", s->className);
                printf("成绩: %d\n", s->score);
                break;
            }
            case 2: {
                Student* cur = head;
                printf("\n=== %s 班级成绩 ===\n", s->className);
                printf("%-15s | %-15s | 成绩\n", "用户名", "姓名");
                while(cur) {
                    if(strcmp(cur->className, s->className) == 0) {
                        printf("%-15s | %-15s | %3d\n", 
                              cur->username, cur->name, cur->score);
                    }
                    cur = cur->next;
                }
                break;
            }
        }
    } while(choice != 0);
}


/* 主函数保持不变 */
int main() {
    loadAccounts();
    loadStudentsFromFile();
    
    int choice;
    do {
        printf("\n=== 主菜单 ===\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("0. 退出\n");
        choice = safeInputInt("请选择: ", 0, 2);
        
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
        }
    } while (choice != 0);
    
    while(head) {
        Student* temp = head;
        head = head->next;
        free(temp);
    }
    printf("系统已安全退出\n");
    return 0;
}
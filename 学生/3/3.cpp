#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <termios.h>  // 终端控制头文件
#include <unistd.h>   // 包含 STDIN_FILENO 的定义


#define MAX_ACCOUNTS 100
#define MAX_STR_LEN 20
#define MIN_SCORE 0
#define MAX_SCORE 100
#define _POSIX_C_SOURCE 200809L


typedef struct {
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
    char role[MAX_STR_LEN];
    char className[MAX_STR_LEN];
    char email[MAX_STR_LEN]; 
} Account;

typedef struct Student {
    char username[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    char className[MAX_STR_LEN];
    int score;
    struct Student* prev;
    struct Student* next;
} Student;


Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

Student* head = NULL;
Student* tail = NULL;

void safeInputPassword(char* buffer, int maxLen, const char* prompt) {
    struct termios oldt, newt;
    printf("%s", prompt);
    fflush(stdout);

    // 获取当前终端设置
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 修改终端设置：禁用回显和行缓冲
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch;
    int pos = 0;
    while ((ch = getchar()) != '\n' && pos < maxLen-1) {
        if (ch == 127 || ch == 8) { // 处理退格键（macOS/Linux/Windows）
            if (pos > 0) {
                pos--;
                printf("\b \b");
            }
        } else if (isprint(ch)) {
            buffer[pos++] = ch;
            printf("*");
        }
    }
    buffer[pos] = '\0';
    printf("\n");

    // 恢复原始终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

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
                accounts[i].className); 
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
    
    // 检查用户名是否存在
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, acc.username) == 0) {
            printf("用户名已存在！\n");
            return;
        }
    }

    safeInputPassword(acc.password, MAX_STR_LEN, "请输入密码: ");
    safeInput(acc.email, MAX_STR_LEN, "请输入邮箱: "); 

    while (1) {
        safeInput(acc.role, MAX_STR_LEN, "请输入角色 (student/teacher/admin): ");
        if (strcmp(acc.role, "teacher") == 0) {
            safeInput(acc.className, MAX_STR_LEN, "请输入负责班级: ");
            break;
        }
        if (strcmp(acc.role, "student") == 0) {
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

void forgotPassword() {
    char username[MAX_STR_LEN], email[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "请输入用户名: ");

    Account *target = NULL;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            target = &accounts[i];
            break;
        }
    }
    
    if (!target) {
        printf("该用户名未注册！\n");
        return;
    }

    safeInput(email, MAX_STR_LEN, "请输入注册邮箱: ");
    if (strcmp(target->email, email) != 0) {
        printf("邮箱验证失败！\n");
        return;
    }
    
    // 生成随机验证码
    srand(time(NULL));
    int verifyCode = rand() % 9000 + 1000;
    printf("验证码已发送到 %s：%d\n", email, verifyCode);
    
    int inputCode = safeInputInt("请输入收到的验证码: ", 1000, 9999);
    if (inputCode != verifyCode) {
        printf("验证码错误！\n");
        return;
    }
    
    char newpass[MAX_STR_LEN];
    safeInputPassword(newpass, MAX_STR_LEN, "请输入新密码: ");
    strcpy(target->password, newpass);
    saveAccounts();
    printf("密码重置成功！\n");
}


void analyzeAllScores() {
    if (!head) {
        printf("没有学生记录！\n");
        return;
    }
    
    int total = 0, count = 0;
    Student* cur = head;
    printf("\n=== 全局成绩分析 ===\n");
    printf("%-10s | %-15s | %-15s | 成绩 | 柱状图\n", "班级", "用户名", "姓名");
    while (cur) {
        total += cur->score;
        count++;
        printf("%-10s | %-15s | %-15s | %3d | ", 
               cur->className, cur->username, cur->name, cur->score);
        for (int i = 0; i < cur->score/5; i++) printf("█");
        printf("\n");
        cur = cur->next;
    }
    if (count > 0) {
        printf("\n平均成绩: %.1f\n", (float)total/count);
    }
}
void sortStudentsByClass(const char* className, int ascending) {
    // 收集符合条件的学生
    Student* students[100];
    int count = 0;
    Student* cur = head;
    
    while(cur && count < 100) {
        if(strcmp(cur->className, className) == 0) {
            students[count++] = cur;
        }
        cur = cur->next;
    }

    // 排序算法（冒泡排序）
    for(int i = 0; i < count-1; i++) {
        for(int j = 0; j < count-i-1; j++) {
            if(ascending ? (students[j]->score > students[j+1]->score) 
                       : (students[j]->score < students[j+1]->score)) {
                Student* temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

    // 显示结果
    printf("\n%-15s | %-15s | 成绩\n", "用户名", "姓名");
    for(int i = 0; i < count; i++) {
        printf("%-15s | %-15s | %3d\n", 
              students[i]->username, 
              students[i]->name, 
              students[i]->score);
    }
}


Account* login() {
    char username[MAX_STR_LEN], password[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "用户名: ");
    safeInputPassword(password, MAX_STR_LEN, "密码: ");
    
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
void teacherMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 教师菜单 (%s) ===\n", acc->className);
        printf("1. 添加学生\n");
        printf("2. 查看本班学生\n");
        printf("3. 修改学生信息\n");
        printf("4. 删除学生\n");
        printf("5. 班级成绩分析\n");
        printf("6. 成绩排序\n");  // 新增选项
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 6);  // 修改选项范围
        
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
            
            case 6: {
                printf("\n排序方式：");
                int sortType = safeInputInt("1.降序 2.升序 : ", 1, 2);
                sortStudentsByClass(acc->className, sortType == 2);
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

void adminStudentManagement() {
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
            case 1: {
                Student* cur = head;
                printf("\n%-15s | %-15s | %-10s | 成绩\n", "用户名", "姓名", "班级");
                while(cur) {
                    printf("%-15s | %-15s | %-10s | %3d\n", 
                          cur->username, cur->name, cur->className, cur->score);
                    cur = cur->next;
                }
                break;
            }
            case 2: 
                addStudent(NULL); // 传递NULL表示管理员权限
                break;
            case 3: {
                char username[MAX_STR_LEN];
                safeInput(username, MAX_STR_LEN, "要修改的学生用户名: ");
                Student* target = findStudentByUsername(username);
                
                if (target) {
                    printf("原姓名: %s\n", target->name);
                    safeInput(target->name, MAX_STR_LEN, "新姓名(直接回车保留): ");
                    
                    printf("原班级: %s\n", target->className);
                    safeInput(target->className, MAX_STR_LEN, "新班级(直接回车保留): ");
                    
                    printf("原成绩: %d\n", target->score);
                    target->score = safeInputInt("新成绩(输入-1保留): ", -1, MAX_SCORE);
                    if(target->score == -1) target->score = target->score; // 保留原值
                    
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
                
                if (target) {
                    // 确认删除
                    char confirm[MAX_STR_LEN];
                    safeInput(confirm, MAX_STR_LEN, "确认删除？(y/n): ");
                    if(tolower(confirm[0]) == 'y') {
                        if (target->prev) target->prev->next = target->next;
                        else head = target->next;
                        
                        if (target->next) target->next->prev = target->prev;
                        else tail = target->prev;
                        
                        free(target);
                        saveStudentsToFile();
                        printf("删除成功！\n");
                    }
                } else {
                    printf("找不到该学生！\n");
                }
                break;
            }
            case 5:
                analyzeAllScores();
                break;
        }
    } while(subChoice != 0);
}

void adminMenu(Account* acc) {
    int choice;
    do {
        printf("\n=== 管理员菜单 ===\n");
        printf("1. 学生管理\n");
        printf("2. 账号管理\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 2);
        
        switch(choice) {
            case 1: 
                adminStudentManagement();
                break;
            case 2: 
                adminAccountManagement();
                break;
        }
    } while(choice != 0);
}


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


int main() {
    loadAccounts();
    loadStudentsFromFile();
    
    int choice;
    do {
        printf("\n=== 主菜单 ===\n");
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("3. 找回密码\n"); 
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
                forgotPassword();
                break;
        }
    } while (choice != 0);
    while (head) {
        Student* temp = head;
        head = head->next;
        free(temp);
    }
    printf("系统已安全退出\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACCOUNTS 100
#define MAX_STR_LEN 20
#define ID_LEN 10
#define MIN_SCORE 0
#define MAX_SCORE 100

typedef struct {
    char username[MAX_STR_LEN];
    char password[MAX_STR_LEN];
    char role[MAX_STR_LEN];
    char student_id[ID_LEN+1];
} Account;

typedef struct Student {
    char student_id[ID_LEN+1];
    char name[MAX_STR_LEN];
    int score;
    struct Student* prev;
    struct Student* next;
} Student;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

Student* head = NULL;
Student* tail = NULL;

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
        printf("\n输入无效，请输入 %d~%d 之间的整数\n", min, max);
    }
}

int isValidStudentID(const char* id) {
    if (strlen(id) != ID_LEN) return 0;
    for (int i = 0; i < ID_LEN; i++) {
        if (!isdigit(id[i])) return 0;
    }
    return 1;
}

void loadAccounts() {
    FILE* fp = fopen("accounts.txt", "r");
    if (!fp) return;

    while (accountCount < MAX_ACCOUNTS &&
           fscanf(fp, "%19s %19s %19s %10s",
                  accounts[accountCount].username,
                  accounts[accountCount].password,
                  accounts[accountCount].role,
                  accounts[accountCount].student_id) == 4) {
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
                accounts[i].student_id);
    }
    fclose(fp);
}

Student* findStudentByID(const char* id) {
    Student* cur = head;
    while (cur) {
        if (strcmp(cur->student_id, id) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void saveStudents() {
    FILE* fp = fopen("students.txt", "w");
    Student* cur = head;
    while (cur) {
        fprintf(fp, "%s %s %d\n", cur->student_id, cur->name, cur->score);
        cur = cur->next;
    }
    fclose(fp);
}

void loadStudents() {
    FILE* fp = fopen("students.txt", "r");
    if (!fp) return;

    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        Student* s = (Student*)malloc(sizeof(Student));
        if (sscanf(line, "%10s %19s %d", s->student_id, s->name, &s->score) != 3) {
            free(s);
            continue;
        }
        if (!isValidStudentID(s->student_id) || findStudentByID(s->student_id)) {
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

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("系统用户已达上限！\n");
        return;
    }

    Account acc;
    while (1) {
        safeInput(acc.username, MAX_STR_LEN, "请输入用户名: ");
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

    while (1) {
        safeInput(acc.role, MAX_STR_LEN, "请输入角色 (student/teacher/admin): ");
        if (strcmp(acc.role, "student") == 0 || 
            strcmp(acc.role, "teacher") == 0 || 
            strcmp(acc.role, "admin") == 0) break;
        printf("角色无效！\n");
    }

    if (strcmp(acc.role, "student") == 0) {
        while (1) {
            safeInput(acc.student_id, ID_LEN+1, "请输入学号（10位数字）: ");
            if (!isValidStudentID(acc.student_id)) {
                printf("学号格式错误！\n");
                continue;
            }
            int exists = 0;
            for (int i = 0; i < accountCount; i++) {
                if (strcmp(accounts[i].student_id, acc.student_id) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) break;
            printf("该学号已被注册！\n");
        }
    } else {
        strcpy(acc.student_id, "");
    }

    safeInput(acc.password, MAX_STR_LEN, "请输入密码: ");
    accounts[accountCount++] = acc;
    saveAccounts();
    printf("注册成功！\n");
}

Account* login() {
    char username[MAX_STR_LEN], password[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "请输入用户名: ");
    safeInput(password, MAX_STR_LEN, "请输入密码: ");
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            printf("登录成功，欢迎 %s！\n", username);
            return &accounts[i];
        }
    }
    printf("用户名或密码错误！\n");
    return NULL;
}

void changePassword() {
    char username[MAX_STR_LEN], oldPass[MAX_STR_LEN], newPass[MAX_STR_LEN];
    safeInput(username, MAX_STR_LEN, "请输入用户名: ");
    safeInput(oldPass, MAX_STR_LEN, "请输入原密码: ");
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, oldPass) == 0) {
            safeInput(newPass, MAX_STR_LEN, "请输入新密码: ");
            strcpy(accounts[i].password, newPass);
            saveAccounts();
            printf("密码修改成功！\n");
            return;
        }
    }
    printf("用户名或密码错误，修改失败！\n");
}

void addStudent() {
    char id[ID_LEN + 1], name[MAX_STR_LEN];
    int score;

    safeInput(id, sizeof(id), "请输入学生学号（10位数字）: ");
    if (!isValidStudentID(id)) {
        printf("学号格式错误！\n");
        return;
    }

    if (findStudentByID(id)) {
        printf("该学生已存在！\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].student_id, id) == 0 &&
            strcmp(accounts[i].role, "student") == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到该学号对应的注册学生账号，无法添加！\n");
        return;
    }

    safeInput(name, sizeof(name), "请输入学生姓名: ");
    score = safeInputInt("请输入学生成绩（0-100）: ", MIN_SCORE, MAX_SCORE);

    Student* s = (Student*)malloc(sizeof(Student));
    strcpy(s->student_id, id);
    strcpy(s->name, name);
    s->score = score;
    s->prev = tail;
    s->next = NULL;

    if (tail) tail->next = s;
    else head = s;
    tail = s;

    saveStudents();
    printf("学生信息添加成功！\n");
}

void listStudents(int perPage) {
    Student* cur = head;
    int total = 0;
    for (Student* tmp = head; tmp; tmp = tmp->next) total++;
    if (total == 0) {
        printf("暂无学生信息。\n");
        return;
    }

    int page = 1;
    while (1) {
        printf("\n第 %d 页（每页 %d 条，共 %d 条）:\n", page, perPage, total);
        printf("--------------------------------------------------\n");
        printf("学号         姓名           成绩\n");
        printf("--------------------------------------------------\n");

        int start = (page - 1) * perPage;
        int count = 0;
        cur = head;
        for (int i = 0; i < start && cur; i++) cur = cur->next;
        while (cur && count < perPage) {
            printf("%-12s %-15s %d\n", cur->student_id, cur->name, cur->score);
            cur = cur->next;
            count++;
        }

        printf("--------------------------------------------------\n");
        printf("n: 下一页, p: 上一页, q: 退出\n");
        printf("请输入指令: ");

        char cmd;
        scanf(" %c", &cmd);
        while (getchar() != '\n');
        if (cmd == 'n') {
            if (page * perPage >= total) printf("已经是最后一页！\n");
            else page++;
        } else if (cmd == 'p') {
            if (page == 1) printf("已经是第一页！\n");
            else page--;
        } else if (cmd == 'q') {
            break;
        } else {
            printf("无效指令！\n");
        }
    }
}

void modifyStudent() {
    char id[ID_LEN + 1];
    safeInput(id, sizeof(id), "请输入要修改的学生学号: ");
    Student* s = findStudentByID(id);
    if (!s) {
        printf("未找到该学生！\n");
        return;
    }

    printf("当前信息 - 姓名: %s，成绩: %d\n", s->name, s->score);
    safeInput(s->name, MAX_STR_LEN, "请输入新的姓名: ");
    s->score = safeInputInt("请输入新的成绩（0-100）: ", MIN_SCORE, MAX_SCORE);
    saveStudents();
    printf("修改成功！\n");
}

void deleteStudent() {
    char id[ID_LEN + 1];
    safeInput(id, sizeof(id), "请输入要删除的学生学号: ");
    Student* s = findStudentByID(id);
    if (!s) {
        printf("未找到该学生！\n");
        return;
    }

    if (s->prev) s->prev->next = s->next;
    else head = s->next;
    if (s->next) s->next->prev = s->prev;
    else tail = s->prev;

    free(s);
    saveStudents();
    printf("学生信息删除成功！\n");
}

void analyzeScores() {
    if (!head) {
        printf("暂无学生信息！\n");
        return;
    }

    int count = 0, total = 0, pass = 0;
    int max = -1, min = 101;
    Student* cur = head;

    while (cur) {
        int sc = cur->score;
        if (sc > max) max = sc;
        if (sc < min) min = sc;
        if (sc >= 60) pass++;
        total += sc;
        count++;
        cur = cur->next;
    }

    printf("\n=== 成绩分析 ===\n");
    printf("总人数: %d\n", count);
    printf("平均分: %.2f\n", (double)total / count);
    printf("最高分: %d\n", max);
    printf("最低分: %d\n", min);
    printf("及格人数: %d（及格率 %.2f%%）\n", pass, (double)pass / count * 100);
}

void studentMenu(Account* acc) {
    Student* s = findStudentByID(acc->student_id);
    if (!s) {
        printf("未找到你的成绩记录！\n");
        return;
    }

    int choice;
    do {
        printf("\n=== 学生菜单 ===\n");
        printf("1. 查看我的成绩\n");
        printf("2. 查看全班成绩\n");
        printf("0. 返回上级\n");
        choice = safeInputInt("请选择: ", 0, 2);

        if (choice == 1) {
            printf("\n学号: %s\n", s->student_id);
            printf("姓名: %s\n", s->name);
            printf("成绩: %d\n", s->score);
        }
        else if (choice == 2) {
            listStudents(5);
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
    loadStudents();

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

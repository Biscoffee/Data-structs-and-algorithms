#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "file.h"

Student* head = NULL;
Student* tail = NULL;

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
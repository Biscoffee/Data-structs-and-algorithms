#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// 学生信息结构体
struct Student {
    int id;                 // 学号
    char name[50];          // 姓名
    char gender[10];        // 性别
    int age;                // 年龄
    char major[50];         // 专业
    char className[50];     // 班级
    float gpa;              // 平均成绩
    Student* next;          // 指向下一个节点的指针
    Student* prev;          // 指向前一个节点的指针，用于双向链表
};

// 待办事项结构体
struct TodoItem {
    int id;                 // 待办事项ID
    char title[100];        // 标题
    char description[500];  // 描述
    char deadline[20];      // 截止日期
    bool completed;         // 是否完成
    int priority;           // 优先级：1-低，2-中，3-高
    char username[50];      // 关联的用户名
    TodoItem* next;         // 指向下一个节点的指针
};

// 用户请求类型枚举
enum RequestType {
    PASSWORD_RESET = 0,     // 密码重置
    PASSWORD_CHANGE = 1,    // 密码修改
    SCORE_APPEAL = 2        // 成绩申诉
};

// 用户请求结构体
struct UserRequest {
    int id;                 // 请求ID
    char username[50];      // 用户名
    RequestType type;       // 请求类型
    char details[500];      // 请求详情
    bool processed;         // 是否已处理
    char timestamp[20];     // 时间戳
    UserRequest* next;      // 指向下一个节点的指针
};

// 用户信息结构体
struct User {
    char username[50];      // 用户名
    char password[50];      // 密码
    int userType;           // 用户类型：0-学生，1-教师，2-管理员
    char email[100];        // 邮箱，用于密码找回
    char securityQuestion[100]; // 安全问题
    char securityAnswer[100];   // 安全问题答案
    bool passwordResetRequest;  // 密码重置请求
    bool passwordChangeRequest; // 密码修改请求
    bool scoreAppealRequest;    // 成绩申诉请求
    int studentId;              // 关联的学生ID（仅对学生用户）
    User* next;             // 指向下一个节点的指针
};

// 全局变量声明
extern Student* studentHead;     // 学生链表头指针
extern User* userHead;           // 用户链表头指针
extern User* currentUser;        // 当前登录用户
extern TodoItem* todoHead;       // 待办事项链表头指针
extern UserRequest* requestHead; // 用户请求链表头指针

#endif // COMMON_H
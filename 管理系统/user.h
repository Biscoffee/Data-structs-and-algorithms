#ifndef USER_H
#define USER_H

#include "common.h"

// 用户管理相关函数声明
bool initUserSystem();                      // 初始化用户系统
bool registerUser();                        // 注册用户
bool loginUser();                          // 用户登录
bool saveUserData();                       // 保存用户数据
bool loadUserData();                       // 加载用户数据
bool forgotPassword();                     // 忘记密码/密码找回
bool changePassword();                     // 修改密码
bool resetPassword();                      // 重置密码
bool exportUserData();                     // 导出用户数据到文件
bool importUserData();                     // 从文件导入用户数据

// 待办事项管理函数声明
bool addTodoItem();                         // 添加待办事项
bool deleteTodoItem();                      // 删除待办事项
bool modifyTodoItem();                      // 修改待办事项
bool queryTodoItem();                       // 查询待办事项
bool markTodoItemCompleted();               // 标记待办事项为已完成
bool saveTodoData();                        // 保存待办事项数据
bool loadTodoData();                        // 加载待办事项数据

// 用户请求管理函数声明
bool addUserRequest(const char* username, RequestType type, const char* details);  // 添加用户请求
bool processUserRequest(int requestId);     // 处理用户请求
bool manageUserRequests();                  // 管理用户请求（密码找回、密码修改、成绩申诉）
bool saveRequestData();                     // 保存用户请求数据
bool loadRequestData();                     // 加载用户请求数据

// 菜单函数声明
void showMainMenu();                        // 显示主菜单
void showStudentMenu();                     // 显示学生端菜单
void showTeacherMenu();                     // 显示教师端菜单
void showAdminMenu();                       // 显示管理员端菜单
void showTodoMenu();                        // 显示待办事项菜单
void showRequestMenu();                     // 显示用户请求菜单

#endif // USER_H
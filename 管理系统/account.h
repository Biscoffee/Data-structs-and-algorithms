#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "common.h"

// 验证用户名是否合法
int validateUsername(const char* username);

// 验证密码是否合法
int validatePassword(const char* password);

// 验证角色是否合法
int validateRole(const char* role);

// 从文件加载账号信息
void loadAccounts();

// 保存账号信息到文件
void saveAccounts();

// 导入账号
void importAccounts();

// 导出账号
void exportAccounts();

// 注册账号
void registerAccount();

// 修改密码
void changePassword(const char* username);

// 找回密码
void forgotPassword();

// 登录
void login();

#endif // ACCOUNT_H
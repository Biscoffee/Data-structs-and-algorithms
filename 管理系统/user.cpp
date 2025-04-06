#include "user.h"

// 全局变量定义
User* userHead = nullptr;        // 用户链表头指针
User* currentUser = nullptr;     // 当前登录用户

// 用户请求队列
struct RequestNode {
    char username[50];
    int requestType;  // 0-密码找回，1-密码修改，2-成绩申诉
    char details[200];
    RequestNode* next;
};

RequestNode* requestHead = nullptr;  // 请求链表头指针

// 初始化用户系统
bool initUserSystem() {
    // 尝试加载用户数据
    if (!loadUserData()) {
        // 如果加载失败，创建默认管理员账户
        User* admin = new User;
        strcpy(admin->username, "admin");
        strcpy(admin->password, "admin123");
        admin->userType = 2;  // 管理员
        strcpy(admin->email, "admin@school.edu");
        strcpy(admin->securityQuestion, "默认安全问题");
        strcpy(admin->securityAnswer, "默认答案");
        admin->passwordResetRequest = false;
        admin->passwordChangeRequest = false;
        admin->scoreAppealRequest = false;
        admin->next = nullptr;
        
        userHead = admin;
        
        // 保存默认用户数据
        return saveUserData();
    }
    return true;
}

// 用户注册
bool registerUser() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             用户注册             " << endl;
    cout << "===================================" << endl;
    
    User* newUser = new User;
    char confirmPassword[50];
    
    cout << "请输入用户名：";
    cin >> newUser->username;
    
    // 检查用户名是否已存在
    User* current = userHead;
    while (current != nullptr) {
        if (strcmp(current->username, newUser->username) == 0) {
            cout << "该用户名已存在，请选择其他用户名！" << endl;
            delete newUser;
            system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
            return false;
        }
        current = current->next;
    }
    
    cout << "请输入密码：";
    cin >> newUser->password;
    
    cout << "请确认密码：";
    cin >> confirmPassword;
    
    if (strcmp(newUser->password, confirmPassword) != 0) {
        cout << "两次输入的密码不一致，注册失败！" << endl;
        delete newUser;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择用户类型
    int userType;
    cout << "请选择用户类型：" << endl;
    cout << "0. 学生" << endl;
    cout << "1. 教师" << endl;
    cout << "请选择：";
    cin >> userType;
    
    if (userType != 0 && userType != 1) {
        cout << "无效的用户类型，默认设置为学生！" << endl;
        userType = 0;
    }
    
    newUser->userType = userType;
    
    // 设置邮箱和安全问题（用于密码找回）
    cout << "请输入邮箱：";
    cin >> newUser->email;
    
    cout << "请设置安全问题：";
    cin.ignore();
    cin.getline(newUser->securityQuestion, 100);
    
    cout << "请设置安全问题答案：";
    cin.getline(newUser->securityAnswer, 100);
    
    // 初始化请求状态
    newUser->passwordResetRequest = false;
    newUser->passwordChangeRequest = false;
    newUser->scoreAppealRequest = false;
    newUser->next = nullptr;
    
    // 添加到链表
    if (userHead == nullptr) {
        userHead = newUser;
    } else {
        current = userHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
    
    // 保存用户数据
    if (saveUserData()) {
        cout << "注册成功！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return true;
    } else {
        cout << "注册失败，无法保存用户数据！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
}

// 重置密码（管理员功能）
bool resetPassword() {

// 显示学生端菜单
void showStudentMenu() {
    int choice = 0;
    
    while (true) {
        system("clear");  // 清屏
        cout << "===================================" << endl;
        cout << "             学生端菜单           " << endl;
        cout << "===================================" << endl;
        cout << "        1. 查询个人成绩          " << endl;
        cout << "        2. 查询班级成绩          " << endl;
        cout << "        3. 成绩分析（班内排名）  " << endl;
        cout << "        4. 成绩申诉              " << endl;
        cout << "        5. 修改密码              " << endl;
        cout << "        0. 返回主菜单            " << endl;
        cout << "===================================" << endl;
        cout << "当前用户：" << currentUser->username << endl;
        cout << "===================================" << endl;
        cout << "请选择操作：";
        cin >> choice;
        
        switch (choice) {
            case 1:
                queryStudent();  // 查询个人成绩
                break;
            case 2:
                queryClassScore();  // 查询班级成绩
                break;
            case 3:
                showRanking();  // 显示排名
                break;
            case 4:
                appealScore();  // 成绩申诉
                break;
            case 5:
                changePassword();  // 修改密码
                break;
            case 0:
                return;
            default:
                cout << "无效的选择，请重新输入！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        }
    }
}

// 显示教师端菜单
void showTeacherMenu() {
    int choice = 0;
    
    while (true) {
        system("clear");  // 清屏
        cout << "===================================" << endl;
        cout << "             教师端菜单           " << endl;
        cout << "===================================" << endl;
        cout << "        1. 添加学生信息          " << endl;
        cout << "        2. 删除学生信息          " << endl;
        cout << "        3. 修改学生信息          " << endl;
        cout << "        4. 查询学生信息          " << endl;
        cout << "        5. 查看班级成绩(翻页)    " << endl;
        cout << "        6. 导出学生信息          " << endl;
        cout << "        7. 成绩分析              " << endl;
        cout << "        8. 修改密码              " << endl;
        cout << "        0. 返回主菜单            " << endl;
        cout << "===================================" << endl;
        cout << "当前用户：" << currentUser->username << endl;
        cout << "===================================" << endl;
        cout << "请选择操作：";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addStudent();  // 添加学生
                break;
            case 2:
                deleteStudent();  // 删除学生
                break;
            case 3:
                modifyStudent();  // 修改学生信息
                break;
            case 4:
                queryStudent();  // 查询学生
                break;
            case 5:
                viewClassScoreWithPaging();  // 查看班级成绩(带翻页)
                break;
            case 6:
                exportStudentData();  // 导出学生信息
                break;
            case 7:
                analyzeScore();  // 成绩分析
                break;
            case 8:
                changePassword();  // 修改密码
                break;
            case 0:
                return;
            default:
                cout << "无效的选择，请重新输入！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        }
    }
}

// 显示管理员端菜单
void showAdminMenu() {
    int choice = 0;
    
    while (true) {
        system("clear");  // 清屏
        cout << "===================================" << endl;
        cout << "            管理员端菜单          " << endl;
        cout << "===================================" << endl;
        cout << "        1. 用户管理              " << endl;
        cout << "        2. 学生管理              " << endl;
        cout << "        3. 导出用户数据          " << endl;
        cout << "        4. 导入用户数据          " << endl;
        cout << "        5. 查看待办事项          " << endl;
        cout << "        6. 修改密码              " << endl;
        cout << "        7. 重置用户密码          " << endl;
        cout << "        0. 返回主菜单            " << endl;
        cout << "===================================" << endl;
        cout << "当前用户：" << currentUser->username << " (管理员)" << endl;
        cout << "===================================" << endl;
        cout << "请选择操作：";
        cin >> choice;
        
        switch (choice) {
            case 1:
                // 用户管理子菜单
                break;
            case 2:
                showTeacherMenu();  // 使用教师菜单进行学生管理
                break;
            case 3:
                exportUserData();  // 导出用户数据
                break;
            case 4:
                importUserData();  // 导入用户数据
                break;
            case 5:
                manageUserRequests();  // 查看待办事项
                break;
            case 6:
                changePassword();  // 修改密码
                break;
            case 7:
                resetPassword();  // 重置用户密码
                break;
            case 0:
                return;
            default:
                cout << "无效的选择，请重新输入！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        }
    }
}

// 用户登录
bool loginUser() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             用户登录             " << endl;
    cout << "===================================" << endl;
    
    char username[50];
    char password[50];
    
    cout << "请输入用户名：";
    cin >> username;
    
    cout << "请输入密码：";
    cin >> password;
    
    User* current = userHead;
    while (current != nullptr) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            currentUser = current;
            cout << "登录成功！" << endl;
            system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
            return true;
        }
        current = current->next;
    }
    
    cout << "用户名或密码错误，登录失败！" << endl;
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return false;
}

// 保存用户数据到二进制文件
bool saveUserData() {
    ofstream outFile("users.dat", ios::binary);
    if (!outFile) {
        return false;
    }
    
    User* current = userHead;
    while (current != nullptr) {
        // 写入用户数据，不包括next指针
        outFile.write(reinterpret_cast<char*>(current), sizeof(User) - sizeof(User*));
        current = current->next;
    }
    
    outFile.close();
    return true;
}

// 从二进制文件加载用户数据
bool loadUserData() {
    ifstream inFile("users.dat", ios::binary);
    if (!inFile) {
        return false;
    }
    
    // 清空现有链表
    User* current = userHead;
    while (current != nullptr) {
        User* temp = current;
        current = current->next;
        delete temp;
    }
    userHead = nullptr;
    
    // 读取用户数据
    User tempUser;
    User* lastUser = nullptr;
    
    while (inFile.read(reinterpret_cast<char*>(&tempUser), sizeof(User) - sizeof(User*))) {
        User* newUser = new User;
        memcpy(newUser, &tempUser, sizeof(User) - sizeof(User*));
        newUser->next = nullptr;
        
        if (userHead == nullptr) {
            userHead = newUser;
        } else {
            lastUser->next = newUser;
        }
        
        lastUser = newUser;
    }
    
    inFile.close();
    return true;
}

// 忘记密码/密码找回
bool forgotPassword() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             密码找回             " << endl;
    cout << "===================================" << endl;
    
    char username[50];
    char email[100];
    
    cout << "请输入用户名：";
    cin >> username;
    
    cout << "请输入注册邮箱：";
    cin >> email;
    
    User* current = userHead;
    while (current != nullptr) {
        if (strcmp(current->username, username) == 0 && strcmp(current->email, email) == 0) {
            // 验证安全问题
            char answer[100];
            cout << "安全问题：" << current->securityQuestion << endl;
            cout << "请输入答案：";
            cin.ignore();
            cin.getline(answer, 100);
            
            if (strcmp(current->securityAnswer, answer) == 0) {
                // 重置密码
                char newPassword[50];
                char confirmPassword[50];
                
                cout << "请输入新密码：";
                cin >> newPassword;
                
                cout << "请确认新密码：";
                cin >> confirmPassword;
                
                if (strcmp(newPassword, confirmPassword) == 0) {
                    strcpy(current->password, newPassword);
                    
                    // 保存用户数据
                    if (saveUserData()) {
                        cout << "密码重置成功！" << endl;
                        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                        return true;
                    } else {
                        cout << "密码重置失败，无法保存用户数据！" << endl;
                        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                        return false;
                    }
                } else {
                    cout << "两次输入的密码不一致，密码重置失败！" << endl;
                    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                    return false;
                }
            } else {
                cout << "安全问题答案错误，密码找回失败！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
        }
        current = current->next;
    }
    
    cout << "未找到匹配的用户名和邮箱，密码找回失败！" << endl;
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return false;
}

// 修改密码
bool changePassword() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             修改密码             " << endl;
    cout << "===================================" << endl;
    
    if (currentUser == nullptr) {
        cout << "请先登录！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    char oldPassword[50];
    char newPassword[50];
    char confirmPassword[50];
    
    cout << "请输入当前密码：";
    cin >> oldPassword;
    
    if (strcmp(currentUser->password, oldPassword) != 0) {
        cout << "当前密码错误，修改失败！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    cout << "请输入新密码：";
    cin >> newPassword;
    
    cout << "请确认新密码：";
    cin >> confirmPassword;
    
    if (strcmp(newPassword, confirmPassword) != 0) {
        cout << "两次输入的密码不一致，修改失败！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    strcpy(currentUser->password, newPassword);
    
    // 保存用户数据
    if (saveUserData()) {
        cout << "密码修改成功！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return true;
    } else {
        cout << "密码修改失败，无法保存用户数据！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
}

// 重置密码（管理员功能）
bool resetPassword() {

// 重置密码（管理员功能）
bool resetPassword() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             重置密码             " << endl;
    cout << "===================================" << endl;
    
    if (currentUser == nullptr || currentUser->userType != 2) {
        cout << "您没有权限执行此操作！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    char username[50];
    cout << "请输入要重置密码的用户名：";
    cin >> username;
    
    User* current = userHead;
    while (current != nullptr) {
        if (strcmp(current->username, username) == 0) {
            char newPassword[50];
            char confirmPassword[50];
            
            cout << "请输入新密码：";
            cin >> newPassword;
            
            cout << "请确认新密码：";
            cin >> confirmPassword;
            
            if (strcmp(newPassword, confirmPassword) != 0) {
                cout << "两次输入的密码不一致，重置失败！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            strcpy(current->password, newPassword);
            current->passwordResetRequest = false;  // 清除密码重置请求
            
            // 保存用户数据
            if (saveUserData()) {
                cout << "密码重置成功！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return true;
            } else {
                cout << "密码重置失败，无法保存用户数据！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
        }
        current = current->next;
    }
    
    cout << "未找到该用户名，重置失败！" << endl;
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return false;
}
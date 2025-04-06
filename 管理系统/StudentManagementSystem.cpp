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
    float gpa;              // 平均成绩
    Student* next;          // 指向下一个节点的指针
};

// 用户信息结构体
struct User {
    char username[50];      // 用户名
    char password[50];      // 密码
    bool isAdmin;           // 是否为管理员
    User* next;             // 指向下一个节点的指针
};

// 全局变量
Student* studentHead = nullptr;  // 学生链表头指针
User* userHead = nullptr;        // 用户链表头指针
User* currentUser = nullptr;     // 当前登录用户

// 函数声明
// 用户管理相关函数
bool initUserSystem();                      // 初始化用户系统
bool registerUser();                        // 注册用户
bool loginUser();                          // 用户登录
bool saveUserData();                       // 保存用户数据
bool loadUserData();                       // 加载用户数据

// 学生管理相关函数
bool initStudentSystem();                  // 初始化学生系统
bool addStudent();                         // 添加学生
bool deleteStudent();                      // 删除学生
bool modifyStudent();                      // 修改学生信息
bool queryStudent();                       // 查询学生
bool insertStudent();                      // 插入学生
bool statisticsStudent();                  // 统计学生信息
bool sortStudent();                        // 排序学生信息
bool saveStudentData();                    // 保存学生数据
bool loadStudentData();                    // 加载学生数据
void displayStudent(Student* student);     // 显示学生信息
void displayAllStudents();                 // 显示所有学生信息

// 菜单函数
void showMainMenu();                       // 显示主菜单
void showStudentMenu();                    // 显示学生管理菜单
void showUserMenu();                       // 显示用户管理菜单

// 主函数
int main() {
    // 初始化系统
    if (!initUserSystem() || !initStudentSystem()) {
        cout << "系统初始化失败，请检查文件权限或磁盘空间！" << endl;
        return -1;
    }
    
    // 显示主菜单
    showMainMenu();
    
    return 0;
}

// 初始化用户系统
bool initUserSystem() {
    // 尝试加载用户数据
    if (!loadUserData()) {
        // 如果加载失败，创建默认管理员账户
        User* admin = new User;
        strcpy(admin->username, "admin");
        strcpy(admin->password, "admin123");
        admin->isAdmin = true;
        admin->next = nullptr;
        
        userHead = admin;
        
        // 保存默认用户数据
        return saveUserData();
    }
    return true;
}

// 初始化学生系统
bool initStudentSystem() {
    // 尝试加载学生数据
    return loadStudentData();
}

// 显示主菜单
void showMainMenu() {
    int choice = 0;
    
    while (true) {
        system("clear");  // 清屏，Windows系统使用"cls"
        cout << "===================================" << endl;
        cout << "      学生信息管理系统 v2.0       " << endl;
        cout << "===================================" << endl;
        cout << "        1. 用户登录              " << endl;
        cout << "        2. 用户注册              " << endl;
        cout << "        3. 忘记密码              " << endl;
        cout << "        0. 退出系统              " << endl;
        cout << "===================================" << endl;
        cout << "请选择操作：";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (loginUser()) {
                    // 根据用户类型显示不同的菜单
                    switch (currentUser->userType) {
                        case 0:  // 学生
                            showStudentMenu();
                            break;
                        case 1:  // 教师
                            showTeacherMenu();
                            break;
                        case 2:  // 管理员
                            showAdminMenu();
                            break;
                        default:
                            cout << "用户类型错误！" << endl;
                            system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                    }
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                forgotPassword();  // 忘记密码/密码找回
                break;
            case 0:
                cout << "感谢使用本系统，再见！" << endl;
                return;
            default:
                cout << "无效的选择，请重新输入！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停，Windows系统使用"pause"
        }
    }
}

// 显示学生管理菜单
void showStudentMenu() {
    int choice = 0;
    
    while (true) {
        system("clear");  // 清屏
        cout << "===================================" << endl;
        cout << "         学生信息管理菜单         " << endl;
        cout << "===================================" << endl;
        cout << "        1. 添加学生信息          " << endl;
        cout << "        2. 删除学生信息          " << endl;
        cout << "        3. 修改学生信息          " << endl;
        cout << "        4. 查询学生信息          " << endl;
        cout << "        5. 插入学生信息          " << endl;
        cout << "        6. 统计学生信息          " << endl;
        cout << "        7. 排序学生信息          " << endl;
        cout << "        8. 显示所有学生          " << endl;
        cout << "        0. 返回主菜单            " << endl;
        cout << "===================================" << endl;
        cout << "当前用户：" << currentUser->username << (currentUser->isAdmin ? "(管理员)" : "") << endl;
        cout << "===================================" << endl;
        cout << "请选择操作：";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                queryStudent();
                break;
            case 5:
                insertStudent();
                break;
            case 6:
                statisticsStudent();
                break;
            case 7:
                sortStudent();
                break;
            case 8:
                displayAllStudents();
                break;
            case 0:
                return;
            default:
                cout << "无效的选择，请重新输入！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        }
    }
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
    
    // 默认为普通用户
    newUser->isAdmin = false;
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

// 添加学生信息
bool addStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           添加学生信息           " << endl;
    cout << "===================================" << endl;
    
    Student* newStudent = new Student;
    
    cout << "请输入学号：";
    cin >> newStudent->id;
    
    // 检查学号是否已存在
    Student* current = studentHead;
    while (current != nullptr) {
        if (current->id == newStudent->id) {
            cout << "该学号已存在，请使用其他学号！" << endl;
            delete newStudent;
            system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
            return false;
        }
        current = current->next;
    }
    
    cout << "请输入姓名：";
    cin >> newStudent->name;
    
    cout << "请输入性别：";
    cin >> newStudent->gender;
    
    cout << "请输入年龄：";
    cin >> newStudent->age;
    
    cout << "请输入专业：";
    cin >> newStudent->major;
    
    cout << "请输入平均成绩：";
    cin >> newStudent->gpa;
    
    newStudent->next = nullptr;
    
    // 添加到链表末尾
    if (studentHead == nullptr) {
        studentHead = newStudent;
    } else {
        current = studentHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newStudent;
    }
    
    // 保存学生数据
    if (saveStudentData()) {
        cout << "添加学生信息成功！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return true;
    } else {
        cout << "添加失败，无法保存学生数据！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
}

// 删除学生信息
bool deleteStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           删除学生信息           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法删除！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    int id;
    cout << "请输入要删除的学生学号：";
    cin >> id;
    
    Student* current = studentHead;
    Student* previous = nullptr;
    
    // 查找要删除的学生
    while (current != nullptr && current->id != id) {
        previous = current;
        current = current->next;
    }
    
    if (current == nullptr) {
        cout << "未找到该学号的学生！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 删除学生节点
    if (previous == nullptr) {
        // 删除的是头节点
        studentHead = current->next;
    } else {
        previous->next = current->next;
    }
    
    delete current;
    
    // 保存学生数据
    if (saveStudentData()) {
        cout << "删除学生信息成功！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return true;
    } else {
        cout << "删除失败，无法保存学生数据！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
}

// 修改学生信息
bool modifyStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           修改学生信息           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法修改！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    int id;
    cout << "请输入要修改的学生学号：";
    cin >> id;
    
    Student* current = studentHead;
    
    // 查找要修改的学生
    while (current != nullptr && current->id != id) {
        current = current->next;
    }
    
    if (current == nullptr) {
        cout << "未找到该学号的学生！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 显示当前信息
    cout << "当前学生信息：" << endl;
    displayStudent(current);
    
    // 修改信息
    cout << "\n请输入新的信息（不修改的项目请输入原值）：" << endl;
    
    cout << "请输入姓名：";
    cin >> current->name;
    
    cout << "请输入性别：";
    cin >> current->gender;
    
    cout << "请输入年龄：";
    cin >> current->age;
    
    cout << "请输入专业：";
    cin >> current->major;
    
    cout << "请输入平均成绩：";
    cin >> current->gpa;
    
    // 保存学生数据
    if (saveStudentData()) {
        cout << "修改学生信息成功！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return true;
    } else {
        cout << "修改失败，无法保存学生数据！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
}

// 查询学生信息
bool queryStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           查询学生信息           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法查询！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    int choice;
    cout << "请选择查询方式：" << endl;
    cout << "1. 按学号查询" << endl;
    cout << "2. 按姓名查询" << endl;
    cout << "3. 按专业查询" << endl;
    cout << "请选择：";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            int id;
            cout << "请输入学号：";
            cin >> id;
            
            Student* current = studentHead;
            bool found = false;
            
            while (current != nullptr) {
                if (current->id == id) {
                    displayStudent(current);
                    found = true;
                    break;
                }
                current = current->next;
            }
            
            if (!found) {
                cout << "未找到该学号的学生！" << endl;
            }
            break;
        }
        case 2: {
            char name[50];
            cout << "请输入姓名：";
            cin >> name;
            
            Student* current = studentHead;
            bool found = false;
            
            while (current != nullptr) {
                if (strcmp(current->name, name) == 0) {
                    displayStudent(current);
                    found = true;
                }
                current = current->next;
            }
            
            if (!found) {
                cout << "未找到该姓名的学生！" << endl;
            }
            break;
        }
        case 3: {
            char major[50];
            cout << "请输入专业：";
            cin >> major;
            
            Student* current = studentHead;
            bool found = false;
            
            while (current != nullptr) {
                if (strcmp(current->major, major) == 0) {
                    displayStudent(current);
                    found = true;
                }
                current = current->next;
            }
            
            if (!found) {
                cout << "未找到该专业的学生！" << endl;
            }
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            break;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 插入学生信息
bool insertStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           插入学生信息           " << endl;
    cout << "===================================" << endl;
    
    Student* newStudent = new Student;
    
    cout << "请输入学号：";
    cin >> newStudent->id;
    
    // 检查学号是否已存在
    Student* current = studentHead;
    while (current != nullptr) {
        if (current->id == newStudent->id) {
            cout << "该学号已存在，请使用其他学号！" << endl;
            delete newStudent;
            system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
            return false;
        }
        current = current->next;
    }
    
    cout << "请输入姓名：";
    cin >> newStudent->name;
    
    cout << "请输入性别：";
    cin >> newStudent->gender;
    
    cout << "请输入年龄：";
    cin >> newStudent->age;
    
    cout << "请输入专业：";
    cin >> newStudent->major;
    
    cout << "请输入平均成绩：";
    cin >> newStudent->gpa;
    
    newStudent->next = nullptr;
    
    // 选择插入位置
    int position;
    cout << "请选择插入位置：" << endl;
    cout << "1. 插入到链表头部" << endl;
    cout << "2. 插入到链表尾部" << endl;
    cout << "3. 插入到指定位置" << endl;
    cout << "请选择：";
    cin >> position;
    
    switch (position) {
        case 1: {
            // 插入到链表头部
            newStudent->next = studentHead;
            studentHead = newStudent;
            break;
        }
        case 2: {
            // 插入到链表尾部
            if (studentHead == nullptr) {
                studentHead = newStudent;
            } else {
                current = studentHead;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newStudent;
            }
            break;
        }
        case 3: {
            // 插入到指定位置
            int pos;
            cout << "请输入要插入的位置（从1开始）：";
            cin >> pos;
            
            if (pos <= 0) {
                cout << "位置无效，必须大于0！" << endl;
                delete newStudent;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            if (pos == 1 || studentHead == nullptr) {
                // 插入到链表头部
                newStudent->next = studentHead;
                studentHead = newStudent;
            } else {
                current = studentHead;
                int count = 1;
                
                // 找到插入位置的前一个节点
                while (current->next != nullptr && count < pos - 1) {
                    current = current->next;
                    count++;
                }
                
                // 插入节点
                newStudent->next = current->next;
                current->next = newStudent;
            }
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            delete newStudent;
            system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
            return false;
    }
    
    // 保存学生数据
    if (saveStudentData()) {
        cout << "插入学生信息成功！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return true;
    } else {
        cout << "插入失败，无法保存学生数据！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
}

// 统计学生信息
bool statisticsStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           统计学生信息           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法统计！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    int totalStudents = 0;
    int maleCount = 0;
    int femaleCount = 0;
    float totalGpa = 0.0;
    int ageSum = 0;
    
    // 专业统计
    struct MajorStat {
        char major[50];
        int count;
        MajorStat* next;
    };
    
    MajorStat* majorHead = nullptr;
    
    Student* current = studentHead;
    while (current != nullptr) {
        totalStudents++;
        
        // 性别统计
        if (strcmp(current->gender, "男") == 0 || strcmp(current->gender, "male") == 0) {
            maleCount++;
        } else if (strcmp(current->gender, "女") == 0 || strcmp(current->gender, "female") == 0) {
            femaleCount++;
        }
        
        // GPA统计
        totalGpa += current->gpa;
        
        // 年龄统计
        ageSum += current->age;
        
        // 专业统计
        bool majorFound = false;
        MajorStat* majorCurrent = majorHead;
        
        while (majorCurrent != nullptr) {
            if (strcmp(majorCurrent->major, current->major) == 0) {
                majorCurrent->count++;
                majorFound = true;
                break;
            }
            majorCurrent = majorCurrent->next;
        }
        
        if (!majorFound) {
            MajorStat* newMajor = new MajorStat;
            strcpy(newMajor->major, current->major);
            newMajor->count = 1;
            newMajor->next = nullptr;
            
            // 添加到专业统计链表
            if (majorHead == nullptr) {
                majorHead = newMajor;
            } else {
                MajorStat* temp = majorHead;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newMajor;
            }
        }
        
        current = current->next;
    }
    
    // 显示统计结果
    cout << "===================================" << endl;
    cout << "总学生数：" << totalStudents << endl;
    cout << "男生人数：" << maleCount << endl;
    cout << "女生人数：" << femaleCount << endl;
    cout << "平均年龄：" << fixed << setprecision(2) << (float)ageSum / totalStudents << endl;
    cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / totalStudents << endl;
    cout << "===================================" << endl;
    cout << "专业分布：" << endl;
    
    MajorStat* majorCurrent = majorHead;
    while (majorCurrent != nullptr) {
        cout << majorCurrent->major << "：" << majorCurrent->count << "人" << endl;
        MajorStat* temp = majorCurrent;
        majorCurrent = majorCurrent->next;
        delete temp;  // 释放内存
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 排序学生信息
bool sortStudent() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           排序学生信息           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr || studentHead->next == nullptr) {
        cout << "学生列表为空或只有一个学生，无需排序！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    int choice;
    cout << "请选择排序方式：" << endl;
    cout << "1. 按学号排序" << endl;
    cout << "2. 按姓名排序" << endl;
    cout << "3. 按年龄排序" << endl;
    cout << "4. 按成绩排序" << endl;
    cout << "请选择：";
    cin >> choice;
    
    int order;
    cout << "请选择排序顺序：" << endl;
    cout << "1. 升序" << endl;
    cout << "2. 降序" << endl;
    cout << "请选择：";
    cin >> order;
    
    // 冒泡排序
    Student* p = nullptr;
    Student* q = nullptr;
    bool swapped;
    
    for (p = studentHead; p != nullptr; p = p->next) {
        swapped = false;
        for (q = studentHead; q->next != nullptr; q = q->next) {
            bool shouldSwap = false;
            
            // 根据不同的排序方式比较
            switch (choice) {
                case 1:  // 按学号排序
                    shouldSwap = (order == 1) ? (q->id > q->next->id) : (q->id < q->next->id);
                    break;
                case 2:  // 按姓名排序
                    shouldSwap = (order == 1) ? (strcmp(q->name, q->next->name) > 0) : (strcmp(q->name, q->next->name) < 0);
                    break;
                case 3:  // 按年龄排序
                    shouldSwap = (order == 1) ? (q->age > q->next->age) : (q->age < q->next->age);
                    break;
                case 4:  // 按成绩排序
                    shouldSwap = (order == 1) ? (q->gpa > q->next->gpa) : (q->gpa < q->next->gpa);
                    break;
                default:
                    cout << "无效的选择！" << endl;
                    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                    return false;
            }
            
            // 如果需要交换，则交换节点的数据（不交换节点本身）
            if (shouldSwap) {
                // 交换数据
                Student temp;
                temp.id = q->id;
                strcpy(temp.name, q->name);
                strcpy(temp.gender, q->gender);
                temp.age = q->age;
                strcpy(temp.major, q->major);
                temp.gpa = q->gpa;
                
                q->id = q->next->id;
                strcpy(q->name, q->next->name);
                strcpy(q->gender, q->next->gender);
                q->age = q->next->age;
                strcpy(q->major, q->next->major);
                q->gpa = q->next->gpa;
                
                q->next->id = temp.id;
                strcpy(q->next->name, temp.name);
                strcpy(q->next->gender, temp.gender);
                q->next->age = temp.age;
                strcpy(q->next->major, temp.major);
                q->next->gpa = temp.gpa;
                
                swapped = true;
            }
        }
        
        // 如果内层循环没有发生交换，则已经排序完成
        if (!swapped) {
            break;
        }
    }
    
    cout << "排序完成！" << endl;
    displayAllStudents();
    
    // 保存排序后的数据
    if (saveStudentData()) {
        cout << "排序结果已保存！" << endl;
    } else {
        cout << "排序结果保存失败！" << endl;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 保存学生数据到二进制文件
bool saveStudentData() {
    ofstream outFile("students.dat", ios::binary);
    if (!outFile) {
        return false;
    }
    
    Student* current = studentHead;
    while (current != nullptr) {
        // 写入学生数据，不包括next指针
        outFile.write(reinterpret_cast<char*>(current), sizeof(Student) - sizeof(Student*));
        current = current->next;
    }
    
    outFile.close();
    return true;
}

// 从二进制文件加载学生数据
bool loadStudentData() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        return true;  // 文件不存在，返回true表示初始化成功（空链表）
    }
    
    // 清空现有链表
    Student* current = studentHead;
    while (current != nullptr) {
        Student* temp = current;
        current = current->next;
        delete temp;
    }
    studentHead = nullptr;
    
    // 读取学生数据
    Student tempStudent;
    Student* lastStudent = nullptr;
    
    while (inFile.read(reinterpret_cast<char*>(&tempStudent), sizeof(Student) - sizeof(Student*))) {
        Student* newStudent = new Student;
        memcpy(newStudent, &tempStudent, sizeof(Student) - sizeof(Student*));
        newStudent->next = nullptr;
        
        if (studentHead == nullptr) {
            studentHead = newStudent;
        } else {
            lastStudent->next = newStudent;
        }
        
        lastStudent = newStudent;
    }
    
    inFile.close();
    return true;
}

// 显示单个学生信息
void displayStudent(Student* student) {
    cout << "===================================" << endl;
    cout << "学号：" << student->id << endl;
    cout << "姓名：" << student->name << endl;
    cout << "性别：" << student->gender << endl;
    cout << "年龄：" << student->age << endl;
    cout << "专业：" << student->major << endl;
    cout << "平均成绩：" << fixed << setprecision(2) << student->gpa << endl;
    cout << "===================================" << endl;
}

// 显示所有学生信息
void displayAllStudents() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           所有学生信息           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return;
    }
    
    Student* current = studentHead;
    int count = 0;
    
    cout << left << setw(10) << "学号" << setw(15) << "姓名" << setw(10) << "性别" 
         << setw(10) << "年龄" << setw(20) << "专业" << setw(10) << "平均成绩" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    
    while (current != nullptr) {
        cout << left << setw(10) << current->id << setw(15) << current->name << setw(10) << current->gender 
             << setw(10) << current->age << setw(20) << current->major << setw(10) << fixed << setprecision(2) << current->gpa << endl;
        
        current = current->next;
        count++;
    }
    
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "总计 " << count << " 名学生" << endl;
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
}
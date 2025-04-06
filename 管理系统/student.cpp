#include "student.h"
#include "user.h"

// 全局变量定义
Student* studentHead = nullptr;  // 学生链表头指针

// 初始化学生系统
bool initStudentSystem() {
    // 尝试加载学生数据
    return loadStudentData();
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

// 查询班级成绩
bool queryClassScore() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           查询班级成绩           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法查询！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    char className[50];
    cout << "请输入班级名称：";
    cin >> className;
    
    Student* current = studentHead;
    bool found = false;
    
    cout << left << setw(10) << "学号" << setw(15) << "姓名" << setw(10) << "性别" 
         << setw(10) << "年龄" << setw(15) << "专业" << setw(10) << "平均成绩" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    
    while (current != nullptr) {
        if (strcmp(current->className, className) == 0) {
            cout << left << setw(10) << current->id << setw(15) << current->name << setw(10) << current->gender 
                 << setw(10) << current->age << setw(15) << current->major 
                 << setw(10) << fixed << setprecision(2) << current->gpa << endl;
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "未找到该班级的学生！" << endl;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 成绩分析
bool analyzeScore() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             成绩分析             " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法分析！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择分析方式
    int choice;
    cout << "请选择分析方式：" << endl;
    cout << "1. 班级成绩分析" << endl;
    cout << "2. 专业成绩分析" << endl;
    cout << "请选择：";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            char className[50];
            cout << "请输入班级名称：";
            cin >> className;
            
            // 统计班级成绩
            int count = 0;
            float totalGpa = 0.0;
            float maxGpa = 0.0;
            float minGpa = 5.0;  // 假设GPA最高为5.0
            
            Student* current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->className, className) == 0) {
                    count++;
                    totalGpa += current->gpa;
                    if (current->gpa > maxGpa) maxGpa = current->gpa;
                    if (current->gpa < minGpa) minGpa = current->gpa;
                }
                current = current->next;
            }
            
            if (count == 0) {
                cout << "未找到该班级的学生！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            // 显示统计结果
            cout << "===================================" << endl;
            cout << "班级：" << className << endl;
            cout << "学生人数：" << count << endl;
            cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / count << endl;
            cout << "最高成绩：" << fixed << setprecision(2) << maxGpa << endl;
            cout << "最低成绩：" << fixed << setprecision(2) << minGpa << endl;
            cout << "===================================" << endl;
            
            // 生成成绩分布
            int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeF = 0;
            
            current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->className, className) == 0) {
                    if (current->gpa >= 4.0) gradeA++;
                    else if (current->gpa >= 3.0) gradeB++;
                    else if (current->gpa >= 2.0) gradeC++;
                    else if (current->gpa >= 1.0) gradeD++;
                    else gradeF++;
                }
                current = current->next;
            }
            
            cout << "成绩分布：" << endl;
            cout << "A (4.0-5.0): " << gradeA << " 人 (" << fixed << setprecision(2) << (float)gradeA / count * 100 << "%)" << endl;
            cout << "B (3.0-3.9): " << gradeB << " 人 (" << fixed << setprecision(2) << (float)gradeB / count * 100 << "%)" << endl;
            cout << "C (2.0-2.9): " << gradeC << " 人 (" << fixed << setprecision(2) << (float)gradeC / count * 100 << "%)" << endl;
            cout << "D (1.0-1.9): " << gradeD << " 人 (" << fixed << setprecision(2) << (float)gradeD / count * 100 << "%)" << endl;
            cout << "F (0.0-0.9): " << gradeF << " 人 (" << fixed << setprecision(2) << (float)gradeF / count * 100 << "%)" << endl;
            
            // 简单的条形图
            cout << "\n成绩分布图：" << endl;
            cout << "A: ";
            for (int i = 0; i < gradeA * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "B: ";
            for (int i = 0; i < gradeB * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "C: ";
            for (int i = 0; i < gradeC * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "D: ";
            for (int i = 0; i < gradeD * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "F: ";
            for (int i = 0; i < gradeF * 50 / count; i++) cout << "*";
            cout << endl;
            
            break;
        }
        case 2: {
            char major[50];
            cout << "请输入专业名称：";
            cin >> major;
            
            // 统计专业成绩
            int count = 0;
            float totalGpa = 0.0;
            float maxGpa = 0.0;
            float minGpa = 5.0;  // 假设GPA最高为5.0
            
            Student* current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->major, major) == 0) {
                    count++;
                    totalGpa += current->gpa;
                    if (current->gpa > maxGpa) maxGpa = current->gpa;
                    if (current->gpa < minGpa) minGpa = current->gpa;
                }
                current = current->next;
            }
            
            if (count == 0) {
                cout << "未找到该专业的学生！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            // 显示统计结果
            cout << "===================================" << endl;
            cout << "专业：" << major << endl;
            cout << "学生人数：" << count << endl;
            cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / count << endl;
            cout << "最高成绩：" << fixed << setprecision(2) << maxGpa << endl;
            cout << "最低成绩：" << fixed << setprecision(2) << minGpa << endl;
            cout << "===================================" << endl;
            
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            break;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 显示排名
bool showRanking() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             成绩排名             " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法排名！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择排名方式
    int choice;
    cout << "请选择排名方式：" << endl;
    cout << "1. 班级内排名" << endl;
    cout << "2. 专业内排名" << endl;
    cout << "3. 全校排名" << endl;
    cout << "请选择：";
    cin >> choice;
    
    // 创建学生数组用于排序
    int studentCount = 0;
    Student* current = studentHead;
    while (current != nullptr) {
        studentCount++;
        current = current->next;
    }
    
    Student** students = new Student*[studentCount];
    current = studentHead;
    for (int i = 0; i < studentCount; i++) {
        students[i] = current;
        current = current->next;
    }
    
    // 按GPA降序排序
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j]->gpa < students[j + 1]->gpa) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    switch (choice) {
        case 1: {
            char className[50];
            cout << "请输入班级名称：";
            cin >> className;
            
            cout << "\n" << className << " 班级成绩排名：" << endl;
            cout << left << setw(5) << "排名" << setw(10) << "学号" << setw(15) << "姓名" 
                 << setw(10) << "平均成绩" << endl;
            cout << "-----------------------------------" << endl;
            
            int rank = 0;
            for (int i = 0; i < studentCount; i++) {
                if (strcmp(students[i]->className, className) == 0) {
                    rank++;
                    cout << left << setw(5) << rank << setw(10) << students[i]->id 
                         << setw(15) << students[i]->name 
                         << setw(10) << fixed << setprecision(2) << students[i]->gpa << endl;
                }
            }
            
            if (rank == 0) {
                cout << "未找到该班级的学生！" << endl;
            }
            
            break;
        }
        case 2: {
            char major[50];
            cout << "请输入专业名称：";
            cin >> major;
            
            cout << "\n" << major << " 专业成绩排名：" << endl;
            cout << left << setw(5) << "排名" << setw(10) << "学号" << setw(15) << "姓名" 
                 << setw(15) << "班级" << setw(10) << "平均成

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
    
    // 班级统计
    struct ClassStat {
        char className[50];
        int count;
        ClassStat* next;
    };
    
    MajorStat* majorHead = nullptr;
    ClassStat* classHead = nullptr;
    
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
        
        // 班级统计
        bool classFound = false;
        ClassStat* classCurrent = classHead;
        
        while (classCurrent != nullptr) {
            if (strcmp(classCurrent->className, current->className) == 0) {
                classCurrent->count++;
                classFound = true;
                break;
            }
            classCurrent = classCurrent->next;
        }
        
        if (!classFound) {
            ClassStat* newClass = new ClassStat;
            strcpy(newClass->className, current->className);
            newClass->count = 1;
            newClass->next = nullptr;
            
            // 添加到班级统计链表
            if (classHead == nullptr) {
                classHead = newClass;
            } else {
                ClassStat* temp = classHead;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newClass;
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
    
    cout << "===================================" << endl;
    cout << "班级分布：" << endl;
    
    ClassStat* classCurrent = classHead;
    while (classCurrent != nullptr) {
        cout << classCurrent->className << "：" << classCurrent->count << "人" << endl;
        ClassStat* temp = classCurrent;
        classCurrent = classCurrent->next;
        delete temp;  // 释放内存
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 查询班级成绩
bool queryClassScore() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           查询班级成绩           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法查询！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    char className[50];
    cout << "请输入班级名称：";
    cin >> className;
    
    Student* current = studentHead;
    bool found = false;
    
    cout << left << setw(10) << "学号" << setw(15) << "姓名" << setw(10) << "性别" 
         << setw(10) << "年龄" << setw(15) << "专业" << setw(10) << "平均成绩" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    
    while (current != nullptr) {
        if (strcmp(current->className, className) == 0) {
            cout << left << setw(10) << current->id << setw(15) << current->name << setw(10) << current->gender 
                 << setw(10) << current->age << setw(15) << current->major 
                 << setw(10) << fixed << setprecision(2) << current->gpa << endl;
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "未找到该班级的学生！" << endl;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 成绩分析
bool analyzeScore() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             成绩分析             " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法分析！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择分析方式
    int choice;
    cout << "请选择分析方式：" << endl;
    cout << "1. 班级成绩分析" << endl;
    cout << "2. 专业成绩分析" << endl;
    cout << "请选择：";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            char className[50];
            cout << "请输入班级名称：";
            cin >> className;
            
            // 统计班级成绩
            int count = 0;
            float totalGpa = 0.0;
            float maxGpa = 0.0;
            float minGpa = 5.0;  // 假设GPA最高为5.0
            
            Student* current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->className, className) == 0) {
                    count++;
                    totalGpa += current->gpa;
                    if (current->gpa > maxGpa) maxGpa = current->gpa;
                    if (current->gpa < minGpa) minGpa = current->gpa;
                }
                current = current->next;
            }
            
            if (count == 0) {
                cout << "未找到该班级的学生！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            // 显示统计结果
            cout << "===================================" << endl;
            cout << "班级：" << className << endl;
            cout << "学生人数：" << count << endl;
            cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / count << endl;
            cout << "最高成绩：" << fixed << setprecision(2) << maxGpa << endl;
            cout << "最低成绩：" << fixed << setprecision(2) << minGpa << endl;
            cout << "===================================" << endl;
            
            // 生成成绩分布
            int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeF = 0;
            
            current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->className, className) == 0) {
                    if (current->gpa >= 4.0) gradeA++;
                    else if (current->gpa >= 3.0) gradeB++;
                    else if (current->gpa >= 2.0) gradeC++;
                    else if (current->gpa >= 1.0) gradeD++;
                    else gradeF++;
                }
                current = current->next;
            }
            
            cout << "成绩分布：" << endl;
            cout << "A (4.0-5.0): " << gradeA << " 人 (" << fixed << setprecision(2) << (float)gradeA / count * 100 << "%)" << endl;
            cout << "B (3.0-3.9): " << gradeB << " 人 (" << fixed << setprecision(2) << (float)gradeB / count * 100 << "%)" << endl;
            cout << "C (2.0-2.9): " << gradeC << " 人 (" << fixed << setprecision(2) << (float)gradeC / count * 100 << "%)" << endl;
            cout << "D (1.0-1.9): " << gradeD << " 人 (" << fixed << setprecision(2) << (float)gradeD / count * 100 << "%)" << endl;
            cout << "F (0.0-0.9): " << gradeF << " 人 (" << fixed << setprecision(2) << (float)gradeF / count * 100 << "%)" << endl;
            
            // 简单的条形图
            cout << "\n成绩分布图：" << endl;
            cout << "A: ";
            for (int i = 0; i < gradeA * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "B: ";
            for (int i = 0; i < gradeB * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "C: ";
            for (int i = 0; i < gradeC * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "D: ";
            for (int i = 0; i < gradeD * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "F: ";
            for (int i = 0; i < gradeF * 50 / count; i++) cout << "*";
            cout << endl;
            
            break;
        }
        case 2: {
            char major[50];
            cout << "请输入专业名称：";
            cin >> major;
            
            // 统计专业成绩
            int count = 0;
            float totalGpa = 0.0;
            float maxGpa = 0.0;
            float minGpa = 5.0;  // 假设GPA最高为5.0
            
            Student* current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->major, major) == 0) {
                    count++;
                    totalGpa += current->gpa;
                    if (current->gpa > maxGpa) maxGpa = current->gpa;
                    if (current->gpa < minGpa) minGpa = current->gpa;
                }
                current = current->next;
            }
            
            if (count == 0) {
                cout << "未找到该专业的学生！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            // 显示统计结果
            cout << "===================================" << endl;
            cout << "专业：" << major << endl;
            cout << "学生人数：" << count << endl;
            cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / count << endl;
            cout << "最高成绩：" << fixed << setprecision(2) << maxGpa << endl;
            cout << "最低成绩：" << fixed << setprecision(2) << minGpa << endl;
            cout << "===================================" << endl;
            
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            break;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 显示排名
bool showRanking() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             成绩排名             " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法排名！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择排名方式
    int choice;
    cout << "请选择排名方式：" << endl;
    cout << "1. 班级内排名" << endl;
    cout << "2. 专业内排名" << endl;
    cout << "3. 全校排名" << endl;
    cout << "请选择：";
    cin >> choice;
    
    // 创建学生数组用于排序
    int studentCount = 0;
    Student* current = studentHead;
    while (current != nullptr) {
        studentCount++;
        current = current->next;
    }
    
    Student** students = new Student*[studentCount];
    current = studentHead;
    for (int i = 0; i < studentCount; i++) {
        students[i] = current;
        current = current->next;
    }
    
    // 按GPA降序排序
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j]->gpa < students[j + 1]->gpa) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    switch (choice) {
        case 1: {
            char className[50];
            cout << "请输入班级名称：";
            cin >> className;
            
            cout << "\n" << className << " 班级成绩排名：" << endl;
            cout << left << setw(5) << "排名" << setw(10) << "学号" << setw(15) << "姓名" 
                 << setw(10) << "平均成绩" << endl;
            cout << "-----------------------------------" << endl;
            
            int rank = 0;
            for (int i = 0; i < studentCount; i++) {
                if (strcmp(students[i]->className, className) == 0) {
                    rank++;
                    cout << left << setw(5) << rank << setw(10) << students[i]->id 
                         << setw(15) << students[i]->name 
                         << setw(10) << fixed << setprecision(2) << students[i]->gpa << endl;
                }
            }
            
            if (rank == 0) {
                cout << "未找到该班级的学生！" << endl;
            }
            
            break;
        }
        case 2: {
            char major[50];
            cout << "请输入专业名称：";
            cin >> major;
            
            cout << "\n" << major << " 专业成绩排名：" << endl;
            cout << left << setw(5) << "排名" << setw(10) << "学号" << setw(15) << "姓名" 
                 << setw(15) << "班级" << setw(10) << "平均成

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

// 查询班级成绩
bool queryClassScore() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "           查询班级成绩           " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法查询！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    char className[50];
    cout << "请输入班级名称：";
    cin >> className;
    
    Student* current = studentHead;
    bool found = false;
    
    cout << left << setw(10) << "学号" << setw(15) << "姓名" << setw(10) << "性别" 
         << setw(10) << "年龄" << setw(15) << "专业" << setw(10) << "平均成绩" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    
    while (current != nullptr) {
        if (strcmp(current->className, className) == 0) {
            cout << left << setw(10) << current->id << setw(15) << current->name << setw(10) << current->gender 
                 << setw(10) << current->age << setw(15) << current->major 
                 << setw(10) << fixed << setprecision(2) << current->gpa << endl;
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "未找到该班级的学生！" << endl;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 成绩分析
bool analyzeScore() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             成绩分析             " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法分析！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择分析方式
    int choice;
    cout << "请选择分析方式：" << endl;
    cout << "1. 班级成绩分析" << endl;
    cout << "2. 专业成绩分析" << endl;
    cout << "请选择：";
    cin >> choice;
    
    switch (choice) {
        case 1: {
            char className[50];
            cout << "请输入班级名称：";
            cin >> className;
            
            // 统计班级成绩
            int count = 0;
            float totalGpa = 0.0;
            float maxGpa = 0.0;
            float minGpa = 5.0;  // 假设GPA最高为5.0
            
            Student* current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->className, className) == 0) {
                    count++;
                    totalGpa += current->gpa;
                    if (current->gpa > maxGpa) maxGpa = current->gpa;
                    if (current->gpa < minGpa) minGpa = current->gpa;
                }
                current = current->next;
            }
            
            if (count == 0) {
                cout << "未找到该班级的学生！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            // 显示统计结果
            cout << "===================================" << endl;
            cout << "班级：" << className << endl;
            cout << "学生人数：" << count << endl;
            cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / count << endl;
            cout << "最高成绩：" << fixed << setprecision(2) << maxGpa << endl;
            cout << "最低成绩：" << fixed << setprecision(2) << minGpa << endl;
            cout << "===================================" << endl;
            
            // 生成成绩分布
            int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeF = 0;
            
            current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->className, className) == 0) {
                    if (current->gpa >= 4.0) gradeA++;
                    else if (current->gpa >= 3.0) gradeB++;
                    else if (current->gpa >= 2.0) gradeC++;
                    else if (current->gpa >= 1.0) gradeD++;
                    else gradeF++;
                }
                current = current->next;
            }
            
            cout << "成绩分布：" << endl;
            cout << "A (4.0-5.0): " << gradeA << " 人 (" << fixed << setprecision(2) << (float)gradeA / count * 100 << "%)" << endl;
            cout << "B (3.0-3.9): " << gradeB << " 人 (" << fixed << setprecision(2) << (float)gradeB / count * 100 << "%)" << endl;
            cout << "C (2.0-2.9): " << gradeC << " 人 (" << fixed << setprecision(2) << (float)gradeC / count * 100 << "%)" << endl;
            cout << "D (1.0-1.9): " << gradeD << " 人 (" << fixed << setprecision(2) << (float)gradeD / count * 100 << "%)" << endl;
            cout << "F (0.0-0.9): " << gradeF << " 人 (" << fixed << setprecision(2) << (float)gradeF / count * 100 << "%)" << endl;
            
            // 简单的条形图
            cout << "\n成绩分布图：" << endl;
            cout << "A: ";
            for (int i = 0; i < gradeA * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "B: ";
            for (int i = 0; i < gradeB * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "C: ";
            for (int i = 0; i < gradeC * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "D: ";
            for (int i = 0; i < gradeD * 50 / count; i++) cout << "*";
            cout << endl;
            
            cout << "F: ";
            for (int i = 0; i < gradeF * 50 / count; i++) cout << "*";
            cout << endl;
            
            break;
        }
        case 2: {
            char major[50];
            cout << "请输入专业名称：";
            cin >> major;
            
            // 统计专业成绩
            int count = 0;
            float totalGpa = 0.0;
            float maxGpa = 0.0;
            float minGpa = 5.0;  // 假设GPA最高为5.0
            
            Student* current = studentHead;
            while (current != nullptr) {
                if (strcmp(current->major, major) == 0) {
                    count++;
                    totalGpa += current->gpa;
                    if (current->gpa > maxGpa) maxGpa = current->gpa;
                    if (current->gpa < minGpa) minGpa = current->gpa;
                }
                current = current->next;
            }
            
            if (count == 0) {
                cout << "未找到该专业的学生！" << endl;
                system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
                return false;
            }
            
            // 显示统计结果
            cout << "===================================" << endl;
            cout << "专业：" << major << endl;
            cout << "学生人数：" << count << endl;
            cout << "平均成绩：" << fixed << setprecision(2) << totalGpa / count << endl;
            cout << "最高成绩：" << fixed << setprecision(2) << maxGpa << endl;
            cout << "最低成绩：" << fixed << setprecision(2) << minGpa << endl;
            cout << "===================================" << endl;
            
            break;
        }
        default:
            cout << "无效的选择！" << endl;
            break;
    }
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
    return true;
}

// 显示排名
bool showRanking() {
    system("clear");  // 清屏
    cout << "===================================" << endl;
    cout << "             成绩排名             " << endl;
    cout << "===================================" << endl;
    
    if (studentHead == nullptr) {
        cout << "学生列表为空，无法排名！" << endl;
        system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
        return false;
    }
    
    // 选择排名方式
    int choice;
    cout << "请选择排名方式：" << endl;
    cout << "1. 班级内排名" << endl;
    cout << "2. 专业内排名" << endl;
    cout << "3. 全校排名" << endl;
    cout << "请选择：";
    cin >> choice;
    
    // 创建学生数组用于排序
    int studentCount = 0;
    Student* current = studentHead;
    while (current != nullptr) {
        studentCount++;
        current = current->next;
    }
    
    Student** students = new Student*[studentCount];
    current = studentHead;
    for (int i = 0; i < studentCount; i++) {
        students[i] = current;
        current = current->next;
    }
    
    // 按GPA降序排序
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j]->gpa < students[j + 1]->gpa) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    switch (choice) {
        case 1: {
            char className[50];
            cout << "请输入班级名称：";
            cin >> className;
            
            cout << "\n" << className << " 班级成绩排名：" << endl;
            cout << left << setw(5) << "排名" << setw(10) << "学号" << setw(15) << "姓名" 
                 << setw(10) << "平均成绩" << endl;
            cout << "-----------------------------------" << endl;
            
            int rank = 0;
            for (int i = 0; i < studentCount; i++) {
                if (strcmp(students[i]->className, className) == 0) {
                    rank++;
                    cout << left << setw(5) << rank << setw(10) << students[i]->id 
                         << setw(15) << students[i]->name 
                         << setw(10) << fixed << setprecision(2) << students[i]->gpa << endl;
                }
            }
            
            if (rank == 0) {
                cout << "未找到该班级的学生！" << endl;
            }
            
            break;
        }
        case 2: {
            char major[50];
            cout << "请输入专业名称：";
            cin >> major;
            
            cout << "\n" << major << " 专业成绩排名：" << endl;
            cout << left << setw(5) << "排名" << setw(10) << "学号" << setw(15) << "姓名" 
                 << setw(15) << "班级" << setw(10) << "平均成

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
         << setw(10) << "年龄" << setw(15) << "班级" << setw(15) << "专业" << setw(10) << "平均成绩" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    
    while (current != nullptr) {
        cout << left << setw(10) << current->id << setw(15) << current->name << setw(10) << current->gender 
             << setw(10) << current->age << setw(15) << current->className << setw(15) << current->major 
             << setw(10) << fixed << setprecision(2) << current->gpa << endl;
        
        current = current->next;
        count++;
    }
    
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "总计 " << count << " 名学生" << endl;
    
    system("read -n 1 -s -p \"按任意键继续...\"");  // 暂停
}
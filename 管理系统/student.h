#ifndef STUDENT_H
#define STUDENT_H

#include "common.h"

// 全局变量声明
extern Student* studentHead;  // 学生链表头指针

// 学生管理相关函数声明
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

// 新增功能
bool queryClassScore();                    // 查询班级成绩
bool analyzeScore();                       // 成绩分析
bool showRanking();                        // 显示排名
bool exportStudentData();                  // 导出学生数据到文件
bool importStudentData();                  // 从文件导入学生数据
bool appealScore();                        // 成绩申诉
bool viewClassScoreWithPaging();           // 带翻页功能的查看班级成绩（教师端）
bool generateScoreChart();                 // 生成成绩图表（条形图）

#endif // STUDENT_H
#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student {
    char id[10];
    char name[20];
    int score;
    struct Student* prev;
    struct Student* next;
} Student;

extern Student* head;
extern Student* tail;

void loadStudentsFromFile();
void saveStudentsToFile();
void addStudent();
void modifyStudent();
void deleteStudent();
void analyzeScores();
void listStudents(int pageSize);
void queryOwnScore(char* username);
void queryClassScores();

#endif
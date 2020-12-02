#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <new>
#include <iostream>

using namespace std;

struct Student
{
    char name[20];
    char egn[20];
    char fnumber[20];
    int grades[10];
    float avg;
};


struct Student * initStudents(int studentsCount) {
    Student *students = new Student[studentsCount];

    for (int i = 0; i < studentsCount; i++)
    {
        printf("Students name: "); scanf("%s", &students[i].name);
        printf("Students egn: "); scanf("%s",  &students[i].egn);
        printf("Students fnumber: "); scanf("%s", &students[i].fnumber);

        printf("Enter grades, each on a new line\n");

        for (int f = 0; f <= 9; f++)
        {
            printf("Grade number %d: ", f+1);
            scanf("%d", &students[i].grades[f]);
            while(students[i].grades[f] < 2 || students[i].grades[f] > 6){
                printf("Incorrect grade.\n");
                printf("Grade number %d: ", f+1);
                scanf("%d", &students[i].grades[f]);
            }       
        }
    }

    return students;
}

void calculateAvg(Student *students, int studentsCount) {
    for (int i = 0; i < studentsCount; i++)
    {
        float sum = 0;
        for (int f = 0; f <= 9; f++)
        {
            sum+= students[i].grades[f];
        }
        students[i].avg = sum/10;
    }
    printf("Calculated.\n");
}

void calculateAvgSpecialStudents(Student *students, int studentsCount) {
    float avg;
    float count = 0;
    for (int i = 0; i < studentsCount; i++)
    {
        if (students[i].grades[2] >= 3) {
            avg += students[i].grades[0];
            count++;
        }
    }
    if (count > 0) {
        avg /= count;
        printf("Avg grade of the first class is - %.2f\n", avg);
    } else {
        printf("No one has passed their third exam.\n");
    }
    printf("Calculated.\n");
}

void printStudents(Student *students, int studentsCount) {
    for (int i = 0; i < studentsCount; i++)
    {
        printf("Name: %s, Egn: %s, Fnumer: %s, Grades: {", students[i].name, students[i].egn, students[i].fnumber);
        for (int f = 0; f <= 9; f++)
        {
            printf(" %d ", students[i].grades[f]);
        }
        printf("}\n");
    }
    
}

void printAverages(Student *students, int studentsCount) {
    for (int i = 0; i < studentsCount; i++)
    {
        printf("Fnumer: %s, Avg: %.2f\n", students[i].fnumber, students[i].avg);
    }
}

int main() {
    int n;
    char c;
    printf("How many students: "); scanf("%d", &n);
    Student *students = initStudents(n);
    printf("\n\n(1)Print students\n(2)Calculate avg on all of the students\n(3)Calculate avg on students that have passed their first exam\n(4)Print averages\nCommand: ");
    cin >> c;

    while(true) {
        if (c == '1') {
            printStudents(students, n);
        } else if (c == '2') {
            calculateAvg(students, n);
        } else if (c == '3') {
            calculateAvgSpecialStudents(students, n);
        } else if (c == '4') {
            printAverages(students, n);
        } else {
            exit(1);
        }
        printf("\n\n(1)Print students\n(2)Calculate avg on all of the students\n(3)Calculate avg on students that have passed their first exam\n(4)Print averages\nCommand: ");
        cin >> c;
    }

    delete [] students;
} 

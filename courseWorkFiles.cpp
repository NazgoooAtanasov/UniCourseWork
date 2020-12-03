#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

// Section used for output messages.
const char openingMessage[] = "Enter a file to put results in (It will be overwriten if exists.): ";
const char closingMessage[] = "Your file should be ready if everything went okey. Do you want to create a new one? (Y to continue ot any key to close the program.)";
const char fileNotFoundMessage[] = "There is no file named like that. Do you want to create it? y/n ";
const char enterFileNameMessage[] = "Enter a file to put results in: ";
const char incorrectGradeValueMessage[] = "Incorrect grade (between 2 and 6 only). Enter a new one: ";
const char enterGradesMessage[] = "Enter grades, each on a new line \n";

// Struct representing a student
struct Student
{
    char Name[50];
    char Egn[11];
    char Fnumber[7];
    int Grades[10];
    float Avg;
};

// Used to write separate lines to the output file so it is more readable.
void AddSeparatorLine(FILE *file, char type[20], char text[20]) {
    fprintf(file, "------------------ %s of %s list ------------------\n", type, text);
}

// Used for entering information about the students
void EnterStudents(char filename[20],int numberOfStudents){
    FILE *file;
    file = fopen(filename, "w+");
    for (int i = 0; i < numberOfStudents; i++)
    {
        Student student;
        

        printf("Students first name: ");
        scanf("%s", &student.Name);
        printf("Students Egn: ");
        scanf("%s", &student.Egn);
        printf("Students Fnumber: ");
        scanf("%s", &student.Fnumber);

        printf(enterGradesMessage);
        for (int f = 0; f <= 9; f++)
        {  
            printf("Grade number %d: ", f+1);
            scanf("%d", &student.Grades[f]);
            while(student.Grades[f] < 2 || student.Grades[f] > 6){
                printf(incorrectGradeValueMessage);
                scanf("%d", &student.Grades[f]);
            }            
        }

        fprintf(file, "Fnumber: %s, Name: %s, EGN: %s, Grades: { ", student.Fnumber, student.Name, student.Egn);
        for (int f = 0; f <= 9; f++)
        {
            fprintf(file, "%d ", student.Grades[f]);
        }
        fprintf(file, "}\n");
    }
    fclose(file);
}

// Appends the calculated average grades for the students.
void AppendAvgGradesForStudents(char fileName[30], int elementsCount) {
    FILE *file;

    file = fopen(fileName, "a+");

    char singleLine[100]="";
    int fileIterations = 0;
    int studentsCount = 0;
    while (!feof(file) || fileIterations <= elementsCount) {
        fgets(singleLine,100,file);
        studentsCount++;
        float avg = 0.0;
        for (int i = 0; i < 100; i++)
        {
           if (isdigit(singleLine[i])){
                avg+=atof(&singleLine[i]);
            }
        }
        
        avg/=10;
        fprintf(file, "Student: %d, Avg: %.2f\n", studentsCount, avg);
        fileIterations++;
    }

    fclose(file);
}

// Appends the calculated average grades for the students that have passed their third exam.
void AppendAvgGradesForStudentsPassedTheyThirdExam(char fileName[30], int elementsCount) {
    FILE *file;

    file = fopen(fileName, "a+");
    char singleLine[100]="";

    float avg = 0.0;
    int studentsCount = 0;
    int fileIterations = 0;
    while (!feof(file) || fileIterations<=elementsCount) {
        fgets(singleLine,100,file);
        int digitCount = 0;
        float first = 0;
        for (int i = 0; i < 100; i++)
        {
            if (isdigit(singleLine[i])){
                digitCount++;
                if(digitCount == 1) {
                    first = atof(&singleLine[i]);
                }
                float digit = atof(&singleLine[i]);
                if (digitCount == 3 && digit >=3) {
                    avg += first;
                    studentsCount++;
                    break;
                }
                if(digitCount == 3) {
                    break;
                }
            }
        }
        fileIterations++;
    }
    avg/=studentsCount;
    fprintf(file, "Average on the first class is: %.2f\n", avg);

    fclose(file);
}

// Checks if the file with the given name exists.
bool CheckIfFileExists(char filename[100]) {
    FILE *file;
    
    if(fopen(filename, "r") == NULL){
        return false;
    }
    return true;
}

void Execute() {
    char fn[20];
    char filename[100] = { '.','/' };
    printf(openingMessage);
    scanf("%s", &fn);
    strcat(filename, fn); 
    while (!CheckIfFileExists(filename)) {
        printf(fileNotFoundMessage);
        char c;
        scanf("%s", &c);
        if(c == 'y'){
            break;
        } else {
            printf(enterFileNameMessage);
            scanf("%s", &fn);
        }
    }


    int n;
    printf("How many students: ");
    scanf("%d", &n);
    EnterStudents(filename, n);
    AppendAvgGradesForStudents(filename, n);
    AppendAvgGradesForStudentsPassedTheyThirdExam(filename, n);
}

// The entry point of the program.
int main() {
    // Starts up the program.
    Execute();
    char c;
    printf(closingMessage);
    scanf("%s", &c);
    if (c == 'y' || c == 'Y') {
        Execute();
    } else {
        return 0;
    } 
}

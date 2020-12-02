#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char FirstName[50];
    char LastName[50];
    char Egn[11];
    char Fnumber[7];
    int Grades[10];
};

// Used to write separate lines to the output file so it is more readable.
void AddSeparatorLine(FILE *file, char type[20], char text[20]) {
    fprintf(file, "------------------ %s of %s list ------------------\n", type, text);
}

// Used for entering information about the students
void EnterStudents(Student arr[],int numberOfStudents){
    for (int i = 0; i < numberOfStudents; i++)
    {
        printf("Students first name: ");
        scanf("%s", &arr[i].FirstName);
        printf("Students last name: ");
        scanf("%s", &arr[i].LastName);
        printf("Students Egn: ");
        scanf("%s", &arr[i].Egn);
        printf("Students Fnumber: ");
        scanf("%s", &arr[i].Fnumber);

        printf(enterGradesMessage);
        for (int f = 0; f <= 9; f++)
        {  
            printf("Grade number %d: ", f+1);
            scanf("%d", &arr[i].Grades[f]);
            while(arr[i].Grades[f] < 2 || arr[i].Grades[f] > 6){
                printf(incorrectGradeValueMessage);
                scanf("%d", &arr[i].Grades[f]);
            }            
        }
    }
}

// Writes the students to the given file if it exists.
// If it does not exist, it gets created.
void WriteStudentsToFile(char fileName[30], Student arr[], int arraySize) {
    FILE *file;

    file = fopen(fileName, "w+");
    AddSeparatorLine(file, "Start", "students");
    for (int i = 0; i < arraySize; i++)
    {
        fprintf(file, "Fnumber %s, Name: %s %s, Egn: %s ",
            arr[i].Fnumber, arr[i].FirstName, arr[i].LastName, arr[i].Egn);
        
        fprintf(file, "grades: { ");
        for (int f = 0; f <= 9; f++)
        {
            fprintf(file, "%d, ", arr[i].Grades[f]);
        }
        fprintf(file, "} \n");
    }
    AddSeparatorLine(file, "End", "students");
    fclose(file);
}

// Appends the calculated average grades for the students.
void AppendAvgGradesForStudents(char fileName[30], Student arr[], int arraySize) {
    FILE *file;

    file = fopen(fileName, "a");
    AddSeparatorLine(file, "Start", "avg grades");
    for (int i = 0; i < arraySize; i++)
    {
        fprintf(file, "Fnomer: %s", arr[i].Fnumber);
        float avg = 0;
        for (int f = 0; f <= 9; f++)
        {
            avg+=arr[i].Grades[f];
        }
        avg/=10;
        fprintf(file, " Avg: %.2f \n", avg);
    }
    AddSeparatorLine(file, "End", "avg grades");
    fclose(file);
}

// Appends the calculated average grades for the students that have passed their third exam.
void AppendAvgGradesForStudentsPassedTheyThirdExam(char fileName[30], Student arr[], int arraySize) {
    FILE *file;

    file = fopen(fileName, "a");
    AddSeparatorLine(file, "Start", "avg grade on the first class.");
    fprintf(file, "Calculated if there are students that passed their 3rd exam.\n");
    float avg;
    int count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (arr[i].Grades[2] >= 3) {
            avg += arr[i].Grades[0];
            count++;
        }
    }
    if (count > 0) {
        avg /= count;
        fprintf(file, "Avg grade of the first class is - %.2f\n", avg);
        AddSeparatorLine(file, "End", "avg grades of first class");
    } else {
        fprintf(file, "Noone has passed their third exam.\n");
    }
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
    struct Student students[n];
    int arraySize = sizeof(students)/ sizeof(students[0]);
    EnterStudents(students, n);
    WriteStudentsToFile(filename, students, arraySize);
    AppendAvgGradesForStudents(filename, students, arraySize);
    AppendAvgGradesForStudentsPassedTheyThirdExam(filename, students, arraySize);
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

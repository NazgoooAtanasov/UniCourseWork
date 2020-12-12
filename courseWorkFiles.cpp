#include <stdio.h>
#include <string.h>

using namespace std;

struct Student
{
    char name[20];
    char egn[11];
    char fnumber[7];
    int grades[10];
    float avg;
};

Student student;
FILE *binaryFile;
char filename[30];


void createFile() {
    binaryFile = fopen(filename, "w");
    fclose(binaryFile);
}

void readStudent(Student *s){
    printf("Student's name: "); scanf("%s", &s->name);
    printf("Student's egn: "); scanf("%s", &s->egn);
    printf("Student's fnumber: "); scanf("%s", &s->fnumber);

    printf("Enter grades, each on a new line\n");

    for (int f = 0; f <= 9; f++)
    {
        printf("Grade number %d: ", f+1);
        scanf("%d", &s->grades[f]);
        while(s->grades[f] < 2 || s->grades[f] > 6){
            printf("Incorrect grade.\n");
            printf("Grade number %d: ", f+1);
            scanf("%d", &s->grades[f]);
        }       
    }
}

void writeStudentsToBinary() {
    char c;
    binaryFile = fopen(filename, "ab");
    do {
        readStudent(&student);
        fwrite(&student, sizeof(student),1,binaryFile);
        printf("Do you want to add another student? (y to continue, else for no): ");
        scanf("%s", &c);
    } while(c == 'y');
    fclose(binaryFile);
}

void calculateAvg() {
    binaryFile = fopen(filename, "r+b");

    fread(&student, sizeof(student),1,binaryFile);
    while (!feof(binaryFile)) {
        float sum = 0.0;

        for (int i = 0; i <=9; i++)
        {
            sum+=student.grades[i];
        }
        student.avg = sum / 10;

        fseek(binaryFile, -(long)sizeof(student), SEEK_CUR);
        fwrite(&student, sizeof(student), 1, binaryFile);

        fread(&student, sizeof(student),1,binaryFile);
    }

    fclose(binaryFile);
}

void calculateAvgFristSubject() { 
    float sum = 0.0;
    int counter = 0;
    binaryFile = fopen(filename, "rb");

    fread(&student, sizeof(student),1,binaryFile);
    while (!feof(binaryFile)) {
        if (student.grades[2] >= 3){
            sum+=student.grades[0];
            counter++;
        }
        fread(&student, sizeof(student),1,binaryFile);
    }
    fclose(binaryFile);

    if (counter >= 1) {
        printf("Avg for the first subject is: %.2f\n", sum/counter);
    } else {
        printf("No one has passed their 3rd exam.\n");
    }
}

void createTxtFile() {
    binaryFile = fopen(filename, "rb");
    FILE *txt;
    strcat(filename,".txt");
    txt = fopen(filename, "w");

    fread(&student, sizeof(student),1,binaryFile);
    while (!feof(binaryFile)) {
        fprintf(txt, "Name: %s, Egn: %s, Fnumer: %s, Grades: ", student.name, student.egn, student.fnumber);

        for (int i = 0; i <=9; i++)
        {
            fprintf(txt,"%d ", student.grades[i]);
        }

        fprintf(txt, ", Avg: %.2f\n", student.avg);
        fread(&student, sizeof(student),1,binaryFile);
    }

    fclose(binaryFile);
    fclose(txt);
}

int main() {

    int c;
    printf("Enter the name of the file: ");scanf("%s", &filename);
    do {
        printf("MENU:\n");
        printf("1. Create new file\n");
        printf("2. Add students\n");
        printf("3. Calculate avg\n");
        printf("4. Calculate avg on first subject\n");
        printf("5. Write students to txt file.\n");
        printf("Select an option or 0 to close the program: ");
        scanf("%d",&c);getchar();
    switch (c){
        case 1:createFile();break;
        case 2:writeStudentsToBinary();break;
        case 3:calculateAvg();break;
        case 4:calculateAvgFristSubject();break;
        case 5:createTxtFile();
    }
    }while (c!=0);
}
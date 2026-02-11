#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student {
    int sid;
    char name[30];
    float fees;
};

/* Function declarations */
void addStudent(char fileName[]);
void displayStudents(char fileName[]);
void updateStudent(char fileName[]);
void deleteStudent(char fileName[]);

int main() {
    char fileName[30];
    int choice;

    printf("Enter file name: ");
    scanf("%s", fileName);

    do {
        printf("\n------ MENU ------");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Update Student");
        printf("\n4. Delete Student");
        printf("\n0. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(fileName); break;
            case 2: displayStudents(fileName); break;
            case 3: updateStudent(fileName); break;
            case 4: deleteStudent(fileName); break;
            case 0: exit(0);
            default: printf("\nInvalid choice!");
        }
    } while(1);

    return 0;
}

void addStudent(char fileName[]) {
    FILE *fp;
    struct Student s;

    fp = fopen(fileName, "ab");
    if(fp == NULL) {
        printf("File error!");
        return;
    }

    printf("\nEnter SID: ");
    scanf("%d", &s.sid);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Fees: ");
    scanf("%f", &s.fees);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully.");
}

void displayStudents(char fileName[]) {
    FILE *fp;
    struct Student s;

    fp = fopen(fileName, "rb");
    if(fp == NULL) {
        printf("\nNo records found.");
        return;
    }

    printf("\nSID\tName\tFees\n");
    while(fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%.2f\n", s.sid, s.name, s.fees);
    }

    fclose(fp);
}
void updateStudent(char fileName[]) {
    FILE *fp;
    struct Student s;
    int sid, found = 0;

    fp = fopen(fileName, "rb+");
    if(fp == NULL) {
        printf("\nFile not found.");
        return;
    }

    printf("\nEnter SID to update: ");
    scanf("%d", &sid);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.sid == sid) {
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new fees: ");
            scanf("%f", &s.fees);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found)
        printf("\nRecord updated successfully.");
    else
        printf("\nStudent not found.");
}
void deleteStudent(char fileName[]) {
    FILE *fp, *temp;
    struct Student s;
    int sid, found = 0;

    fp = fopen(fileName, "rb");
    temp = fopen("temp.dat", "wb");

    if(fp == NULL) {
        printf("\nFile not found.");
        return;
    }

    printf("\nEnter SID to delete: ");
    scanf("%d", &sid);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.sid != sid) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(fileName);
    rename("temp.dat", fileName);

    if(found)
        printf("\nRecord deleted successfully.");
    else
        printf("\nStudent not found.");
}

#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int rno;
    char name[50];
    int std;
    int marks;
    int rank;
    int active;
};

#define SIZE 1000

struct Student srecords[SIZE];
int index = 0, rnos = 1;

void printStudent(struct Student s);

void addStudent() {
    struct Student s;

    if (index == SIZE) {
        printf("\nStudent list is full.\n");
        return;
    }

    s.rno = rnos;

    printf("\nEnter Name : ");
    scanf("%s", s.name);

    printf("Enter Std : ");
    scanf("%d", &s.std);

    printf("Enter Marks : ");
    scanf("%d", &s.marks);

    s.active = 1;

    srecords[index] = s;
    index++;
    rnos++;

    printf("\nStudent record inserted successfully.\n");
}

void deleteStudentbyId() {
    int i, rno, flag = 1;

    printf("\nEnter Rno to delete student record : ");
    scanf("%d", &rno);

    for (i = 0; i < index; i++) {
        if (srecords[i].rno == rno && srecords[i].active == 1) {
            srecords[i].active = 0;
            printf("\nStudent Rno %d deleted.\n", rno);
            flag = 0;
            break;
        }
    }

    if (flag) {
        printf("\nStudent Rno %d not found.\n", rno);
    }
}

void searchStudentById() {
    int i, rno, flag = 1;

    printf("\nEnter Rno to search student : ");
    scanf("%d", &rno);

    for (i = 0; i < index; i++) {
        if (srecords[i].rno == rno && srecords[i].active == 1) {
            printStudent(srecords[i]);
            flag = 0;
            break;
        }
    }

    if (flag) {
        printf("\nStudent Rno %d not found.\n", rno);
    }
}

void updateStudentById() {
    int i, rno, flag = 1;

    printf("\nEnter Rno to update record : ");
    scanf("%d", &rno);

    for (i = 0; i < index; i++) {
        if (srecords[i].rno == rno && srecords[i].active == 1) {

            printf("Enter Name : ");
            scanf("%s", srecords[i].name);

            printf("Enter Std : ");
            scanf("%d", &srecords[i].std);

            printf("Enter Marks : ");
            scanf("%d", &srecords[i].marks);

            printf("\nStudent Rno %d updated successfully.\n", rno);
            flag = 0;
            break;
        }
    }

    if (flag) {
        printf("\nStudent Rno %d not found.\n", rno);
    }
}

void calculateRank() {
    int i, j;

    for (i = 0; i < index; i++) {
        if (srecords[i].active == 1) {
            int rank = 1;

            for (j = 0; j < index; j++) {
                if (srecords[j].active == 1 &&
                    srecords[j].marks > srecords[i].marks) {
                    rank++;
                }
            }

            srecords[i].rank = rank;
        }
    }
}

void displayStudent() {
    int i;

    if (index == 0) {
        printf("\nStudent list is empty.\n");
        return;
    }

    calculateRank();

    printf("\nRno\tName\tStd\tMarks\tRank\n");

    for (i = 0; i < index; i++) {
        if (srecords[i].active == 1) {
            printStudent(srecords[i]);
        }
    }
}

void sortStudentByMarks() {
    struct Student temp;
    int i, j, sort;

    printf("\n1. Ascending Order");
    printf("\n2. Descending Order");
    printf("\nChoice : ");
    scanf("%d", &sort);

    for (i = 0; i < index; i++) {
        for (j = i + 1; j < index; j++) {
            if ((sort == 1 && srecords[i].marks > srecords[j].marks) ||
                (sort == 2 && srecords[i].marks < srecords[j].marks)) {
                temp = srecords[i];
                srecords[i] = srecords[j];
                srecords[j] = temp;
            }
        }
    }

    printf("\nStudents sorted by marks.\n");
    displayStudent();
}

void printStudent(struct Student s) {
    printf("%d\t%s\t%d\t%d\t%d\n",
           s.rno, s.name, s.std, s.marks, s.rank);
}

int main() {
    int choice;

    do {
        printf("\n----- Student Management System -----");
        printf("\n1. Add student");
        printf("\n2. Update student");
        printf("\n3. Delete student");
        printf("\n4. Display students");
        printf("\n5. Search student");
        printf("\n6. Sort by marks");
        printf("\n7. Exit");
        printf("\nChoice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudentById(); break;
            case 3: deleteStudentbyId(); break;
            case 4: displayStudent(); break;
            case 5: searchStudentById(); break;
            case 6: sortStudentByMarks(); break;
            case 7: printf("\nExiting application...\n"); break;
            default: printf("\nInvalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}
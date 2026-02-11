#include<stdio.h>
#include<conio.h>
struct Student {
    int rno;
    char name[20];
    int std;
    int marks;
};

struct Student scanData(struct Student s)
{
    printf("\nEnter Rno : ");
    scanf("%d" , &s.rno);
    printf("\nEnter Name : ");
    scanf("%s",&s.name);
    printf("\nEnter Std : ");
    scanf("%d" , &s.std);
    printf("\nEnter Marks : ");
    scanf("%d" , &s.marks);

    return s;
}

void disData(struct Student s)
{
    printf("\n%d \t %s \t %d \t %d" , s.rno , s.name , s.std , s.marks);
}

void main()
{
    struct Student s[3];
    int i;

    for(i=0 ; i<3 ; i++)
    {
        s[i] = scanData(s[i]);
    }

    printf("\nRno \t Name \t Std \t Marks");
    for(i=0 ; i<3 ; i++)
    {
        disData(s[i]);
    }

    getch();
}
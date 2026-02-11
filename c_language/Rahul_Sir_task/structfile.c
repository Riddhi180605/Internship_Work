#include<stdio.h>
#include<conio.h>
#define SIZE 2

struct Student{
    int sid;
    char name[30];
    float fees;
}s[SIZE];

// or  struct Student s[SIZE];

void scanStudentDetails();
void displayStudentDetails();

void main(){
    FILE *fp;
    struct Student t;
    char fileName[30];
    int i;
    // clrscr();
    printf("\nEnter the filename : ");
    scanf("%s",fileName);
    fp=fopen(fileName,"w");
    scanStudentDetails();
    for(i=0;i<SIZE;i++){
        fwrite(&s[i],sizeof(s[i]),1,fp);
    }
    fclose(fp);
    fp = fopen(fileName,"r");
    for(i=0;i<SIZE;i++){
        fread(&t,sizeof(t),1,fp);
        displayStudentDetails(t);
    }
    fclose(fp);
    getch();
}

void scanStudentDetails(){
    int i;
    float temp;
    for(i=0;i<SIZE;i++){
        printf("\nEnter the value of sid :");
        scanf("%d",&s[i].sid);
        printf("\nEnter the student name :");
        scanf("%s",s[i].name);
        printf("\nEnter the fees :");
        scanf("%f",&temp);
        s[i].fees = temp;
    }
}

void displayStudentDetails(struct Student t){
    int i;
    printf("\nsid\tname\tfees");
    printf("\n%d\t%s\t%.2f",t.sid,t.name,t.fees);
}
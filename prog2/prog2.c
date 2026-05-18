#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student {
    int id;
    char name[20];
} Student;

void input(Student s[], int n);
void writeTofile(Student s[],int n);
void createSeekArray(long pos[], int n);
void display(long pos[], int studentnumber);

int main(){
    int n,choice;
    printf("Enter the number of students: ");
    scanf("%d",&n);

    if(n<=0){
        printf("invalid value");
    }

    Student s[n];
    long pos[n];

    input(s,n);
    writeTofile(s,n);
   createSeekArray(pos,n);
    
    printf("enter the choice of record:");
    scanf("%d",&choice);

    display(pos, choice-1);
    return 0;
 
}
void input(Student s[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\nEnter ID: ");
        scanf("%d", &s[i].id);

        printf("Enter Name: ");
        scanf("%s", s[i].name);
    }
};
void writeTofile(Student s[],int n){
    FILE *fp=fopen("student.txt","w");
    if(fp==NULL){
        printf("invalid");
    }
    for(int i=0;i<n;i++){
        fprintf(fp,"%d %s\n",s[i].id,s[i].name);
    }
    fclose(fp);
}
void createSeekArray(long pos[], int n)
{
    FILE *fp;

    fp = fopen("student.txt", "r");

    if(fp == NULL)
    {
        printf("Cannot open file.");
        return;
    }

    char line[100];

    for(int i = 0; i < n; i++)
    {
        pos[i] = ftell(fp);

        fgets(line, sizeof(line), fp);
    }

    fclose(fp);
}
void display(long pos[], int recordNumber)
{
    FILE *fp;

    fp = fopen("student.txt", "r");

    if(fp == NULL)
    {
        printf("Cannot open file.");
        return;
    }

    char line[100];

   
    fseek(fp, pos[recordNumber], SEEK_SET);

    
    fgets(line, sizeof(line), fp);

    printf("\nRecord:\n");
    printf("%s", line);

    fclose(fp);
}


#include<stdio.h>
#include<sqlite3.h>
int printRecords(void *ptr,int columnSize,char **dataPtr,char **coloumnPtr)
{
int i;
printf("%s\n",(char *)ptr);
for(i=0;i<columnSize;i++)
{
printf("%s---->%s\n",coloumnPtr[i],dataPtr[i]);
}
printf("-------------------------------------------\n");
return 0;
}
int main()
{
int resultCode,tableExist;
sqlite3 *db;
char *errorMessage;
resultCode=sqlite3_open("employee.db",&db);
char title[500]="Employee Title";
if(resultCode!=SQLITE_OK)
{
printf("Unable to establish the data\n");
return 0;
}
resultCode=sqlite3_exec(db,"select * from employee;",printRecords,&title,&errorMessage);
printf("Result code: %d\n",resultCode);
if(resultCode==0)
{
printf("table now created\n");
}
else
{
printf("table already presents\n");
}
sqlite3_close(db);
return 0;
}
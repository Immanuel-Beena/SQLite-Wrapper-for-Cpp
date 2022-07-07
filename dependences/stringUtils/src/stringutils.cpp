#include<stringutils>
#include<iostream>
using namespace std;
string stringutils::trimmed(const string &str)
{
int len=str.length();
if(len==0) return string("");
int i,j;
for(i=0;str[i]==' ' && i<len;i++);
if(i==len) return string("");
for(j=len-1;str[j]==' ';j++);
char *c;
c=new char[j-i+1+1];
int k=0;
while(i<=j)
{
c[k]=str[i];
k++;
i++;
}
c[k]='\0';
string s(c);
delete [] c;
return s;
}
int stringutils::compareStringIgnoreCase(const char *a,const char *b)
{
if(a==b) return 0;
if(a==NULL) return -1;
if(b==NULL) return 1;
char c,d;
for(;*a!='\0' && *b!='\0'; a++,b++)
{
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
if(c!=d) return c-d;
}
if(*a==*b) return 0;
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
return c-d;
}
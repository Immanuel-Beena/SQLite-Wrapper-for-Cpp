#include<sqlite>
#include<iostream>
#include<queue>
#include<forward_list>
using namespace std;
using namespace sqlite;
int main()
{
SqliteDB sqliteDB;
queue<forward_list<string *> *> *data;
forward_list<string *> *list;
string *str;
try
{
sqliteDB.open("some.db");
data=sqliteDB.selectRows("select * from raju");
while(!data->empty())
{
list=data->front();
while(!list->empty())
{
str=list->front();
cout<<(*str)<<endl;
delete str;
list->pop_front();
}
data->pop();
}
cout<<"SQL statement succefully fire"<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
return 0;
}
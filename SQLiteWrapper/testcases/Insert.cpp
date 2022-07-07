#include<sqlite>
#include<iostream>
using namespace std;
using namespace sqlite;
int main()
{
SqliteDB sqliteDB;
try
{
sqliteDB.open("some.db");
sqliteDB.executeInsert("insert into students values(101,'sam','M');");
cout<<"SQL statement succefully fire"<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
return 0;
}
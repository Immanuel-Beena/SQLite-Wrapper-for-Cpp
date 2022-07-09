#include<sqlite>
#include<iostream>
using namespace std;
using namespace sqlite;
int main()
{
int allotedNumber;
SqliteDB sqliteDB;
try
{
sqliteDB.open("some.db");
sqliteDB.executeInsert("insert into pet (name) values('Rockey');",&allotedNumber);
cout<<"allocted Number: "<<allotedNumber<<endl;
cout<<"SQL statement succefully fire"<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
return 0;
}
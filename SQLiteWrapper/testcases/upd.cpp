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
sqliteDB.executeUpdate("update students set name='Beena' , gender='F' where roll_number=103;");
cout<<"SQL statement succefully fire"<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
return 0;
}
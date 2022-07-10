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
string sql="select * from students;";
/*
Here is Example where main() function programmer calls two times a select
Method but Assgin the dataStructure to Rows object Only One Time.So I 
also Handeled this situation.
*/
Rows rows=sqliteDB.selectRows(sql);
Row row;
int rollNumber;
string name;
string gender;
while(rows.hasMoreRows())
{
row=rows.getRow();
rollNumber=row.getInt("roll_number");
name=row.getString("name");
gender=row.getString("gender");
cout<<rollNumber<<","<<name<<","<<gender<<endl;
}
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}
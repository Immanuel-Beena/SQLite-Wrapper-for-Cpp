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
sqliteDB.selectRows(sql);
/* may be main() function programmer not read docs on 
    github and expecting this method will print its table content I also
    handed this situation because dataStructure is prepared so this is 
    my responsiblity to release memory...
*/
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}
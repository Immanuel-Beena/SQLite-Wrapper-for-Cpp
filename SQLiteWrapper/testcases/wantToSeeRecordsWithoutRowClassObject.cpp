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
Rows rows=sqliteDB.selectRows(sql);
/* may be main() function programmer not read docs on 
    github and expecting there is no memory leak issues 
    so I handed this situation. You run and see the out our Queue Sturctue
    is ready but because no use of Row class we handel this memory leak 
    on Rows class destructor...
*/
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}
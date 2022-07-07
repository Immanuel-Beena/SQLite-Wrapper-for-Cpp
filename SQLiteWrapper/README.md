# SQLite Wrapper for C++
## DOCUMENTATION

## Overview
here you get to know about `SQLite Wrapper for c++`, which is built in `c++` programming language.

## Why The SQLite Wrapper For C++ ?
I made project for learning `layered arhitecture` but In data_layer I use Sqlite3 during the Implementation I realise the error handling for each SQL Statement is Difficult So I decided to Make Library and create Wrapper for C++ so Whenver I or anybody who wants to use sqlite3 in c++ so this library or wrapper help a lot...

## Dependencies
* [String utils](#string-utils)
* [Sqlite3](#sqlite3-library)



## SQlite Wrapper Class Methods
* [Common things](#common-things)
* [Error-Handling](#error-handling)
* [How to open database](#how-to-open-database)
* [How to insert data](#how-to-insert-data)
* [How to update data](#how-to-update-data)


   
### Common things
1 Every Time you should include `sqlite` header.
Ex:
`#include<sqlite>`

2 Always create `SQLiteDB Object`
Ex:
`SqliteDB sqliteDB;`

### Error handling
Error handling is reason which makes me to push to create this wrapper.
You don't need to take any pointer.Whenver Your SQL statement not excecuted or you passsed wrong SQL statement it will automatically genrated the Exception and cause
for checking causing call `SQLiteException.what()` it will give you the cause why your execution of sql statement Failed.
I design `SQLiteExcpetion` and intergated inside.  ** _AlWAYS USE TRY CATCH BLOCK TO PREVENT APPLICATION CRASH_ **
Ex:

```
try
{
// call methods of SQLiteDB Objects.
}catch(SQLiteException &sqliteException)
{
// this will you the cause why your execution failed.
cout<<sqliteException.what()<<end; 
}
```



### How to open database
To opening the database use `open(FILE_NAME)` or just use parameterized constructor
Ex:
```c
SqliteDB sqliteDB;
sqliteDB.open(FILE_NAME);
```


### How to insert data
to Inserting data into table call `executeInsert(SQL_STATEMENT)`

Code-
```c
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
```

### How to update data
Special Note:
`executeUpdate` method always overwrite data means if your `where=value` correct then data should always overwrite we can 't do anything because `sqlite3_exec()`.
But If your `where=value` is incorrect means record not exist then you see the exception and call `what()` to check cause.
Ex:
```c
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
```

#include<sqlite>
#include<sqlite3.h>
#include<iostream>
#include<stringutils>
using namespace std;
using namespace sqlite;
using namespace stringutils;
Rows::Rows() throw (SQLiteException)
{
this->dataRows=NULL;
}
Rows::Rows(queue<forward_list<string *> *> *dataRows) throw (SQLiteException)
{
this->dataRows=dataRows;
}
Rows::Rows(const Rows &other) throw (SQLiteException)
{
this->dataRows=other.dataRows;
}
Rows & Rows::operator=(queue<forward_list<string *> *> *dataRows) throw (SQLiteException)
{
this->dataRows=dataRows;
return *this;
}
Rows::~Rows() throw (SQLiteException)
{
// code to free the allocated memeory;
}
int Rows::hasMoreRows() throw (SQLiteException)
{
return !(this->dataRows->empty());
}
forward_list<string *> * Rows::getRow() throw (SQLiteException)
{
forward_list<string *> *row;
if(this->dataRows->empty()) return NULL;
row=this->dataRows->front();
this->dataRows->pop();
return row;
}
int fetchingData(void *ptr,int columnSize,char **dataPtr,char **columnPtr)
{
int e;
string *str;
std::queue<std::forward_list<string *> *> *vQueue;
vQueue=(std::queue<forward_list<string *> *> *)ptr;
std::forward_list<string *> *list;
list=new std::forward_list<string *>;
if(list==NULL)
{
// first clear  queue , inside forward list data and forwardlist..
throw SQLiteException("fetching data is faild because not enough memory");
}
forward_list<string *>::iterator i;
i=list->before_begin();
for(e=0;e<columnSize;e++)
{
str=new string(dataPtr[e]);
if(str==NULL)
{
// first clear  queue , inside forward list data and forwardlist..
throw SQLiteException("fetching data is faild because not enough memory");
}
i=list->insert_after(i,str);
}
vQueue->push(list);
return 0;
}
SqliteDB::SqliteDB() throw (SQLiteException)
{
this->db=NULL;
this->FILE_NAME="";
}
SqliteDB::SqliteDB(const SqliteDB &other) throw (SQLiteException)
{
int resultCode;
string error;
if(other.db==NULL)
{
this->db=NULL;
this->FILE_NAME="";
return;
}
resultCode=sqlite3_open(other.FILE_NAME.c_str(),&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
throw SQLiteException(string("unable to connect,reason: ")+error);
}
this->FILE_NAME=other.FILE_NAME;
}
SqliteDB::SqliteDB(const char *fileName) throw (SQLiteException)
{
int resultCode;
string error;
resultCode=sqlite3_open(fileName,&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
throw SQLiteException("unable to connect,reason: "+error);
}
this->FILE_NAME=fileName;
}
SqliteDB::SqliteDB(string &fileName) throw (SQLiteException)
{
int resultCode;
string error;
resultCode=sqlite3_open(fileName.c_str(),&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
throw SQLiteException("unable to connect,reason: "+error);
}
this->FILE_NAME=fileName;
}
SqliteDB::~SqliteDB() throw(SQLiteException)
{
if(this->db!=NULL)
{
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
}
}
void SqliteDB::executeInsert(const char *sql) throw(SQLiteException)
{
string error;
char *errorMessage;
int resultCode,sqlLength;
string vsql=trimmed(string(sql));
sqlLength=vsql.length();
if(sqlLength==0 || sqlLength <= 11) throw SQLiteException("Invalid SQL Statement");
if(this->db==NULL) throw SQLiteException("Unable to insert because no connection to database");
resultCode=sqlite3_exec(this->db,vsql.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException(string("unable to insert, reason: ")+error);
}
}
void SqliteDB::executeInsert(const string &sql) throw(SQLiteException)
{
string error;
char *errorMessage;
int resultCode,sqlLength;
string vsql=trimmed(sql);
sqlLength=vsql.length();
if(sqlLength==0 || sqlLength <= 11) throw SQLiteException("Invalid SQL Statement");
if(this->db==NULL) throw SQLiteException("Unable to insert because no connection to database");
resultCode=sqlite3_exec(this->db,vsql.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException(string("unable to insert, reason: ")+error);
}
}
void SqliteDB::close() throw (SQLiteException)
{
if(this->db!=NULL)
{
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
}
}
void SqliteDB::open(const char *fileName) throw (SQLiteException)
{
string error;
int resultCode;
if(this->db!=NULL) this->close();
resultCode=sqlite3_open(fileName,&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
this->db=NULL;
this->FILE_NAME="";
throw SQLiteException(string("unable to connect with database, reason: ")+error);
}
}
queue<forward_list<string *> *> * SqliteDB::selectRows(const char *sql) throw (SQLiteException)
{
string error;
char *errorMessage;
int resultCode,sqlLength;
string vsql=trimmed(string(sql));
sqlLength=vsql.length();
if(sqlLength==0 || sqlLength <= 13) throw SQLiteException("Invalid SQL Statement");
if(this->db==NULL) throw SQLiteException("Unable to fetch data because no connection to database");
queue<forward_list<string *> *> *fetchedData;
fetchedData=new queue<forward_list<string *> *>;
if(fetchedData==NULL) throw SQLiteException("not enough amount of memory for internal use");
resultCode=sqlite3_exec(this->db,vsql.c_str(),fetchingData,fetchedData,&errorMessage);
if(resultCode!=SQLITE_OK)
{
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException("unable to fetch data");
}
return fetchedData;
}
queue<forward_list<string *> *> * SqliteDB::selectRows(const string &sql) throw (SQLiteException)
{
string error;
char *errorMessage;
int resultCode,sqlLength;
string vsql=trimmed(sql);
sqlLength=vsql.length();
if(sqlLength==0 || sqlLength <= 13) throw SQLiteException("Invalid SQL Statement");
if(this->db==NULL) throw SQLiteException("Unable to fetch data because no connection to database");
queue<forward_list<string *> *> *fetchedData;
fetchedData=new queue<forward_list<string *> *>;
if(fetchedData==NULL) throw SQLiteException("not enough amount of memory for internal use");
resultCode=sqlite3_exec(this->db,vsql.c_str(),fetchingData,fetchedData,&errorMessage);
if(resultCode!=SQLITE_OK)
{
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException("unable to fetch data");
}
return fetchedData;
}

#include<sqlite>
#include<sqlite3.h>
#include<iostream>
#include<stringutils>
using namespace std;
using namespace sqlite;
using namespace stringutils;
int DMACount=0;
bool StringComparator::operator()(string *left,string *right)
{
return compareStringIgnoreCase((*left).c_str(),(*right).c_str())<0;
}
Row::Row() throw (SQLiteException)
{
// do nothing
}
Row::~Row() throw (SQLiteException)
{
if(!this->row.empty())
{
string *str1;
string *str2;
map<string *,string *,StringComparator>::iterator i;
for(i=this->row.begin();i!=this->row.end();++i)
{
str1=i->first;
str2=i->second;
// I free memory of inside the forward_list string *
cout<<"releasing Memory of str 1 and str 2"<<endl;
DMACount--;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
DMACount--;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
delete str1;
delete str2;
}
this->row.clear(); // all nodes of tree is released
}
}
Row & Row::operator=(forward_list<string *> *row) throw (SQLiteException)
{
string *str1;
string *str2;
if(!this->row.empty())
{
map<string *,string *,StringComparator>::iterator i;
for(i=this->row.begin();i!=this->row.end();++i)
{
str1=i->first;
str2=i->second;
// I free memory of inside the forward_list string *
cout<<"releasing Memory of str 1 and str 2"<<endl;
DMACount--;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
DMACount--;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
delete str1;
delete str2;
}
this->row.clear(); // all nodes of tree is released
// resource of forward_list and Queue is handle by Rows destructor.
}
while(!row->empty())
{
str1=row->front();
row->pop_front();
str2=row->front();
row->pop_front();
this->row.insert(pair<string *,string *>(str1,str2));
}
delete row;
cout<<"releasing memory of particular row and its data on map"<<endl;
DMACount--;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
return *this;
}
int Row::getInt(const char *column) throw (SQLiteException)
{
string col(column);
string *data;
int n;
map<string *,string *,StringComparator>::iterator i;
i=this->row.find(&col);
if(i==this->row.end()) return -1;
data=i->second;
n=atoi(data->c_str());
return n;
}
string Row::getString(const char *column) throw (SQLiteException)
{
string col(column);
map<string *,string *,StringComparator>::iterator i;
i=this->row.find(&col);
if(i==this->row.end()) return string("");
string data=*(i->second);
return data;
}
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
if(this->dataRows!=NULL)
{
/*
Assumed main() function programmer cannot calls getRow
means our queue have data so we need to first relase resourse
*/
forward_list<string *> *row;
string *str1;
string *str2;
while(!this->dataRows->empty())
{
row=this->dataRows->front();
this->dataRows->pop();
while(!row->empty())
{
str1=row->front();
row->pop_front();
str2=row->front();
row->pop_front();
delete str1;
delete str2;
}
delete row;
DMACount--;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
}
DMACount--;
cout<<"Releasing Resource of our Queue Data Struture"<<endl;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
delete this->dataRows;
}
}
int Rows::hasMoreRows() throw (SQLiteException)
{
return !(this->dataRows->empty());
}
forward_list<string *> * Rows::getRow() throw (SQLiteException)
{
forward_list<string *> *row;
if(this->dataRows->empty() || this->dataRows==NULL) return NULL;
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
DMACount++;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
forward_list<string *>::iterator i;
i=list->before_begin();
for(e=0;e<columnSize;e++)
{
str=new string(columnPtr[e]);
if(str==NULL)
{
// first clear  queue , inside forward list data and forwardlist..
throw SQLiteException("fetching data is faild because not enough memory");
}
DMACount++;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
i=list->insert_after(i,str);
str=new string(dataPtr[e]);
if(str==NULL)
{
// first clear  queue , inside forward list data and forwardlist..
throw SQLiteException("fetching data is faild because not enough memory");
}
DMACount++;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
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
delete fetchedData;
fetchedData=NULL;
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
cout<<"Before starting allocation on heap count is: "<<DMACount<<endl;
fetchedData=new queue<forward_list<string *> *>;
if(fetchedData==NULL) throw SQLiteException("not enough amount of memory for internal use");
DMACount++;
cout<<"Current DMA On heap is: "<<DMACount<<endl;
resultCode=sqlite3_exec(this->db,vsql.c_str(),fetchingData,fetchedData,&errorMessage);
if(resultCode!=SQLITE_OK)
{
delete fetchedData;
fetchedData=NULL;
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException("unable to fetch data");
}
return fetchedData;
}

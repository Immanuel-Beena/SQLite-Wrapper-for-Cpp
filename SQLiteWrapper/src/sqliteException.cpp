#include<sqliteException>
SQLiteException::SQLiteException()
{
this->message="";
}
SQLiteException::SQLiteException(const SQLiteException &other)
{
this->message=other.message;
}
SQLiteException & SQLiteException::operator=(const SQLiteException &other)
{
this->message=other.message;
return *this;
}
SQLiteException::~SQLiteException() throw()
{
// do nothing;
}
SQLiteException::SQLiteException(const string &message)
{
this->message=message;
}
SQLiteException::SQLiteException(const char *message)
{
this->message=message;
}
const char * SQLiteException::what() const throw()
{
return this->message.c_str();
}

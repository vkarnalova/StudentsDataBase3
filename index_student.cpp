#include "index_student.h"

istream& operator>>(istream& is, IndexStudent& index)
{
	is >> index.index_fac_num_ >> index.line_;
	return is;
}

ostream& operator<<(ostream& os, IndexStudent& index)
{
	os << index.index_fac_num_ << " " <<index.line_ << endl;
	return os;
}

IndexStudent::IndexStudent(const unsigned long long int fac_num,int line)
{
	index_fac_num_ = fac_num;
	line_ = line;
}

unsigned long long int IndexStudent::GetIndexFacNum()
{
	return index_fac_num_;
}

int IndexStudent::GetLine()
{
	return line_;
}

bool IndexStudent::operator<=(IndexStudent const & index)
{
	return index_fac_num_ <= index.index_fac_num_;
}

#ifndef HOMEWORK3_HOMEWORK3_INDEX_STUDENT_H_
#define HOMEWORK3_HOMEWORK3_INDEX_STUDENT_H_
#include <iostream>
#include <fstream>

using namespace std;

class IndexStudent {
private:
	unsigned long long int index_fac_num_;
	int line_;
public:
	//constructor
	IndexStudent(const unsigned long long int=0,int=0);

	//getters for indexStudent's data
	unsigned long long int GetIndexFacNum();
	int GetLine();

	//overloaded operators
	friend istream& operator>>(istream&, IndexStudent&);
	friend ostream& operator<<(ostream&, IndexStudent&);
	bool operator<=(IndexStudent const &);
};


#endif
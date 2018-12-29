#ifndef HOMEWORK3_HOMEWORK3_FUNCTIONS_H_
#define HOMEWORK3_HOMEWORK3_FUNCTIONS_H_
#include <iostream>
#include <fstream>
#include <vector>
#include "student.h"
#include "index_student.h"

using namespace std;

//function that finds student with a given faculty number
void SequentialSearch() {
	fstream file;
	file.open("StudentsGrades.db", ios::in);
	if (!file) {
		cerr << "File couldn't be opened! \n";
	}
	unsigned long long int fac_num;
	cin >> fac_num;
	Student temp_student;
	file.seekg(0, ios::beg);
	while (file >> temp_student) {
		if (temp_student.GetFacNum() == fac_num) {
			cout << temp_student;
			break;
		}
	}
	if (temp_student.GetFacNum() != fac_num) {
		cout << "Record not found! \n";
	}
	file.close();
}

//swap function for two IndexStudent objects
void SwapIndexes(IndexStudent& index_one, IndexStudent& index_two) {
	IndexStudent temp = index_one;
	index_one = index_two;
	index_two = temp;
}

//function that places all smaller elements to left of the pivot and all greater elements to right of the pivot
//it is used in the quicksort function
int Partition(vector<IndexStudent>& index_vector, int low, int high) {
	IndexStudent pivot = index_vector[high];
	int smaller = low;
	for (int j = low; j < high; j++) {
		if (index_vector[j] <= pivot) {
			SwapIndexes(index_vector[smaller], index_vector[j]);
			smaller++;
		}
	}
	SwapIndexes(index_vector[smaller], index_vector[high]);
	return smaller;
}

//function that sorts a vector with indexes
void QuickSort(vector<IndexStudent>& index_vector,int low,int high) {
	if (low < high) {
		int partitioning_index = Partition(index_vector, low, high);
		QuickSort(index_vector, low, partitioning_index - 1);
		QuickSort(index_vector, partitioning_index + 1, high);
	}
}

//function that builds the file with indexes
void BuildIndex() {
	ifstream iFile("StudentsGrades.db", ios::in);
	if (!iFile) {
		cerr << "File couldn't be opened! \n";
		exit(1);
	}
	streampos current_pos = iFile.tellg();
	vector<IndexStudent> index_vector;
	Student temp_student;
	while (iFile >> temp_student) {
		IndexStudent temp_index(temp_student.GetFacNum(), (int)current_pos);
		index_vector.push_back(temp_index);
		iFile.ignore();
		current_pos = iFile.tellg();
	}
	iFile.close();

	QuickSort(index_vector,0,index_vector.size()-1);

	ofstream oFile("FacultyNumber.ids", ios::out | ios::binary);
	if (!oFile) {
		cerr << "File couldn't be opened! \n";
		exit(1);
	}
	int number_indexes = index_vector.size();
	oFile.seekp(0, ios::beg);
	oFile.write((char*)&number_indexes,sizeof(int));
	for (int i = 0; i < number_indexes; i++) {
		oFile.seekp(i * sizeof(IndexStudent)+sizeof(int), ios::beg);
		oFile.write((char*)&index_vector[i], sizeof(IndexStudent));
	}
	oFile.close();
	cout << "Index is built! \n";
}

//function that searches the file with indexes 
//if it finds the faculty number it returns IndexStudent line_;
int BinarySearch(int start, int end, unsigned long long int find_fac_num) {
	if (start <= end) {
		ifstream file("FacultyNumber.ids", ios::binary | ios::in);
		if (!file) {
			cout << "File couldn't be opened! \n";
			return -1;
		}
		int middle = start + (end - start) / 2;
		IndexStudent temp_index;
		file.seekg(middle * sizeof(IndexStudent) + sizeof(int), ios::beg);
		file.read((char*)&temp_index, sizeof(IndexStudent));
		if (temp_index.GetIndexFacNum() == find_fac_num) {
			return temp_index.GetLine();
		}
		if (temp_index.GetIndexFacNum() > find_fac_num) {
			return BinarySearch(start, middle - 1, find_fac_num);
		}
		return BinarySearch(middle + 1, end, find_fac_num);
	}
	return -1;
}

//function that finds a student using a file with indexes
void Search() {
	unsigned long long int find_fac_num;
	cin >> find_fac_num;
	fstream file("FacultyNumber.ids", ios::binary|ios::in);
	if (!file) {
		file.close();
		BuildIndex();
		file.open("FacultyNumber.ids", ios::binary | ios::in);
	}
	int number_indexes;
	file.seekg(0, ios::beg);
	file.read((char*)&number_indexes, sizeof(int));
	file.close();

	int result = BinarySearch(0, number_indexes, find_fac_num);

	if (result != -1) {
		ifstream ifile("StudentsGrades.db", ios::in);
		ifile.seekg(result, ios::beg);
		Student temp_student;
		ifile >> temp_student;
		cout << temp_student;
		ifile.close();
	}
	else {
		cout << "Record not found! \n";
	}
}
#endif


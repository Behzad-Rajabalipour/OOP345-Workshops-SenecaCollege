#include <iostream>
#include <sstream>
#include "fstream"
#include <string>
#include <vector>

using namespace std;

class Test {
	string code = "";
	string name = "";
	
	
public:
	Test() {};
	Test(string code_, string name_) {
		code = code_;
		name = name_;	
	}

	void load(string code_, string name_) {
		code = code_;
		name = name_;
	}

	void print() {
		cout << code << "\t" << name << endl;
	}
	operator int() {
		return "behzad";
	}
};


ostream& operator<<(ostream& os, Test& obj) {
	os << "2";
	return os;
}

int main() {
	
	/*
	fstream fread("airport_data.csv");
	string line;
	int i = 0;
	vector <Test> tests;							
	while (getline(fread, line)) {
		istringstream iss(line);
		vector <string> arr_str;
		string temp;
		while (getline(iss,temp, ',')) {
			arr_str.push_back(temp);
		}
	
		// for (size_t i = 0; i < arr_str.size(); i++) {};
		tests.emplace_back(arr_str[0], arr_str[1]);
		// tests[i].load(arr_str[0], arr_str[1]);
		tests[i].print();
		i++;
	}
	*/

	string x;
	if (x.empty())
		cout << "x";

	return 0;
}
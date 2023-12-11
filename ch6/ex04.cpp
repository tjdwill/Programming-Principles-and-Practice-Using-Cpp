// tjdwill
// PPP Exercise 6.4
// 11 December 2023
// Task: Solve 4.19 using a class.

/*
	Well, I haven't done 4.19, so that's what I get for skipping. In any case,
	it doesn't seem too bad.
*/
#include "../std_lib_facilities.h"

//-----------------------------------------------------------------------------
class Name_value
{
	public:
		string name;
		int value;
		Name_value(string nm, int val);	
};

Name_value::Name_value(string nm, int val)
{
	name = nm;
	value = val;
}
//-----------------------------------------------------------------------------
bool are_identical(Name_value nv1, Name_value nv2){
	// test if two NV pairs are identical
	const string name1 {nv1.name};
	const int val1 {nv1.value};
	const string name2 {nv2.name};
	const int val2 {nv2.value};

	if (name1 == name2 && val1 == val2)
		return true;
	else
		return false;
}
//-----------------------------------------------------------------------------

int main()
try{

	cout << "Insert names and values ('NoName 0' to terminate):\n\n";

	const Name_value terminating_NV	{"NoName", 0};
	vector<Name_value> nvs {};
	string next_name;
	int next_value;

	while (cin){
		cin >> next_name >> next_value;
		for (Name_value nv: nvs){
			string nm {nv.name};
			if (next_name == nm)
				error("Cannot have duplicate names.\n");
		}
		Name_value next_nv = Name_value(next_name, next_value);
		if (are_identical(next_nv, terminating_NV))
			break;
		else
			nvs.push_back(next_nv);
	}

	cout << "\nName-Value pairs:\n";
	for (Name_value nv: nvs){
		cout 
			<< "Name: " << nv.name
			<< "\tValue: " << nv.value
			<< '\n';
	}
}
catch(exception& e){
	cout << "Error: " << e.what() << '\n';
	return 1;
}
catch(...){
	cout << "Unexpected Error.\n";
	return 2;
}
//-----------------------------------------------------------------------------
/*
	Test(s)
	------

	Insert names and values ('NoName 0' to terminate):

	Joe 17
	Barbara 22
	Stephen 35
	NoName 0

	Name-Value pairs:
	Name: Joe	Value: 17
	Name: Barbara	Value: 22
	Name: Stephen	Value: 35
	---

	Insert names and values ('NoName 0' to terminate):

	Joseph 24
	Youssef 40
	Brossef 35
	Joseph 21
	Error: Cannot have duplicate names.

*/
//------------------------------------------------------------------------------

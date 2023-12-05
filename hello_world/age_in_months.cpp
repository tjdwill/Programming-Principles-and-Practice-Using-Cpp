#include "../std_lib_facilities.h"

int main(){
	string name;
	double age;

	cout << "Please pass your name and age: ";
	cin >> name >> age;
	cout << "Hi, " << name  << "! You are " << age * 12 << " months old!\n";
}

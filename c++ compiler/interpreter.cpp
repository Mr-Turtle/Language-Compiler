#include <iostream>
#include <fstream>
using namespace std;

int interpret(string fn){
	fstream file;
	file.open(fn, ios::in);
	
	if(!file){
		cout << "No such file.";
		return 1;
	}
	
	string line;
	while(getline(file, line)){
		cout << line << "\n";
	}
	
	return 0;
}

int main(){
	cout << "Filename (+.turtleC): ";
	
	string filename;
	cin >> filename;
	
	cout << "Interpreting file...\n";
	interpret(filename + ".turtleC");
}
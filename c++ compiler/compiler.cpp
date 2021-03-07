#include <iostream>
#include <fstream>
#include <direct.h>
using namespace std;

string replace(string target, string find, string replace){
	
	size_t index = 0;
	while (true) {
		 index = target.find(find, index);
		 if (index == string::npos) break;
		 target.replace(index, find.length(), replace);
		 index += find.length();
	}
	
	return target;
}

int compile(const string& target, const string& output, const string& interpreter){
	
	string target_contents = "";
	// Reading target file
	fstream target_file;
	target_file.open(target, ios::in);
	if(!target_file){
		cout << "Target file does not exist.";
		return 1;
	}
	string line;
	while(getline(target_file, line)){
		target_contents += line + "~";
	}
	// Target file read
	
	string interpreter_contents = "";
	// Reading interpreter file
	fstream interpreter_file;
	interpreter_file.open(interpreter, ios::in);
	if(!interpreter_file){
		cout << "Interpreter file does not exist.";
		return 1;
	}
	line = "";
	while(getline(interpreter_file, line)){
		interpreter_contents += line + "\n";
	}
	// Interpreter file read
	
	//boost::replace_all(interpreter_contents, "{FILENAME}", output);
	string end_file_contents = replace(interpreter_contents, "{FILENAME};", "\""+target+"\";");
	end_file_contents = replace(end_file_contents, "{FILE};", "\""+target_contents+"\";");
	
	// Write file contents to output file
	_mkdir("output");
	fstream out_file;
	out_file.open("output/"+output, ios::out);
	out_file << end_file_contents;
	out_file.close();
	
	// We now have a C++ file that contains the interpreter & program
	
	// Convert that C++ file into a Executable
	string command = "g++ output/"+output+" -o output/"+replace(output, ".cpp", ".exe");
	const char * c = command.c_str();
	system(c);
	
	// Delete the old c++ file
	string cpp_path = "output"+output;
	c = cpp_path.c_str();
	remove(c);
}

int main(){
	string target, output;
	cout << "Target (+.turtleC): ";
	cin >> target;
	cout << "\nOutput (+.exe): ";
	cin >> output;
	
	compile(target+".turtleC", output+".cpp", "base/modified_interpreter.mi");
}
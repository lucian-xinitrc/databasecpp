#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>

using namespace std;

ifstream fxp;
ofstream exp;

string databasename;

class commandSystem {
public:
	string database, path = "storage/", extension = ".list";
	void command(const vector<string>& command) {
		string word;
		int k = 0;
		for(string item : command) {
			stringstream scin(item);
			while(scin >> word) {
				if(word == "CREATE") { createCommand(item); }
				if(word == "INSERT") { insertCommand(item); }
				if(word == "SET") { setDatabase(item); }
			}
			k = 0;
			cout << endl;
		}
	}
	void createCommand(string command) {
		stringstream ss(command);
		string item;
		string db, tb;
		int d = 0, t = 0, tf = 0;
		while(ss >> item) {
			if(d > 0) {
				db = "DB" + item;
				databasename = path + item + extension;
				exp.open(databasename);
				exp << db;
				cout << "Database created: " << item ;
				exp.close();
			} else {
				if(t > 0) {
					tb = "TB" + item;
					vector<string> lines;
					string line;
					fxp.open(databasename);
					
					while(fxp >> line) {
						lines.push_back(line);
					}
					lines.push_back(tb);
					exp.open(databasename);
					for(string lined : lines) {
						exp << lined << endl;
					}
					cout << "Insert successfully";
				}
			}
			if(item == "DATABASE") {
				d++;
			} else {
				if(item == "TABLE")
					t++;
			}
		}
		if(!d && !t) {
			cout << "Invalid CREATE command inserted";
		}
	}
	void setDatabase(string command) {
		stringstream ss(command);
		string item;
		while(ss >> item) {
			if(item != "SET") {
				database = item;
				databasename = path + item + extension;
				cout << item << " Database Opened";		
			}
		}
	}
	void insertCommand(string command) {
		stringstream ss(command);
		vector<string> values, cols;
		string item, table;
		int s1 = 0, s2 = 0, s3 = 0;
		while(ss >> item){
			if(s3 > 0) {
				stringstream sd(item);
				string col;
				while(sd >> col) { cols.push_back(col); }
				s3 = 0;
			}

			if(s2 > 0) { table = item; s2 = 0; s3++; }
			if(s1 > 0) {
				stringstream inst(item);
				string value;
				while(inst >> value) { values.push_back(value); }
				s1 = 0;
			}

			if(item == "INSERT") { s1++; }
			if(item == "INTO") { s2++; }
		}
	}
	void selectCommand(const vector<string>& command) {

	}
};

int prog(int h) {
	if(h == 0) {
		commandSystem comm;
		ifstream read ("storage/commands.list");

		string init;
		vector<string> command;
		cout << "ourdatabase prompt: ";
		getline(cin, init);

		command.push_back(init);

		comm.command(command);

		prog(0);
	}
	return 0;
}

int main() {
	prog(0);
	return 0;
}
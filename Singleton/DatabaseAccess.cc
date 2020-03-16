#include <iostream>
#include <fstream>
#include <map>
using namespace std;
static int instance_count = 0;
class SingletonDatabase{
	map<string,string> database;
	SingletonDatabase(){
		ifstream ifs("db.txt");
		string s,s1;
		while(getline(ifs,s)){
			getline(ifs,s1);
			database[s] = s1;
		}
		instance_count++;
	}
	SingletonDatabase *instance;
	public:
		SingletonDatabase(const SingletonDatabase&) = delete;
		void operator=(const SingletonDatabase&) = delete;
		// Thread safe and Lazy evaluated get function!
		static SingletonDatabase& get(){
			static SingletonDatabase db;
			return db;
		}
		// Non-thread safe and lazy evaluated
		SingletonDatabase* get_instance(){
			if(!instance){
				instance = new SingletonDatabase;
			}
			return instance;
		}
};

int main(){
	auto &db = SingletonDatabase::get();
	auto &db2 = SingletonDatabase::get();
	cout << instance_count << endl;
	return 0;
}
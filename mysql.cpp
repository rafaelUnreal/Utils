#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>







using namespace std;

class MysqlConf {

private:
	stringstream sout;
	ifstream file;

	string password;
	string user;
	string database;
	string ip;
	int port;


	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

public:
	MysqlConf(const char* name){
	file.open(name);
	readFile(file);

	}

	void parseConf(string data){
		int pos;
		stringstream ss;
	//	data.erase(remove_if(data.begin(),data.end(),isspace),data.end());
		if ((pos=data.rfind("ip"))>=0){
			ip = data.substr(pos+3);	
			cout << "ip:" << ip << endl;

		}
		else if ((pos=data.find("database"))>=0){
			database = data.substr(pos+8);	
			cout << "database:" << database << endl;

		}
		else if ((pos=data.find("password"))>=0){
		        password = (data.substr(pos+9));
			//ss >> password; 	
			cout << "password:" << password << endl;

		}

		else if ((pos=data.find("user"))>=0){
			user = data.substr(pos+5);	
			cout << "user:" << user << endl;
		}
		else if ((pos=data.find("port"))>=0){
			ss.clear();
			ss << data.substr(pos+5);	
			ss >> port;
			cout << "port:" << port << endl;

		}


	}
	void readFile(ifstream &file){
	string data;

	while(getline(file,data)){
		//cout << data << endl;
		parseConf(data);
	}

	file.close();
	}

	void createConnection(){

	stringstream ss;
	ss << "tcp://" << ip << ":" << port;
	cout << ss.str() << endl;
	driver = get_driver_instance();
	con = driver->connect(ss.str(),user,password);
	con->setSchema("teste");

	}
	void createStatement(){
	
	stmt = con->createStatement();
	stmt->execute("Create table teste123(id INT)");
	delete stmt;

	}


};


int main(){
	MysqlConf teste("mysql.conf");;
	teste.createConnection();
	teste.createStatement();





}

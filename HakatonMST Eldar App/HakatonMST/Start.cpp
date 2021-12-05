//#include <iostream>
//#include <pqxx/pqxx>
//
//using namespace std;
//using namespace pqxx;
//
//int main(int argc, char* argv[]) {
//	try {
//		connection C("dbname = db1 user = rouser password = Pass1234  host = rc1c-90mkmxvku0h105em.mdb.yandexcloud.net port = 6432 sslmode = require");
//		 
//		if (C.is_open()) {
//			cout << "Opened database successfully: " << C.dbname() << endl;
//			while (true);
//		}
//		else {
//			cout << "Can't open database" << endl;
//			while (true);
//			return 1;
//		}
//	}
//	catch (const std::exception& e) {
//		cerr << e.what() << std::endl;
//		while (true);
//		return 1;
//	}
//}

#include "Global.h"

int main()
{
	//setlocale(LC_ALL, "ru");
	Class_Engine Engine;
	Engine.Start();

	return 0;
}
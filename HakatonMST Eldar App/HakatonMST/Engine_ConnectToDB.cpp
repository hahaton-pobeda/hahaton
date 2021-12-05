#include "Global.h"

bool Class_Engine::ConnectToDB()
{
		try {
		Connection = new pqxx::connection("dbname = db1 user = rouser password = Pass1234  host = rc1c-90mkmxvku0h105em.mdb.yandexcloud.net port = 6432 sslmode = require");
		if (Connection->is_open()) {
			std::cout << "Opened db1 successfully." << Connection->dbname() << std::endl;
			return true;
		}
		else {
			std::cout << "Could not open database." << std::endl;
			return false;
		}
	}
	catch (const std::exception& Exception) {
		std::cerr << Exception.what() << std::endl;
		return false;
	}
}
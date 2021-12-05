bool Class_Engine::ConnectToDB()
{
	try {
		pqxx::connection Connection("dbname = db1 user = rouser password = Pass1234  host = rc1c-90mkmxvku0h105em.mdb.yandexcloud.net port = 6432 sslmode = require");
		if (Connection.is_open()) {
			std::cout << "Opened database successfully: " << Connection.dbname() << std::endl;
			pqxx::work Work{ Connection };
			pqxx::result Result = Work.exec("SELECT * FROM det_coords LIMIT 15");
			int const NumberOf_Rows = Result.size();
			for (int i = 0; i < NumberOf_Rows; ++i)
			{
				pqxx::row const row = Result[i];
				int const NumberOf_Cols = row.size();
				for (int j = 0; j < NumberOf_Cols; ++j)
				{
					pqxx::field const field = row[j];
					std::wcout << field.c_str() << '\t';
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}

			return true;
		}
		else {
			std::cout << "Can't open database" << std::endl;
			return false;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
}
#include "Global.h"

bool Class_Engine::Fill_Sectors()
{
	TransportDetectors.clear();
	try {
		std::string MinHour = CurrentHour.c_str();
		std::string MaxHour = CurrentHour.c_str();
		int NewHourInt = std::stoi(MinHour.substr(0, 2)) - 1;
		int NewMinuteInt = std::stoi(MinHour.substr(3, 2)) - 30;
		std::cout << NewHourInt << " " << NewMinuteInt << std::endl;
		if (NewMinuteInt < 0) { NewMinuteInt = 60 + NewMinuteInt; NewHourInt--; }
		if (NewHourInt < 0) NewHourInt = 0;
		std::string NewHourStr = std::to_string(NewHourInt);
		std::string NewMinuteStr = std::to_string(NewMinuteInt);
		if (NewHourInt < 10) NewHourStr = "0" + NewHourStr;
		if (NewMinuteInt < 10) NewMinuteStr = "0" + NewMinuteStr;
		MinHour[0] = NewHourStr[0]; MinHour[1] = NewHourStr[1];
		MinHour[3] = NewMinuteStr[0]; MinHour[4] = NewMinuteStr[1];
		NewHourInt = std::stoi(MaxHour.substr(0, 2)) + 1;
		NewMinuteInt = std::stoi(MaxHour.substr(3, 2)) + 30;
		std::cout << NewHourInt << " " << NewMinuteInt << std::endl;
		if (NewMinuteInt > 59) { NewMinuteInt = NewMinuteInt - 60; NewHourInt++; }
		if (NewHourInt > 23) NewHourInt = 23;
		NewHourStr = std::to_string(NewHourInt);
		NewMinuteStr = std::to_string(NewMinuteInt);
		if (NewHourInt < 10) NewHourStr = "0" + NewHourStr;
		if (NewMinuteInt < 10) NewMinuteStr = "0" + NewMinuteStr;
		MaxHour[0] = NewHourStr[0]; MaxHour[1] = NewHourStr[1];
		MaxHour[3] = NewMinuteStr[0]; MaxHour[4] = NewMinuteStr[1];
		pqxx::work Work{ *Connection };
		//pqxx::result Result = Work.exec("SELECT DISTINCT grz FROM fvf WHERE date BETWEEN '" + CurrentDay + MinHour + "' and '" + CurrentDay + MaxHour + "' LIMIT 10");
		pqxx::result Result = Work.exec("SELECT * FROM fvf WHERE fvf.rownum % 30 = 0 LIMIT 10");
		int NumberOf_Rows = Result.size();
		for (int i = 0; i < NumberOf_Rows; ++i)
		{
			std::cout << Result[i][0].as<int>() << std::endl;
		}
		return true;
	}
	catch (const std::exception& Exception) {
		std::cerr << Exception.what() << std::endl;
		return false;
	}
}
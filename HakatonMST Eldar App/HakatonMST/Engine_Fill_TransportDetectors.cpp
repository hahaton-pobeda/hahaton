#include "Global.h"

bool Class_Engine::Fill_TransportDetectors()
{
	TransportDetectors.clear();
	try {
		pqxx::work Work{ *Connection };
		pqxx::result Result = Work.exec("SELECT lat, lon, devid, angle, active FROM det_coords");
		int NumberOf_Rows = Result.size();
		for (int i = 0; i < NumberOf_Rows; ++i)
		{
			TransportDetectors.insert(std::pair(Result[i][2].as<int>(), Class_TransportDetector(Result[i][0].as<float>(), Result[i][1].as<float>(), Result[i][3].as<float>(), Result[i][4].c_str())));
		}
		Result = Work.exec("SELECT DISTINCT id, utilisation FROM detectors WHERE time = '" + CurrentDay + CurrentHour + "'");
		NumberOf_Rows = Result.size();
		for (int i = 0; i < NumberOf_Rows; ++i)
		{
			if (!Result[i][1].is_null() && TransportDetectors.find(Result[i][0].as<int>()) != TransportDetectors.end()) {
				TransportDetectors[Result[i][0].as<int>()].Utilisation = Result[i][1].as<float>();
			}
		}
		return true;
	}
	catch (const std::exception& Exception) {
		std::cerr << Exception.what() << std::endl;
		return false;
	}
}
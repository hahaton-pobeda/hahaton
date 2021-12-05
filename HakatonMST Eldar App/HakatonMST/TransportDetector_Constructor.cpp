#include "Global.h"

Class_TransportDetector::Class_TransportDetector(float Lat, float Lon, int L_Angle, std::string L_IsActive)
{
	Utilisation = -1;
	X = ((((Lon - 37.1f) * 1000) + 300) * 0.6) * 5;
	Y = (1600 * 1.5f - (((((Lat - 55.6f) * 1000) -180)) + 200) * 5);
	Angle = L_Angle;
	if (L_IsActive == "yes") IsActive = true;
}

Class_TransportDetector::Class_TransportDetector()
{
	Utilisation = -1;
}


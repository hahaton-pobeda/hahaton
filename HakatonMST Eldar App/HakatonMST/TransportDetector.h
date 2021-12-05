#pragma once
#include "Global.h"

class Class_TransportDetector {
public:
	bool IsActive = false;
	float X, Y;
	char Utilisation;
	int Angle;
	Class_TransportDetector(float, float, int, std::string);
	Class_TransportDetector();
};
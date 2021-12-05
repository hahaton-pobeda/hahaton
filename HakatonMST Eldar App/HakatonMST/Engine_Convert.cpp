#include "Global.h"

float Class_Engine::ConvertLatToX(float Lon) {
	return (((((Lon - 55.6f) * 1000) + 200) * 1.5) + 200) * 4;
}

float Class_Engine::ConvertLonToY(float Lat) {
	return (((Lat - 37.1f) * 1000) - 50) * 4;
}
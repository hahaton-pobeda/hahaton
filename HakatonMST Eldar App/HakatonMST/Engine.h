#pragma once
#include "Global.h"

class Class_Engine {
public:
	void Start();
	bool ConnectToDB();
	void Runtime_Iteration();
	Class_Map* Map;
	std::string CurrentDay, CurrentHour;
	std::map<unsigned int, Class_TransportDetector> TransportDetectors;
	pqxx::connection* Connection;
	sf::RenderWindow* Window;
	tgui::Gui GUI;
	bool Fill_TransportDetectors();
	bool Fill_Sectors();
	float ConvertLatToX(float Lat);
	float ConvertLonToY(float Lon);
private:
	Class_Menu_Initial* Menu_Initial;
	void Initialize();
	void Runtime();
	void Interact();
};

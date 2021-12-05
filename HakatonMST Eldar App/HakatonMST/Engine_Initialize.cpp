#include "Global.h"

void Class_Engine::Initialize()
{
	Map = new Class_Map(this);
	GUI.add(Map->Panel, "Map_Panel");

	Menu_Initial = new Class_Menu_Initial(this);
	GUI.add(Menu_Initial->Panel, "Menu_Initial_Panel");
}
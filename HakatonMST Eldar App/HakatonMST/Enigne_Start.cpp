#include "Global.h"

void Class_Engine::Start()
{
	Window = new sf::RenderWindow{ {1600, 900}, "Window" };
	GUI.setTarget(*Window);
	Initialize();
	Runtime();
}
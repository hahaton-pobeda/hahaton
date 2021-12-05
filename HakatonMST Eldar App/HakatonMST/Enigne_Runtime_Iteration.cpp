#include "Global.h"

void Class_Engine::Runtime_Iteration()
{
		Interact();
		Window->clear(sf::Color::White);
		Map->Draw();
		GUI.draw();
		Window->display();
}
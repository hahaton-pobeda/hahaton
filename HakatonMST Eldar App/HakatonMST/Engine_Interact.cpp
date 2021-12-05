#include "Global.h"

void Class_Engine::Interact()
{
	Map->Interact();
	sf::Event event;
	while (Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) Window->close();
		if (event.type == sf::Event::MouseWheelMoved) Map->TargetZoom -= float(event.mouseWheel.delta) / 12.f;
		bool L_InteractionResult = GUI.handleEvent(event);
	}
}


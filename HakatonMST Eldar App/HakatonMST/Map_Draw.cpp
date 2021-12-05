#include "Global.h"

void Class_Map::Draw()
{
	Engine->Window->setView(View);
	if (MapSprite_Moscow != nullptr) {
		Engine->Window->draw(*MapSprite_Moscow);
	}
	if (MapSprite_TransportLoad != nullptr) {
		Engine->Window->draw(*MapSprite_TransportLoad);
	}
	Engine->Window->setView(Engine->Window->getDefaultView());
}
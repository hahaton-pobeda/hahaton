#include "Global.h"

Class_Map::Class_Map(Class_Engine* L_Engine)
{
	Engine = L_Engine;
	Panel = tgui::Panel::create("100%, 100%");
	Panel->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 0));

	MapSprite_Moscow = new sf::Sprite();
	sf::Texture* Texture;
	Texture = new sf::Texture;
	Texture->loadFromFile("Map.png");
	MapSprite_Moscow->setTexture(*Texture);
	MapSprite_Moscow->setScale(0.75f, 0.75f);
	MapSprite_Moscow->setPosition(1510, 400);
	MapSprite_Moscow->setColor(sf::Color(255, 255, 255, 150));
}

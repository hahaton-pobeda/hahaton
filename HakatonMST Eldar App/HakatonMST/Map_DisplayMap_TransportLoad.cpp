#include "Global.h"

void Class_Map::ReloadMap_TransportLoad()
{
	sf::RenderTexture* Texture;
	sf::Texture* ArrowTexture, *KrestikTexture;
	ArrowTexture = new sf::Texture;
	KrestikTexture = new sf::Texture;
	ArrowTexture->loadFromFile("Arrow.png");
	KrestikTexture->loadFromFile("Krestik.png");
	Texture = new sf::RenderTexture;
	Texture->create(1600 * 4, 900 * 4);
	Texture->clear(sf::Color::Transparent);
	Texture->setSmooth(true);
	for (auto const& [Key, Value] : Engine->TransportDetectors)
	{
		int Red = Value.Utilisation * 2.5f;
		int Green = 251 - Value.Utilisation * 2.5f;
		if (!Value.IsActive > 25 || Value.Utilisation == -1 && DisplayInvalidDetectors) {
			sf::Sprite Krestik;
			Krestik.setTexture(*KrestikTexture);
			Krestik.setOrigin(20, 20);
			Krestik.setPosition(Value.X, Value.Y);
			Krestik.setScale(0.5f, 0.5f);
			Krestik.setColor(sf::Color(0, 0, 200, 200));
			Texture->draw(Krestik);
		}
		if (Value.Utilisation > 25 && DisplayMatrix) {
			sf::Sprite Arrow;
			Arrow.setTexture(*ArrowTexture);
			Arrow.setOrigin(10, 100);
			Arrow.setPosition(Value.X, Value.Y);
			Arrow.setRotation(Value.Angle + 90);
			Arrow.setScale(float(Value.Utilisation) * 1.8f / 100, float(Value.Utilisation) * 1.8f / 100);
			Arrow.setColor(sf::Color(Red, Green, 0, 255));
			Texture->draw(Arrow);
		}
		if (Value.Utilisation > -1 && Value.Utilisation < 50) {
			sf::CircleShape Shape;
			Shape.setRadius(8);
			Shape.setOrigin(8, 8);
			Shape.setFillColor(sf::Color(Red, Green, 0, 100));
			Shape.setPosition(Value.X, Value.Y);
			Texture->draw(Shape);
		}
	}
	for (auto const& [Key, Value] : Engine->TransportDetectors)
	{
		if (Value.Utilisation >= 50) {
			sf::CircleShape Shape;
			Shape.setRadius(12);
			Shape.setOrigin(12, 12);
			int Red = Value.Utilisation * 2.5f;
			int Green = 251 - Value.Utilisation * 2.5f;
			Shape.setFillColor(sf::Color(Red, Green, 0, 140));
			Shape.setPosition(Value.X, Value.Y);
			Texture->draw(Shape);
		}
	}
	Texture->display();
	if (MapSprite_TransportLoad != nullptr) delete MapSprite_TransportLoad;
	MapSprite_TransportLoad = new sf::Sprite(Texture->getTexture());
}
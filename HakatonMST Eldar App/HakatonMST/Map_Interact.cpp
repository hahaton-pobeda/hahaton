#include "Global.h"

void Class_Map::Interact()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) View.move(-5 * View.getSize().x / Engine->Window->getSize().x, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) View.move(5 * View.getSize().x / Engine->Window->getSize().x, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) View.move(0, -5 * View.getSize().y / Engine->Window->getSize().y);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) View.move(0, 5 * View.getSize().y / Engine->Window->getSize().y);
	if (View.getCenter().x - View.getSize().x / 2 < 0) View.setCenter(View.getSize().x / 2, View.getCenter().y);
	if (View.getCenter().y - View.getSize().y / 2 < 0) View.setCenter(View.getCenter().x, View.getSize().y / 2);

	if (TargetZoom > 1) TargetZoom = 1; if (TargetZoom < 0.1) TargetZoom = 0.1;
	if (CurrentZoom < (TargetZoom * 0.955f)) {
		CurrentZoom *= 1.04f;
		View.setSize(View.getSize().x * 1.04f, View.getSize().y * 1.04f);
	}
	if (CurrentZoom > (TargetZoom * 1.045f)) {
		CurrentZoom *= 0.96f;
		View.setSize(View.getSize().x * 0.96f, View.getSize().y * 0.96f);
	}

}
#pragma once
#include "Global.h"

class Class_Map {
private:
	Class_Engine* Engine;
public:
	void Draw();
	void ReloadMap_TransportLoad();
	std::shared_ptr<tgui::Panel> Panel;
	Class_Map(Class_Engine*);
	bool Initialize();
	void Interact();
	sf::Sprite* MapSprite_TransportLoad = nullptr;
	sf::Sprite* MapSprite_Moscow = nullptr;
	sf::View View;
	void Slider_Time_onUnfocus(tgui::Slider::Ptr);
	void Button_ToMatrix_onClick();
	void Button_DisplayInvalidDetectors_onClick();
	void Slider_Time_onValueChange(tgui::Slider::Ptr);
	float CurrentZoom = 1, TargetZoom = 1;
	bool DisplayMatrix = false;
	bool DisplayInvalidDetectors = false;
};
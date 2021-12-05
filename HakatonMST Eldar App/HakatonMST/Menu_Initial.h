#pragma once
#include "Global.h"

class Class_Menu_Initial {
private:
	Class_Engine* Engine;
public:
	std::shared_ptr<tgui::Panel> Panel;
	Class_Menu_Initial(Class_Engine*);
	void Button_Connect_onClick();
};
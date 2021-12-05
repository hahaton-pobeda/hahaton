#include "Global.h"

Class_Menu_Initial::Class_Menu_Initial(Class_Engine* L_Engine) {
	Engine = L_Engine;
	Panel = tgui::Panel::create("50%, 50%");
	Panel->setOrigin(0.5, 0.5);
	Panel->setPosition("50%", "50%");
	Panel->getRenderer()->setBorderColor(tgui::Color::Black);
	Panel->getRenderer()->setBorders(tgui::Borders::Outline(2));
	tgui::Label::Ptr Label_Description = tgui::Label::create(L"Вас приветствует программа мониторинга дорожной ситуации");
	Label_Description->setTextSize(15);
	Label_Description->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Description->setOrigin(0.5, 0.5);
	Label_Description->setPosition("50%", "30%");
	tgui::Button::Ptr Button_Connect = tgui::Button::create(L"Поключиться к базе данных");
	Button_Connect->getRenderer()->setBorders(tgui::Borders::Outline(2));
	Button_Connect->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Connect->setOrigin(0.5, 0.5);
	Button_Connect->setPosition("50%", "70%");
	Button_Connect->setSize("30%", "20%");
	Button_Connect->onClick(&Class_Menu_Initial::Button_Connect_onClick, this);
	tgui::Label::Ptr Label_Result = tgui::Label::create(L" ");
	Label_Result->setTextSize(12);
	Label_Result->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Result->setOrigin(0.5, 0.5);
	Label_Result->setPosition("50%", "85%");
	Panel->add(Label_Description, "Label_Description");
	Panel->add(Button_Connect, "Button_Connect");
	Panel->add(Label_Result, "Label_Result");
}


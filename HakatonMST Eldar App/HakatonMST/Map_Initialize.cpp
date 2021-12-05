#include "Global.h"

bool Class_Map::Initialize()
{
	Engine->CurrentDay = "2021-11-29 ";
	Engine->CurrentHour = "00:00:00";
	if (Engine->Fill_TransportDetectors()) {
		View.setSize(1600 * 3, 900 * 3);
		tgui::Slider::Ptr Slider_Time = tgui::Slider::create(0.f, 1439.f);
		Slider_Time->setSize("2%, 2%");
		Slider_Time->setWidth("40%");
		Slider_Time->setOrigin(0, 0.5);
		Slider_Time->setPosition("2%, 2%");
		Slider_Time->getRenderer()->setBorders(3);
		Slider_Time->onMouseLeave(&Class_Map::Slider_Time_onUnfocus, this, Slider_Time);
		Slider_Time->onValueChange(&Class_Map::Slider_Time_onValueChange, this, Slider_Time);
		tgui::Label::Ptr Label_Time = tgui::Label::create(Engine->CurrentDay + Engine->CurrentHour);
		Label_Time->setTextSize(20);
		Label_Time->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
		Label_Time->setOrigin(0.5, 0.5);
		Label_Time->setPosition("21%", "8%");
		tgui::Button::Ptr Button_ToMatrix = tgui::Button::create(L"Показать стрелки направления движения");
		Button_ToMatrix->getRenderer()->setBorders(tgui::Borders::Outline(2));
		Button_ToMatrix->getRenderer()->setBorderColor(tgui::Color::Black);
		Button_ToMatrix->setOrigin(1, 1);
		Button_ToMatrix->setPosition("100%", "100%");
		Button_ToMatrix->setSize("25%", "8%");
		Button_ToMatrix->onClick(&Class_Map::Button_ToMatrix_onClick, this);
		tgui::Button::Ptr Button_DisplayInvalidDetectors = tgui::Button::create(L"Показать нерабочие детекторы");
		Button_DisplayInvalidDetectors->getRenderer()->setBorders(tgui::Borders::Outline(2));
		Button_DisplayInvalidDetectors->getRenderer()->setBorderColor(tgui::Color::Black);
		Button_DisplayInvalidDetectors->setOrigin(1, 1);
		Button_DisplayInvalidDetectors->setPosition("100%", "92%");
		Button_DisplayInvalidDetectors->setSize("25%", "8%");
		Button_DisplayInvalidDetectors->onClick(&Class_Map::Button_DisplayInvalidDetectors_onClick, this);
		Panel->add(Slider_Time, "Slider_Time");
		Panel->add(Label_Time, "Label_Time");
		Panel->add(Button_ToMatrix, "Button_ToMatrix");
		Panel->add(Button_DisplayInvalidDetectors, "Button_DisplayInvalidDetectors");
		return true;
	}
	else return false;
}

//int const NumberOf_Rows = Result.size();
//for (int i = 0; i < NumberOf_Rows; ++i)
//{
//	pqxx::row const row = Result[i];
//	int const NumberOf_Cols = row.size();
//	for (int j = 0; j < NumberOf_Cols; ++j)
//	{
//		pqxx::field const field = row[j];
//	}
//}
#include "Global.h"

void Class_Map::Slider_Time_onUnfocus(tgui::Slider::Ptr Slider)
{
	Engine->Fill_TransportDetectors();
	ReloadMap_TransportLoad();
}

void Class_Map::Slider_Time_onValueChange(tgui::Slider::Ptr Slider)
{
	int Value = Slider->getValue();
	int Hour = Value / 60;
	int Minute = Value % 60;
	Minute = Minute / 5;
	Minute = Minute * 5;
	std::string HourString = std::to_string(Hour);
	if (Hour < 10) HourString = "0" + HourString;
	std::string MinuteString = std::to_string(Minute);
	if (Minute < 10) MinuteString = "0" + MinuteString;
	Engine->CurrentHour = HourString + ":" + MinuteString + ":" + "00";
	tgui::Label::Ptr Label_Time = Panel->get<tgui::Label>("Label_Time");
	Label_Time->setText(Engine->CurrentDay + Engine->CurrentHour);
}

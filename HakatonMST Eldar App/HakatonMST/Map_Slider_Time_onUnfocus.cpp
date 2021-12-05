#include "Global.h"

void Class_Map::Slider_Time_onUnfocus(tgui::Slider::Ptr Slider)
{
	

}

void Class_Map::Slider_Time_onChangeValue(tgui::Slider::Ptr Slider)
{
	int Value = Slider->getValue() * 144;

}

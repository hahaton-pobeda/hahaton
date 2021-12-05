#include "Global.h"

void Class_Map::Button_ToMatrix_onClick()
{
tgui::Button::Ptr Button_ToMatrix = Panel->get<tgui::Button>("Button_ToMatrix");
	if (DisplayMatrix) {
		Button_ToMatrix->setText(L"Показать стрелки направления движения");
		DisplayMatrix = false;
		Engine->Fill_TransportDetectors();
		ReloadMap_TransportLoad();
	}
	else {
		Button_ToMatrix->setText(L" Скрыть стрелки направления движения");
		DisplayMatrix = true;
		Engine->Fill_TransportDetectors();
		ReloadMap_TransportLoad();
	}
}

void Class_Map::Button_DisplayInvalidDetectors_onClick()
{
	tgui::Button::Ptr Button_DisplayInvalidDetectors = Panel->get<tgui::Button>("Button_DisplayInvalidDetectors");
	if (DisplayInvalidDetectors) {
		Button_DisplayInvalidDetectors->setText(L"Показать нерабочие детекторыя");
		DisplayInvalidDetectors = false;
		Engine->Fill_TransportDetectors();
		ReloadMap_TransportLoad();
	}
	else {
		Button_DisplayInvalidDetectors->setText(L" Скрыть нерабочие детекторы");
		DisplayInvalidDetectors = true;
		Engine->Fill_TransportDetectors();
		ReloadMap_TransportLoad();
	}
}
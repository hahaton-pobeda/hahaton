#include "Global.h"

void Class_Menu_Initial::Button_Connect_onClick()
{
	tgui::Label::Ptr Label_Result = Panel->get<tgui::Label>("Label_Result");
	if (Engine->ConnectToDB()) {
		Label_Result->setText(L"����������� �������\n�������� ������...");
		Engine->Runtime_Iteration();
		if (Engine->Map->Initialize()) {
			Label_Result->setText(L"�������� ������ �������\n������������ �����...");
			Engine->Runtime_Iteration();
			Engine->Map->ReloadMap_TransportLoad();
			tgui::Panel::Ptr Menu_Initial = Engine->GUI.get<tgui::Panel>("Menu_Initial_Panel");
			Engine->GUI.remove(Menu_Initial);
		}
		else {
			Label_Result->setText(L"�� ������� ��������� ������ ��� �����");
		}
	}
	else {
		Label_Result->setText(L"����������� �� �������");
	}
}
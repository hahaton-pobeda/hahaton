#include "Global.h"

void Class_Engine::Runtime()
{
	while (Window->isOpen()) Runtime_Iteration();
}
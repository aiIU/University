#include "pch.h"

#include "ProcessManager.h"
#include "ProcessManagerMenu.h"

int main()
{
	auto manager = make_shared<ProcessManager>();
	auto menu = make_shared<ProcessManagerMenu>();

	if (manager && menu)
	{
		menu->Initialize(manager);
		menu->Process();
	}

	return 0;
}
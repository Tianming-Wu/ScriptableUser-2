#define BUILDING_SUCORE_DLL
#include "SUCore.h"

LogFx* LogHx;

int SUCore::init() {
	LogHx = new LogFx("scuser.log");

	wchar_t* _cmdLine = GetCommandLineW();
	LogHx->write("main", "Running with arguments: %ws\n", _cmdLine);

	//GetProcessInformation(GetStdHandle(STD_OUTPUT_HANDLE))

	delete LogHx;
	return 0;
}
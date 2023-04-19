#define BUILDING_SUCORE_DLL
#include "SUCore.h"

wLogFx* LogHx;

SUCore::SUCore()
{
	LogHx = new wLogFx(L"scuser.log");

	wchar_t* _cmdLine = GetCommandLineW();
	LogHx->write(L"main", L"Running with arguments: %ws\n", _cmdLine);

	//GetProcessInformation(GetStdHandle(STD_OUTPUT_HANDLE))
}

SUCore::~SUCore()
{

	delete LogHx;
}

int _sucall SUCore::ExecuteFromFile(const std::wstring FileName)
{
	std::wifstream ifs(FileName);
	if(ifs.fail())
	{
		LogHx->write(L"SUEngine", L"Failed to open file: %d", FileName.c_str());
		return 1;
	}
	std::wstring wbuf(L""); std::wstringstream wsbuf(L"");
	std::wstring _sccmd;
	int el = 0, ec = 0, ew = 0;
	while (getline(ifs, wbuf)) {
		el++; wsbuf << wbuf;
		wsbuf >> _sccmd;
		_sccmd = upperCase(_sccmd);
		if (_sccmd == L"env") {

		}
		else if (_sccmd == L"exit") {


		}
		


		wsbuf.str(L"");
		if (ifs.eof()) break;
	}

	ifs.close();
	return 0;
}

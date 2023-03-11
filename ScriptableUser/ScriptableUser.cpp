#include "ScriptableUser.h"

#ifdef IMC_USEWCEX_PSRD
#define wWinMain WinMain
#define __LPWSTR LPSTR
#else
#define __LPWSTR LPWSTR
#endif

LogFx* LogHx;

/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, __LPWSTR lpCmdLine, int nShowCmd) {
	InitModules();


	return 0;
}*/


int main() {
	LogHx = new LogFx("scuser.log");

	wchar_t* _cmdLine = GetCommandLineW();
	LogHx->write("main", "Running with arguments: %ws\n", _cmdLine);

	InitModules();

	//GetProcessInformation(GetStdHandle(STD_OUTPUT_HANDLE))

	delete LogHx;
	return 0;
}


void InitModules() noexcept {
	try {
		for (auto it : fsit("Modules\\")) {
			string _pathd = it.path().string(); size_t _pthsuf;
			LogHx->write("Init", "Initializing module name %s\n", _pathd.c_str());
			if ((_pthsuf = _pathd.find_last_of(".")) != string::npos) {
				string _suffix = _pathd.substr(_pthsuf);
				if (_suffix.compare(".dll")) {
					LogHx->write("Init", "Skipping invalid suffix %s\n", _suffix.c_str());
					continue;
				}
				LogHx->write("Init", "Load of %s skipped.\n", _pathd.c_str());

			}
			///TODO: Write modules initialization.
		}
	}
	catch (std::filesystem::filesystem_error dterr) {
		LogHx->write("InitModules()", "INIT_ERROR: %s\n", dterr.what());
	}
	LogHx->write("Init", "Initialization finished.\n");
}

CommandIndex GetCommandIndex(string _Command) {
	


	return CI_Undef;
}

void* VarHost(string _Command) {



	return nullptr;
}
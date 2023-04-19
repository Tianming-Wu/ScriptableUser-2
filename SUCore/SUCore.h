#pragma once

#include <windows.h>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <atlconv.h>

#include "..\SUPublic\stringlist.h"
#include "..\SUPublic\logfx.h"
#include "..\SUPublic\basic.h"

using fsit = std::filesystem::directory_iterator;
using std::string;

#include "..\SUPublic\publicdef.h"
#include "..\SUPublic\command.h"

#ifdef BUILDING_SUCORE_DLL
#define _sucall __declspec(dllexport)
#else
#define _sucall __declspec(dllimport)
#endif

class SUCore {
public:
	SUCore();
	~SUCore();
	int _sucall ExecuteFromFile(const std::wstring FileName);
};
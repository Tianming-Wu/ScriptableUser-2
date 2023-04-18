#pragma once

#include <windows.h>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <atlconv.h>

#include "VarsCtrl.h"

using fsit = std::filesystem::directory_iterator;
using std::string;

typedef unsigned char byte;
typedef unsigned char* pbyte;
typedef unsigned int uint;
typedef void* pvoid;

enum CommandIndex {
	CI_Undef = -1,
	CI_Confirm, CI_Ask, CI_Env, CI_Cmd, CI_System,
	CI_Run, CI_Pc, CI_Reg, CI_Var, CI_Findwindow,
	CI_File, CI_User
};

enum VariableType {
	VT_Undef = -1,
	VT_short, VT_ushort, VT_byte, VT_ubyte, VT_int, VT_uint, VT_long, VT_ulong,
	VT_hpnum,
	VT_ByteArray,
	VT_String, VT_BasicString,
	VT_HFILE, VT_HPROCESS, VT_HMODULE,
	VT_HWND, VT_HDISPLAY,
	VT_HREG, VT_HREGKEY,
	VT_HKEYBOARD, VT_HKEY,
	VT_POS, VT_SCPOS, VT_WNDPOS
};

size_t getStdVarSize(VariableType _type) {
	switch (_type) {
	case VT_Undef: return 0;
	case VT_short: case VT_ushort: return sizeof(short);
	case VT_byte: case VT_ubyte: return sizeof(byte);
	case VT_int: case VT_uint: return sizeof(int);
	case VT_long: case VT_ulong: return sizeof(long);
	//VT_hpnum
	case VT_ByteArray: return sizeof(pbyte);
	//VT_String, VT_BasicString
	case VT_HFILE: return sizeof(HFILE);
	//case VT_HPROCESS: return sizeof(HPROCESS);
	case VT_HMODULE: return sizeof(HMODULE);
	case VT_HWND: return sizeof(HWND);
	//case VT_HDISPLAY: return sizeof(HDISPLAY);
	//case VT_HREG: return sizeof(HREG);
	//case VT_HREGKEY: return sizeof(HREGKEY);
	//VT_HKEYBOARD, VT_HKEY
	case VT_POS: case VT_SCPOS: case VT_WNDPOS: return sizeof(POINT);
	default: return 0;
	}
}

namespace myMemCtrl {

	pbyte realloc(pbyte _orig, size_t _nsize, bool _SrcCopy = true) noexcept {
		pbyte _nric = new byte[_nsize];
		if (_SrcCopy && (_nric != nullptr)) {
			memcpy(_nric, _orig, _nsize);
			delete _orig;
		}
		return _nric;
	}
}

class VarObject {
private:
	VariableType type;
	pbyte _data;
public:
	VarObject()  noexcept {
		type = VT_Undef; _data = nullptr;
	}

	void fromData(void* pData, size_t ptr_size) {
		if (_data == nullptr) _data = myMemCtrl::realloc(_data, ptr_size, false);
		memcpy(_data, pData, ptr_size);
	}

	void fromData(pvoid pData, VariableType _type) {
		if (_data == nullptr) _data = myMemCtrl::realloc(_data, getStdVarSize(_type), false);
		memcpy(_data, pData, getStdVarSize(_type));
	}

	void* toData() {
		return (void*)_data;
	}
};

class VarList {
	void* _ptlist;
public:
	void AddObject(VarObject _adddata) {
		
	}

};

class LogFx {
	/*FILE* pf;*/ std::ofstream ofs;
	string ProcessName; int pid;
	size_t _BufSize;
	char* _CplBuffer1, * _CplBuffer2;
public:

	LogFx(const char* _FileName, const char* _ProcessName = nullptr, size_t BufSize = 256)
		: _BufSize(BufSize)
	{
		if (_ProcessName == nullptr) {
			//ProcessName = nullptr;
			char* Mname = new char[32767];
			GetModuleFileNameA(NULL, Mname, sizeof(char[32767]));
			string MnStr(Mname); size_t lpos; delete []Mname;

			if ((lpos = MnStr.find_last_of('\\')) != string::npos) {
				ProcessName = MnStr.substr(lpos + 1);
			}
			else ProcessName = MnStr;
		}
		else {
			ProcessName = _ProcessName;
		}

		_CplBuffer1 = new char[_BufSize], _CplBuffer2 = new char[_BufSize];
		pid = _getpid();
		//fopen_s(&pf, _FileName, "w");
		ofs = std::ofstream(_FileName, std::ios::app);
	}

	~LogFx() {
		ofs.write("\n", strlen("\n"));
		ofs.close();
	}

	string timestamp() {
		time_t tm0 = time(0);
		tm _tm;
		localtime_s(&_tm, &tm0);
		
		static char _TimeBuffer[32];
		sprintf_s(_TimeBuffer, 32, "%02d/%02d/%02d %02d:%02d:%02d",
			_tm.tm_year + 1900, _tm.tm_mon+1, _tm.tm_mday,
			_tm.tm_hour, _tm.tm_min, _tm.tm_sec
		);
		return string(_TimeBuffer);
	}

template<class... Dte>
	int write(const char* _ModuleName, const char* _Format, Dte... _Data) {
		//if (pf == NULL) return -1;
		int ret = sprintf_s(_CplBuffer1, _BufSize, _Format, _Data...);
		sprintf_s(_CplBuffer2, _BufSize, "[%s|%d] [%s/%s]: %s", timestamp().c_str(), pid, ProcessName.c_str(), _ModuleName, _CplBuffer1);
		ofs.write(_CplBuffer2, strlen(_CplBuffer2));
		return ret;
	}

	inline size_t GetBufferSize() { return _BufSize; }
	inline bool ResetBufferSize(size_t _NewVol) {
		_CplBuffer1 = (char*)myMemCtrl::realloc((pbyte)_CplBuffer1, _NewVol, false);
		_CplBuffer2 = (char*)myMemCtrl::realloc((pbyte)_CplBuffer2, _NewVol, false);
		_BufSize = _NewVol;
	}

};



void InitModules()  noexcept;
CommandIndex GetCommandIndex(string _Command);
void* VarHost(string _Command);
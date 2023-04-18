#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>

#include "publicdef.h"

namespace myMemCtrl {
	pbyte realloc(pbyte _orig, size_t _nsize, bool _SrcCopy = true) noexcept {
		pbyte  _nric = new byte[_nsize];
		if (_SrcCopy && (_nric != nullptr)) {
			memcpy(_nric, _orig, _nsize);
			delete _orig;
		}
		return _nric;
	}
}

class LogFx {
	std::ofstream ofs;
	std::string ProcessName; int pid;
	size_t _BufSize;
	char* _CplBuffer1, * _CplBuffer2;
public:

	LogFx(const char* _FileName, const char* _ProcessName = nullptr, size_t BufSize = 256)
		: _BufSize(BufSize)
	{
		if (_ProcessName == nullptr) {
			char* Mname = new char[32767];
			GetModuleFileNameA(NULL, Mname, sizeof(char[32767]));
			std::string MnStr(Mname); size_t lpos; delete []Mname;

			if ((lpos = MnStr.find_last_of('\\')) != std::string::npos) {
				ProcessName = MnStr.substr(lpos + 1);
			}
			else ProcessName = MnStr;
		}
		else {
			ProcessName = _ProcessName;
		}

		_CplBuffer1 = new char[_BufSize], _CplBuffer2 = new char[_BufSize];
		pid = _getpid();
		ofs = std::ofstream(_FileName, std::ios::app);
	}

	~LogFx() {
		ofs.write("\n", strlen("\n"));
		ofs.close();
	}

	std::string timestamp() {
		time_t tm0 = time(0);
		tm _tm;
		localtime_s(&_tm, &tm0);
		
		static char _TimeBuffer[32];
		sprintf_s(_TimeBuffer, 32, "%02d/%02d/%02d %02d:%02d:%02d",
			_tm.tm_year + 1900, _tm.tm_mon+1, _tm.tm_mday,
			_tm.tm_hour, _tm.tm_min, _tm.tm_sec
		);
		return std::string(_TimeBuffer);
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
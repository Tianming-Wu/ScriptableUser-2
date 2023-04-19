#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>

#include "publicdef.h"

#undef size_t;
typedef __int64 size_t;

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

template <typename _T>
class basic_LogFx
{
	using fxofstream = std::basic_ofstream<_T, std::char_traits<_T>>;
	using fxstring = std::basic_string<_T, std::char_traits<_T>, std::allocator<_T>>;
	using cw = sizeof(_T);

#if _T == char
	using fxGetModuleFileName = GetModuleFileNameA;
	using fxprintf = printf;
	using fxsprintf_s = sprintf_s;
	#define fxText(quote) quote
#else
	using fxGetModuleFileName = GetModuleFileNameW;
	using fxprintf = wprintf;
	using fxsprintf_s = swprintf_s;
	#define fxText(quote) L##quote
#endif

	fxstring ProcessName; int pid;
	size_t _BufSize;
	_T* _CplBuffer1, * _CplBuffer2;
public:

	basic_LogFx(const _T* _FileName, const _T* _ProcessName = nullptr, size_t BufSize = 256)
		: _BufSize(BufSize)
	{
		if (_ProcessName == nullptr) {
			_T* Mname = new _T[32767];
			GetModuleFileName(NULL, Mname, sizeof(_T[32767]));
			fxstring MnStr(Mname); size_t lpos; delete []Mname;

			if ((lpos = MnStr.find_last_of('\\')) != fxstring::npos) {
				ProcessName = MnStr.substr(lpos + 1);
			}
			else ProcessName = MnStr;
		}
		else {
			ProcessName = _ProcessName;
		}

		_CplBuffer1 = new char[_BufSize], _CplBuffer2 = new char[_BufSize];
		pid = _getpid();
		ofs = fxofstream(_FileName, std::ios::app);
	}

	~basic_LogFx() {
		ofs.write(fxText("\n"), strlen(fxText("\n")));
		ofs.close();
	}

	fxstring timestamp() {
		time_t tm0 = time(0);
		tm _tm;
		localtime_s(&_tm, &tm0);
		
		static _T _TimeBuffer[32];
		fxsprintf_s(_TimeBuffer, 32, fxText("%02d/%02d/%02d %02d:%02d:%02d"),
			_tm.tm_year + 1900, _tm.tm_mon+1, _tm.tm_mday,
			_tm.tm_hour, _tm.tm_min, _tm.tm_sec
		);
		return fxstring(_TimeBuffer);
	}

template<class... Dte>
	int write(const _T* _ModuleName, const _T* _Format, Dte... _Data) {
		int ret = sprintf_s(_CplBuffer1, _BufSize, _Format, _Data...);
		fxsprintf_s(_CplBuffer2, _BufSize, fxText("[%s|%d] [%s/%s]: %s"), timestamp().c_str(), pid, ProcessName.c_str(), _ModuleName, _CplBuffer1);
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

using LogFx = basic_LogFx<char>;
using wLogFx = basic_LogFx<wchar_t>;
#pragma once

typedef unsigned long size_t;

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
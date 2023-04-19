#pragma once

#include <string>

using namespace std;

constexpr int caseDelta = 'A' - 'a';

string upperCase(const string& _Ref) {
    string up(_Ref); size_t len = up.length();
    for (size_t i = 0; i < len; i++) {
        if (up[i] >= 'a' && up[i] <= 'z') up[i] += caseDelta;
    }
    return up;
}

wstring upperCase(const wstring& _Ref) {
    wstring up(_Ref); size_t len = up.length();
    for (size_t i = 0; i < len; i++) {
        if (up[i] >= L'a' && up[i] <= L'z') up[i] += caseDelta;
    }
    return up;
}
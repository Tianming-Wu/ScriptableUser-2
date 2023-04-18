#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace std {

    template <typename _tcType>
    class _tagStringList {
        using _tagString = std::basic_string<_tcType, std::char_traits<_tcType>, std::allocator<_tcType>>;
        using _tagStringStream = std::basic_stringstream<_tcType, std::char_traits<_tcType>, std::allocator<_tcType>>;
    private:

    public:
        std::vector<_tagString> strListv;

        enum SplitMethod {
            SplDefault, SplArgvStyle
        };

        _tagStringList(_tagString __Source, SplitMethod method = SplitMethod::SplDefault) {
            if (!__Source.empty()) {
                _tagStringStream slstr; _tagString tmpstr;
                slstr << __Source;
                while (slstr >> tmpstr) {
                    strListv.push_back(tmpstr);
                }
            }
        }

        using iterator = typename::std::vector<_tagString>::iterator;

        inline iterator begin() { return strListv.begin(); }
        inline iterator end() { return strListv.end(); }
    };

    using StringList = _tagStringList<char>;
    using wStringList = _tagStringList<wchar_t>;

} //namespace std

//local clear
#undef _tagString
#undef _tagStringStream
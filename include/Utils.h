#pragma once

#include "data_macros.h"

class Utils {
public:
	template<typename ...Ts> static str_type str_build(const Ts& ...args);
	static void str_copy_to_char(char* char_arr, const str_type& str);
	static str_type char_to_str(const char* char_arr, const data_size& siz);
	static std::vector<str_type> str_split(const str_type& str, const char_type& split_char);
	static str_type str_left_padding(const str_type& str, const size_t& padding_len, const char_type& padding_char);
};

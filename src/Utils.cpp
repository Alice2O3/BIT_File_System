#include "Utils_Template.cpp"

using namespace std;

void Utils::str_copy_to_char(char* char_arr, const str_type& str) {
	str.copy(char_arr, str.length());
}

str_type Utils::char_to_str(const char* char_arr, const data_size& siz) {
	return str_type(char_arr, char_arr + siz);
}

str_type Utils::str_left_padding(const str_type& str, const size_t& padding_len, const char_type& padding_char) {
	const auto& len = str.length();
	if (len < padding_len) {
		return str + string(padding_len - len, padding_char);
	}
	return str;
}
#include "FileIO_Template.cpp"
#include "Data.h"
#include "Utils_Template.cpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

void FileIO::create_dir(const str_type& dir) {
	filesystem::create_directory(dir);
}

void FileIO::delete_file(const str_type& file_path) {
	filesystem::remove(file_path);
}

list<str_type> FileIO::search_directory(const str_type& dir, const str_type& file_suffix) {
	list<str_type> ret;
	for (const auto& entry : std::filesystem::directory_iterator(dir)) {
		const auto& path = entry.path();
		const auto& extension = path.extension();
		if (extension == file_suffix) {
			ret.push_back(path.filename().stem().u8string());
		}
	}
	return ret;
}

list<str_type> FileIO::search_directory_full(const str_type& dir, const str_type& file_suffix) {
	list<str_type> ret;
	for (const auto& entry : std::filesystem::directory_iterator(dir)) {
		const auto& path = entry.path();
		const auto& extension = path.extension();
		if (extension == file_suffix) {
			ret.push_back(path.u8string());
		}
	}
	return ret;
}
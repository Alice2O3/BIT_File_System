#include "FileIO.h"
#include <fstream>
#include <filesystem>

template<typename T>
std::unique_ptr<T> FileIO::read_file(const str_type& file_path) {
	auto data = std::make_unique<T>();
	std::ifstream rf(file_path, std::ios::in | std::ios::binary);
	rf.read(reinterpret_cast<char*>(data.get()), sizeof(T));
	rf.close();
	return data;
}

template<typename T>
void FileIO::write_file(const std::unique_ptr<T>& data, const str_type& file_path) {
	std::ofstream wf(file_path, std::ios::out | std::ios::binary);
	wf.write(reinterpret_cast<const char*>(data.get()), sizeof(T));
	wf.close();
}
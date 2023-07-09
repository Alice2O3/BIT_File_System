#ifndef FILEIO_H
#define FILEIO_H

#include "std_headers.h"
#include "data_macros.h"

class FileIO {
public:
	static void create_dir(const str_type& dir);
	static void delete_file(const str_type& file_path);
	static std::list<str_type> search_directory(const str_type& dir, const str_type& file_suffix);
	static std::list<str_type> search_directory_full(const str_type& dir, const str_type& file_suffix);
	// Template Functions
	template<typename T> static std::unique_ptr<T> read_file(const str_type& file_path);
	template<typename T> static void write_file(const std::unique_ptr<T>& data, const str_type& file_path);
};

#endif
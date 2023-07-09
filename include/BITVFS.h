#ifndef VIRTUALFILESYSTEM_H
#define VIRTUALFILESYSTEM_H

#include "std_headers.h"
#include "Data.h"
#include "IVirtualFileSystem.h"

class BITVFS : public IVirtualFileSystem {
private:
	std::unique_ptr<FileSystem_Data> data;
	str_type current_file_system;
	data_index current_file;
	inline bool is_opened();
	inline bool is_reading();
	inline bool length_exceeded(const str_type& name);
	data_index get_current_dir();
	data_index malloc_fcb();
	data_index malloc_fb();
	void push_dir(const data_index& dir_index);
	void pop_dir();
	str_type build_save_path(const str_type& file_name);
	str_type get_absolute_path();
public:
	// Construction Functions
	BITVFS();
	// FileSystem Operations
	vfs_err_code create_file_system(const str_type& filesystem_name) override;
	vfs_err_code open_file_system(const str_type& filesystem_name) override;
	vfs_err_code exit_file_system() override;
	vfs_err_code file_system_exists(const str_type& filesystem_name) override;
	vfs_err_code list_file_systems() override;
	vfs_err_code delete_file_system(const str_type& filesystem_name) override;
	vfs_err_code clear_file_systems() override;
	// Directory Operations
	vfs_err_code mkdir(const str_type& dir_name) override;
	vfs_err_code rmdir(const str_type& dir_name) override;
	vfs_err_code chdir(const str_type& dir_name) override;
	vfs_err_code ls() override;
	vfs_err_code pwd() override;
	vfs_err_code cd(const str_type& dir_name) override;
	// File Operations
	vfs_err_code create_file(const str_type& file_name) override;
	vfs_err_code open_file(const str_type& file_name) override;
	vfs_err_code close_file() override;
	vfs_err_code read_file() override;
	vfs_err_code write_file(const str_type& content) override;
	vfs_err_code delete_file(const str_type& file_name) override;
	// CMD Operations
	void cmd_init() override;
	str_type get_cmd_dir() override;
};

#endif
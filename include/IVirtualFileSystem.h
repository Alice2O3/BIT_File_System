#pragma once

#include "std_headers.h"
#include "data_macros.h"
#include "vfs_macros.h"

class IVirtualFileSystem {
public:
	// Construction Functions
	IVirtualFileSystem() = default;
	virtual ~IVirtualFileSystem() = default;
	IVirtualFileSystem(const IVirtualFileSystem& other) = delete;
	IVirtualFileSystem& operator = (const IVirtualFileSystem& other) = delete;
	IVirtualFileSystem(IVirtualFileSystem&& other) = delete;
	IVirtualFileSystem& operator = (IVirtualFileSystem&& other) = delete;
	// FileSystem Operations
	virtual vfs_err_code create_file_system(const str_type& filesystem_name) = 0;
	virtual vfs_err_code open_file_system(const str_type& filesystem_name) = 0;
	virtual vfs_err_code exit_file_system() = 0;
	virtual vfs_err_code file_system_exists(const str_type& filesystem_name) = 0;
	virtual vfs_err_code list_file_systems() = 0;
	virtual vfs_err_code delete_file_system(const str_type& filesystem_name) = 0;
	virtual vfs_err_code clear_file_systems() = 0;
	// Directory Operations
	virtual vfs_err_code mkdir(const str_type& dir_name) = 0;
	virtual vfs_err_code rmdir(const str_type& dir_name) = 0;
	virtual vfs_err_code chdir(const str_type& dir_name) = 0;
	virtual vfs_err_code ls() = 0;
	virtual vfs_err_code pwd() = 0;
	virtual vfs_err_code cd(const str_type& dir_name) = 0;
	// File Operations
	virtual vfs_err_code create_file(const str_type& file_name) = 0;
	virtual vfs_err_code open_file(const str_type& file_name) = 0;
	virtual vfs_err_code close_file() = 0;
	virtual vfs_err_code read_file() = 0;
	virtual vfs_err_code write_file(const str_type& content) = 0;
	virtual vfs_err_code delete_file(const str_type& file_name) = 0;
	// CMD Operations
	virtual void cmd_init() = 0;
	virtual str_type get_cmd_dir() = 0;
};

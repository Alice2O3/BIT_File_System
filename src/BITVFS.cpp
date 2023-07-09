#include "cmd_macros.h"
#include "BITVFS.h"
#include "Utils_Template.cpp"
#include "Logger_Template.cpp"
#include "FileIO_Template.cpp"

using namespace std;

// File systems
constexpr auto FILE_SAVE_PATH = "FileSystem";
constexpr auto FILE_SAVE_SUFFIX = ".bin";

// Labels
constexpr auto DIRECTORY_LABEL = "-";
constexpr auto FILE_LABEL = "*";

// Constructors
BITVFS::BITVFS() {
	current_file = NOT_READING;
}

// Private
inline bool BITVFS::is_opened() {
	return !current_file_system.empty();
}

inline bool BITVFS::is_reading() {
	return current_file != NOT_READING;
}

inline bool BITVFS::length_exceeded(const str_type& name) {
	return name.length() >= FCB_NAME_LENGTH;
}

data_index BITVFS::get_current_dir() {
	const auto& directory_list = data->fb_status.directory_list;
	const auto& top = directory_list[0];
	if (top == 0) {
		return 0;
	}
	return directory_list[top];
}

data_index BITVFS::malloc_fcb() {
	const auto& fcb_block = data->fcb_block;
	for (data_index i = 1; i < FILE_NUM; i++) {
		if (fcb_block[i].start_index == FCB_NOT_ALLOCATED) {
			return i;
		}
	}
	return FCB_NO_SPACE_LEFT;
}

data_index BITVFS::malloc_fb() {
	const auto& fb_allocation = data->fb_status.fb_allocation;
	for (data_index i = 1; i < FILE_NUM; i++) {
		if (fb_allocation[i] == FB_NOT_ALLOCATED) {
			return i;
		}
	}
	return FB_NO_SPACE_LEFT;
}

void BITVFS::push_dir(const data_index& dir_index) {
	auto& directory_list = data->fb_status.directory_list;
	auto& top = directory_list[0];
	top++;
	directory_list[top] = dir_index;
}

void BITVFS::pop_dir() {
	auto& directory_list = data->fb_status.directory_list;
	auto& top = directory_list[0];
	if (top > 0) {
		directory_list[top] = 0;
		top--;
	}
}

str_type BITVFS::build_save_path(const str_type& file_name) {
	return Utils::str_build(FILE_SAVE_PATH, "/", file_name, FILE_SAVE_SUFFIX);
}

str_type BITVFS::get_absolute_path() {
	const auto& fcb_block = data->fcb_block;
	str_type ret = Utils::str_build(VIRTUAL_ROOT_PATH, fcb_block[0].file_name);
	auto& directory_list = data->fb_status.directory_list;
	auto& top = directory_list[0];
	for (int i = 1; i <= top; i++) {
		ret += Utils::str_build(DIRECTORY_SLASH, fcb_block[directory_list[i]].file_name);
	}
	return ret;
}

// Public
vfs_err_code BITVFS::create_file_system(const str_type& filesystem_name) {
	if (is_opened()) {
		Logger::log_error("You must exit the current file system to create new file system!");
		return VFS_FILE_SYSTEM_OPENED;
	}
	if (length_exceeded(filesystem_name)) {
		Logger::log_error("File system name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	auto data = make_unique<FileSystem_Data>();
	auto& first_fcb = data->fcb_block[0];
	first_fcb.start_index = IS_DIRECTORY;
	Utils::str_copy_to_char(first_fcb.file_name, filesystem_name);
	FileIO::write_file(data, build_save_path(filesystem_name));
	Logger::log("Created new file system ", filesystem_name);
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::open_file_system(const str_type& filesystem_name) {
	if (is_opened()) {
		Logger::log_error("File system is already opened!");
		return VFS_FILE_SYSTEM_OPENED;
	}
	if (length_exceeded(filesystem_name)) {
		Logger::log_error("File system name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	for (const auto& e : FileIO::search_directory(FILE_SAVE_PATH, FILE_SAVE_SUFFIX)) {
		if (filesystem_name == e) {
			current_file_system = filesystem_name;
			data = FileIO::read_file<FileSystem_Data>(build_save_path(filesystem_name));
			Logger::log("Opened file system ", filesystem_name);
			return VFS_NO_ERR;
		}
	}
	Logger::log_error("File system ", filesystem_name, " not found!");
	return VFS_FILE_SYSTEM_DOES_NOT_EXIST;
}

vfs_err_code BITVFS::exit_file_system() {
	if (!is_opened()) {
		Logger::log_error("File system is already closed!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	str_type file_name = current_file_system;
	FileIO::write_file(data, build_save_path(file_name));
	data.release();
	current_file_system.clear();
	Logger::log("Exited file system ", file_name);
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::file_system_exists(const str_type& filesystem_name) {
	if (is_opened()) {
		Logger::log_error("You must exit the current file system to check file systems!");
		return VFS_FILE_SYSTEM_OPENED;
	}
	if (length_exceeded(filesystem_name)) {
		Logger::log_error("File system name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	for (const auto& e : FileIO::search_directory(FILE_SAVE_PATH, FILE_SAVE_SUFFIX)) {
		if (filesystem_name == e) {
			Logger::log("File system ", filesystem_name, " exists!");
			return VFS_NO_ERR;
		}
	}
	Logger::log_error("File system ", filesystem_name, " not found!");
	return VFS_FILE_SYSTEM_DOES_NOT_EXIST;
}

vfs_err_code BITVFS::list_file_systems() {
	if (is_opened()) {
		Logger::log_error("You must exit the current file system to list file systems!");
		return VFS_FILE_SYSTEM_OPENED;
	}
	Logger::log("List of file systems:");
	for (const auto& e : FileIO::search_directory(FILE_SAVE_PATH, FILE_SAVE_SUFFIX)) {
		Logger::log(e);
	}
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::delete_file_system(const str_type& filesystem_name) {
	if (is_opened()) {
		Logger::log_error("You must exit the current file system to delete file systems!");
		return VFS_FILE_SYSTEM_OPENED;
	}
	if (length_exceeded(filesystem_name)) {
		Logger::log_error("File system name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	for (const auto& e : FileIO::search_directory(FILE_SAVE_PATH, FILE_SAVE_SUFFIX)) {
		if (filesystem_name == e) {
			FileIO::delete_file(build_save_path(filesystem_name));
			Logger::log("Deleted file system ", filesystem_name);
			return VFS_NO_ERR;
		}
	}
	Logger::log_warning("File system ", filesystem_name, " not found, return");
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::clear_file_systems() {
	if (is_opened()) {
		Logger::log_error("You must exit the current file system to clear file systems!");
		return VFS_FILE_SYSTEM_OPENED;
	}
	for (const auto& e : FileIO::search_directory_full(FILE_SAVE_PATH, FILE_SAVE_SUFFIX)) {
		FileIO::delete_file(e);
	}
	Logger::log("File system cleared!");
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::mkdir(const str_type& dir_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run mkdir!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run mkdir!");
		return VFS_FILE_READING;
	}
	if (length_exceeded(dir_name)) {
		Logger::log_error("Directory name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	auto& fcb_block = data->fcb_block;
	// Check if directory exists
	{
		auto next_id = fcb_block[get_current_dir()].sub_fcb_index;
		while (next_id != 0) {
			const auto& next_fcb = fcb_block[next_id];
			if (next_fcb.start_index == IS_DIRECTORY && next_fcb.file_name == dir_name) {
				Logger::log_error("Directory ", dir_name, " exists!");
				return VFS_DIRECTORY_EXISTS;
			}
			next_id = next_fcb.next_fcb_index;
		}
	}
	// Create new directory
	{
		const auto& fcb_malloc_index = malloc_fcb();
		// Trying to allocate new fcb
		if (fcb_malloc_index == FCB_NO_SPACE_LEFT) {
			Logger::log_error("FCB no space left!");
			return VFS_FCB_NO_SPACE_LEFT;
		}
		// Initialize new node
		{
			auto& next_id = fcb_block[get_current_dir()].sub_fcb_index;
			auto& new_fcb = fcb_block[fcb_malloc_index];
			Utils::str_copy_to_char(new_fcb.file_name, dir_name);
			new_fcb.start_index = IS_DIRECTORY;
			new_fcb.next_fcb_index = next_id;
			next_id = fcb_malloc_index;
		}
		Logger::log("Created dir ", dir_name);
		return VFS_NO_ERR;
	}
}

vfs_err_code BITVFS::ls() {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run ls!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run ls!");
		return VFS_FILE_READING;
	}
	Logger::log("List of directories and files ('", DIRECTORY_LABEL, "': directory, '", FILE_LABEL, "': file):");
	const auto& fcb_block = data->fcb_block;
	auto next_id = fcb_block[get_current_dir()].sub_fcb_index;
	while (next_id != 0) {
		const auto& next_fcb = fcb_block[next_id];
		if (next_fcb.start_index == IS_DIRECTORY) {
			Logger::log(DIRECTORY_LABEL, " ", next_fcb.file_name);
		}
		else {
			Logger::log(FILE_LABEL, " ", next_fcb.file_name);
		}
		next_id = next_fcb.next_fcb_index;
	}
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::chdir(const str_type& dir_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run dir_exists!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run dir_exists!");
		return VFS_FILE_READING;
	}
	if (length_exceeded(dir_name)) {
		Logger::log_error("Directory name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	const auto& fcb_block = data->fcb_block;
	auto next_id = fcb_block[get_current_dir()].sub_fcb_index;
	while (next_id != 0) {
		const auto& next_fcb = fcb_block[next_id];
		if (next_fcb.start_index == IS_DIRECTORY && next_fcb.file_name == dir_name) {
			Logger::log("Directory ", dir_name, " exists!");
			return VFS_NO_ERR;
		}
		next_id = next_fcb.next_fcb_index;
	}
	Logger::log_error("Directory ", dir_name, " not found!");
	return VFS_DIRECTORY_DOES_NOT_EXIST;
}

vfs_err_code BITVFS::rmdir(const str_type& dir_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run rmdir!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run rmdir!");
		return VFS_FILE_READING;
	}
	if (length_exceeded(dir_name)) {
		Logger::log_error("Directory name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	auto& fcb_block = data->fcb_block;
	auto current_id = get_current_dir();
	auto next_id = fcb_block[current_id].sub_fcb_index;
	bool is_root_node = true;
	while (next_id != 0) {
		auto& next_fcb = fcb_block[next_id];
		if (next_fcb.start_index == IS_DIRECTORY && next_fcb.file_name == dir_name) {
			// Check if the directory is empty
			{
				if (next_fcb.sub_fcb_index != NO_SUBDIRECTORY) {
					Logger::log_error("Directory ", dir_name, " is not empty, can't remove");
					return VFS_DIRECTORY_NOT_EMPTY;
				}
			}
			// Remove the directory
			{
				if (is_root_node) {
					fcb_block[current_id].sub_fcb_index = next_fcb.next_fcb_index;
				}
				else {
					fcb_block[current_id].next_fcb_index = next_fcb.next_fcb_index;
				}
				// Remove fcb
				next_fcb = { 0 };
			}
			Logger::log("Directory ", dir_name, " removed!");
			return VFS_NO_ERR;
		}
		current_id = next_id;
		next_id = next_fcb.next_fcb_index;
		is_root_node = false;
	}
	Logger::log_error("Directory ", dir_name, " not found!");
	return VFS_DIRECTORY_DOES_NOT_EXIST;
}

vfs_err_code BITVFS::pwd() {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run pwd!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run pwd!");
		return VFS_FILE_READING;
	}
	Logger::log("Current dir: " + get_absolute_path());
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::cd(const str_type& dir_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run cd!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run cd!");
		return VFS_FILE_READING;
	}
	if (dir_name == PARENT_DIRECTORY) {
		pop_dir();
		goto label_ret;
	}
	else {
		if (length_exceeded(dir_name)) {
			Logger::log_error("File name length exceeded!");
			return VFS_FILE_NAME_EXCEEDED;
		}
		const auto& fcb_block = data->fcb_block;
		auto next_id = fcb_block[get_current_dir()].sub_fcb_index;
		while (next_id != 0) {
			const auto& next_fcb = fcb_block[next_id];
			if (next_fcb.start_index == IS_DIRECTORY && next_fcb.file_name == dir_name) {
				push_dir(next_id);
				goto label_ret;
			}
			next_id = next_fcb.next_fcb_index;
		}
		Logger::log_error("Directory ", dir_name, " not found!");
		return VFS_DIRECTORY_DOES_NOT_EXIST;
	}
label_ret:
	Logger::log("Move to ", get_absolute_path());
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::create_file(const str_type& file_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run create_file!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run create_file!");
		return VFS_FILE_READING;
	}
	auto& fcb_block = data->fcb_block;
	// Check if file exists
	{
		auto next_id = fcb_block[get_current_dir()].sub_fcb_index;
		while (next_id != 0) {
			const auto& next_fcb = fcb_block[next_id];
			if (next_fcb.start_index != IS_DIRECTORY && next_fcb.file_name == file_name) {
				Logger::log_error("File ", file_name, " exists!");
				return VFS_FILE_EXISTS;
			}
			next_id = next_fcb.next_fcb_index;
		}
	}
	// Create new file
	{
		// Try to malloc new fcb
		const auto& fcb_malloc_index = malloc_fcb();
		if (fcb_malloc_index == FCB_NO_SPACE_LEFT) {
			Logger::log_error("FCB no space left!");
			return VFS_FCB_NO_SPACE_LEFT;
		}
		// Try to malloc new fb
		const auto& fb_malloc_index = malloc_fb();
		if (fb_malloc_index == FB_NO_SPACE_LEFT) {
			Logger::log_error("FB no space left!");
			return VFS_FB_NO_SPACE_LEFT;
		}
		// Initialize new node
		{
			auto& next_id = fcb_block[get_current_dir()].sub_fcb_index;
			auto& new_fcb = fcb_block[fcb_malloc_index];
			Utils::str_copy_to_char(new_fcb.file_name, file_name);
			new_fcb.start_index = fb_malloc_index;
			new_fcb.next_fcb_index = next_id;
			next_id = fcb_malloc_index;
			// Allocate fb
			auto& fb_allocation = data->fb_status.fb_allocation;
			fb_allocation[0]++;
			fb_allocation[fb_malloc_index] = FB_ALLOCATED;
		}

		Logger::log("Created file ", file_name);
		return VFS_NO_ERR;
	}
}

vfs_err_code BITVFS::open_file(const str_type& file_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run open_file!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run open_file!");
		return VFS_FILE_READING;
	}
	if (length_exceeded(file_name)) {
		Logger::log_error("File name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	const auto& fcb_block = data->fcb_block;
	auto next_id = fcb_block[get_current_dir()].sub_fcb_index;
	while (next_id != 0) {
		const auto& next_fcb = fcb_block[next_id];
		if (next_fcb.start_index != IS_DIRECTORY && next_fcb.file_name == file_name) {
			current_file = next_id;
			Logger::log("Opened file ", file_name);
			return VFS_NO_ERR;
		}
		next_id = next_fcb.next_fcb_index;
	}
	Logger::log_error("File ", file_name, " not found!");
	return VFS_DIRECTORY_DOES_NOT_EXIST;
}

vfs_err_code BITVFS::read_file() {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run read_file!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (!is_reading()) {
		Logger::log_error("You must open the file to run read_file!");
		return VFS_FILE_READING;
	}
	const auto& current_fcb = data->fcb_block[current_file];
	const auto& current_fb = data->fb_block[current_fcb.start_index];
	const auto& file_size = current_fcb.file_size;
	Logger::log("Reading file ", current_fcb.file_name);
	Logger::log("File size: ", file_size);
	Logger::log("File content:");
	Logger::log(Utils::char_to_str(current_fb.content, file_size));
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::write_file(const str_type& content) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run write_file!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (!is_reading()) {
		Logger::log_error("You must open the file to run write_file!");
		return VFS_FILE_READING;
	}
	const data_size& content_length = content.length();
	auto& current_fcb = data->fcb_block[current_file];
	auto& current_fb = data->fb_block[current_fcb.start_index];
	auto& file_size = current_fcb.file_size;
	if (file_size + content_length > BLOCK_LENGTH) {
		Logger::log_error("File size exceeded!");
		return VFS_FILE_SIZE_EXCEEDED;
	}
	Logger::log("Writing file ", current_fcb.file_name);
	Utils::str_copy_to_char(current_fb.content + file_size, content);
	file_size += content_length;
	Logger::log("Writing complete!");
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::close_file() {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run close_file!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (!is_reading()) {
		Logger::log_error("You must open the file to run close_file!");
		return VFS_FILE_READING;
	}
	current_file = NOT_READING;
	return VFS_NO_ERR;
}

vfs_err_code BITVFS::delete_file(const str_type& file_name) {
	if (!is_opened()) {
		Logger::log_error("You must open the current file system to run delete_file!");
		return VFS_FILE_SYSTEM_CLOSED;
	}
	if (is_reading()) {
		Logger::log_error("You must exit the file to run delete_file!");
		return VFS_FILE_READING;
	}
	if (length_exceeded(file_name)) {
		Logger::log_error("Directory name length exceeded!");
		return VFS_FILE_NAME_EXCEEDED;
	}
	auto& fcb_block = data->fcb_block;
	auto current_id = get_current_dir();
	auto next_id = fcb_block[current_id].sub_fcb_index;
	bool is_root_node = true;
	while (next_id != 0) {
		auto& next_fcb = fcb_block[next_id];
		if (next_fcb.start_index != IS_DIRECTORY && next_fcb.file_name == file_name) {
			// Remove the file
			{
				if (is_root_node) {
					fcb_block[current_id].sub_fcb_index = next_fcb.next_fcb_index;
				}
				else {
					fcb_block[current_id].next_fcb_index = next_fcb.next_fcb_index;
				}
				// Remove fb data
				const auto& fb_index = next_fcb.start_index;
				data->fb_block[fb_index] = { 0 };
				// Remove fb allocation
				auto& fb_allocation = data->fb_status.fb_allocation;
				fb_allocation[fb_index] = FB_NOT_ALLOCATED;
				fb_allocation[0]--;
				// Remove fcb
				next_fcb = { 0 };
			}
			Logger::log("File ", file_name, " deleted!");
			return VFS_NO_ERR;
		}
		current_id = next_id;
		next_id = next_fcb.next_fcb_index;
		is_root_node = false;
	}
	Logger::log_error("File ", file_name, " not found!");
	return VFS_FILE_DOES_NOT_EXIST;
}

str_type BITVFS::get_cmd_dir() {
	if (!is_opened()) {
		return Utils::str_build(REAL_ROOT_PATH, CMD_CURSOR);
	}
	if (is_reading()) {
		return Utils::str_build(get_absolute_path(), DIRECTORY_SLASH, data->fcb_block[current_file].file_name, CMD_CURSOR);
	}
	return Utils::str_build(get_absolute_path(), CMD_CURSOR);
}

void BITVFS::cmd_init() {
	FileIO::create_dir(FILE_SAVE_PATH);
}
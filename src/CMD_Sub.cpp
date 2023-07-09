#include "CMD_Sub.h"
#include "Utils_Template.cpp"
#include "Logger_Template.cpp"

using namespace std;

// Static
cmd_map_type CMD::cmd_map = {
	{"help", make_shared<CMD_Sub_Help>()},
	{"quit", make_shared<CMD_Sub_Quit>()},
	{"new", make_shared<CMD_Sub_New>()},
	{"openfs", make_shared<CMD_Sub_Openfs>()},
	{"listfs", make_shared<CMD_Sub_Listfs>()},
	{"deletefs", make_shared<CMD_Sub_Deletefs>()},
	{"clearfs", make_shared<CMD_Sub_Clearfs>()},
	{"exit", make_shared<CMD_Sub_Exit>()},
	{"mkdir", make_shared<CMD_Sub_Mkdir>()},
	{"rmdir", make_shared<CMD_Sub_Rmdir>()},
	{"chdir", make_shared<CMD_Sub_Chdir>()},
	{"pwd", make_shared<CMD_Sub_Pwd>()},
	{"cd", make_shared<CMD_Sub_Cd>()},
	{"ls", make_shared<CMD_Sub_Ls>()},
	{"create", make_shared<CMD_Sub_Create>()},
	{"open", make_shared<CMD_Sub_Open>()},
	{"close", make_shared<CMD_Sub_Close>()},
	{"read", make_shared<CMD_Sub_Read>()},
	{"write", make_shared<CMD_Sub_Write>()},
	{"delete", make_shared<CMD_Sub_Delete>()}
};

// Base
const str_type& CMD_Sub_Base::get_help_message() {
	return help_message;
}

const cmd_message_list& CMD_Sub_Base::get_usage_list() {
	return usage_list;
}

// Help
CMD_Sub_Help::CMD_Sub_Help() {
	help_message = "Show the usage of a command";
	usage_list = { 
		{ "help", "Show the list of all commands" },
		{ "help <command>", "Show the usage of <command>" }
	};
}

cmd_code CMD_Sub_Help::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		Logger::log();
		Logger::log("List of commands:");
		Logger::log();
		for (const auto& e : CMD::cmd_map) {
			Logger::log(Utils::str_left_padding(e.first, CMD_HELP_PADDING_LEN, CHAR_SPACE), " ", e.second->get_help_message());
		}
		return CMD_NO_ERR;
	}
	break;
	case 2:
	{
		const auto& help_command = args[1];
		const auto& it = CMD::cmd_map.find(help_command);
		if (it == CMD::cmd_map.end()) {
			Logger::log("Command \"", help_command, "\" not found. Run \"help\" for more instructions.");
			return CMD_PARSE_ERROR;
		}
		Logger::log();
		Logger::log("Usage of \"", help_command, "\":");
		Logger::log();
		for (const auto& e : it->second->get_usage_list()) {
			Logger::log(Utils::str_left_padding(e.first, CMD_USAGE_PADDING_LEN, CHAR_SPACE), e.second);
		}
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Quit
CMD_Sub_Quit::CMD_Sub_Quit() {
	help_message = "Quit the whole program";
	usage_list = { 
		{ "quit" , "Quit the whole program" }
	};
}

cmd_code CMD_Sub_Quit::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		Logger::log("Program exited!");
		return CMD_QUIT;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// New
CMD_Sub_New::CMD_Sub_New() {
	help_message = "Create new file system";
	usage_list = { 
		{ "new <filesystem>", "Create new file system <filesystem>" }
	};
}

cmd_code CMD_Sub_New::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->create_file_system(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Openfs
CMD_Sub_Openfs::CMD_Sub_Openfs() {
	help_message = "Open existing file system";
	usage_list = {
		{ "openfs <filesystem>", "Open the file system <filesystem>" }
	};
}

cmd_code CMD_Sub_Openfs::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->open_file_system(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Listfs
CMD_Sub_Listfs::CMD_Sub_Listfs() {
	help_message = "List the existing file systems";
	usage_list = {
		{ "listfs", "List the existing file systems" }
	};
}

cmd_code CMD_Sub_Listfs::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->list_file_systems();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Deletefs
CMD_Sub_Deletefs::CMD_Sub_Deletefs() {
	help_message = "Delete the existing file system";
	usage_list = {
		{ "deletefs <filesystem>", "Delete the existing file system named <filesystem>" }
	};
}

cmd_code CMD_Sub_Deletefs::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->delete_file_system(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Clearfs
CMD_Sub_Clearfs::CMD_Sub_Clearfs() {
	help_message = "Clear the file systems";
	usage_list = {
		{ "clearfs", "Clear the file systems" }
	};
}

cmd_code CMD_Sub_Clearfs::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->clear_file_systems();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Exit
CMD_Sub_Exit::CMD_Sub_Exit() {
	help_message = "Exit the opened file system";
	usage_list = {
		{ "exit", "Exit the opened file system" }
	};
}

cmd_code CMD_Sub_Exit::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->exit_file_system();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Mkdir
CMD_Sub_Mkdir::CMD_Sub_Mkdir() {
	help_message = "Create new directory";
	usage_list = {
		{ "mkdir <dir>", "Create new directory named <dir> at current dir" }
	};
}

cmd_code CMD_Sub_Mkdir::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->mkdir(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Rmdir
CMD_Sub_Rmdir::CMD_Sub_Rmdir() {
	help_message = "Delete the directory";
	usage_list = {
		{ "rmdir <dir>", "Delete the directory named <dir> if it is empty" }
	};
}

cmd_code CMD_Sub_Rmdir::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->rmdir(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Chdir
CMD_Sub_Chdir::CMD_Sub_Chdir() {
	help_message = "Check if directory exists";
	usage_list = {
		{ "chdir <dir>", "Check if directory named <dir> exists at the current dir" }
	};
}

cmd_code CMD_Sub_Chdir::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->chdir(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Pwd
CMD_Sub_Pwd::CMD_Sub_Pwd() {
	help_message = "Show the current working directory";
	usage_list = {
		{ "pwd", "Show the current working directory" }
	};
}

cmd_code CMD_Sub_Pwd::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->pwd();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Cd
CMD_Sub_Cd::CMD_Sub_Cd() {
	help_message = "Change the current directory";
	usage_list = {
		{ "cd <dir>", "Change the current directory to <dir> relative to current dir" },
		{ Utils::str_build("cd ", PARENT_DIRECTORY), "Return to parent directory relative to current dir" }
	};
}

cmd_code CMD_Sub_Cd::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->cd(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Ls
CMD_Sub_Ls::CMD_Sub_Ls() {
	help_message = "List the files and directories at current dir";
	usage_list = {
		{ "ls", "List the files and directories at current dir" }
	};
}

cmd_code CMD_Sub_Ls::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->ls();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Create
CMD_Sub_Create::CMD_Sub_Create() {
	help_message = "Create the new file";
	usage_list = {
		{ "create <file>", "Create new file named <file> at the current dir" }
	};
}

cmd_code CMD_Sub_Create::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->create_file(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Open
CMD_Sub_Open::CMD_Sub_Open() {
	help_message = "Open the existing file";
	usage_list = {
		{ "open <file>", "Open the existing file named <file> at the current dir" }
	};
}

cmd_code CMD_Sub_Open::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->open_file(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Close
CMD_Sub_Close::CMD_Sub_Close() {
	help_message = "Close the existing file";
	usage_list = {
		{ "close", "Close the opened file" }
	};
}

cmd_code CMD_Sub_Close::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->close_file();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Read
CMD_Sub_Read::CMD_Sub_Read() {
	help_message = "Read the opened file";
	usage_list = {
		{ "read", "Read the opened file" }
	};
}

cmd_code CMD_Sub_Read::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 1:
	{
		vfs->read_file();
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Write
CMD_Sub_Write::CMD_Sub_Write() {
	help_message = "Write the opened file";
	usage_list = {
		{ "write <message>", "Write the opened file at the end with <message>" }
	};
}

cmd_code CMD_Sub_Write::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->write_file(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}

// Delete
CMD_Sub_Delete::CMD_Sub_Delete() {
	help_message = "Delete the existing file";
	usage_list = {
		{ "delete <file>", "Delete the existing file named <file> at the current dir" }
	};
}

cmd_code CMD_Sub_Delete::execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) {
	switch (args_num) {
	case 2:
	{
		vfs->delete_file(args[1]);
		return CMD_NO_ERR;
	}
	break;
	default:
	{
		return CMD_INVALID_ARGS;
	}
	}
}
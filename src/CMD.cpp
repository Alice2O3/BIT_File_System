#include "CMD.h"
#include "CMD_Sub.h"
#include "Utils_Template.cpp"
#include "Logger_Template.cpp"
#include "FileIO_Template.cpp"
#include <iostream>

using namespace std;

// Constructor
CMD::CMD(std::unique_ptr<IVirtualFileSystem> vfs_) {
	vfs = move(vfs_);
}

// Private
vector<str_type> CMD::arg_split(const str_type& str) {
	vector<str_type> res;
	str_type tmp;
	bool flag = false;
	for (const auto& ch : str) {
		if (ch == CHAR_SPACE) {
			if (flag == true) {
				res.push_back(tmp);
				tmp.clear();
				flag = false;
			}
		}
		else {
			if (flag == false) {
				flag = true;
			}
			tmp += ch;
		}
	}
	if (flag == true) {
		res.push_back(tmp);
	}
	return res;
}

cmd_code CMD::processCMD(const str_type& command) {
	const auto& args = arg_split(command);
	const auto& num = args.size();
	if (num == 0) {
		return CMD_SKIP;
	}
	const auto& op = args[0];
	const auto& it = CMD::cmd_map.find(op);
	if (it == CMD::cmd_map.end()) {
		// Invalid command
		Logger::log("Invalid command \"", op, "\". Run \"help\" for more instructions.");
		return CMD_INVALID_COMMAND;
	}
	// Execute command
	const auto& ret = it->second->execute(vfs, args, args.size());
	if (ret == CMD_INVALID_ARGS) {
		Logger::log("Command \"", op, "\" has invalid arguments. Run \"help ", op, "\" for more instructions.");
	}
	return ret;
}

// Public
void CMD::run() {
	vfs->cmd_init();
	str_type command;
	while (true) {
		Logger::put(vfs->get_cmd_dir());
		getline(cin, command);
		if(processCMD(command) == CMD_QUIT){
			return;
		}
		Logger::log();
	}
}
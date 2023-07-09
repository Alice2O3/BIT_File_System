#ifndef CMD_H
#define CMD_H

#include "std_headers.h"
#include "cmd_macros.h"
#include "IVirtualFileSystem.h"

class CMD {
private:
	std::unique_ptr<IVirtualFileSystem> vfs;
	std::vector<str_type> arg_split(const str_type& str);
	cmd_code processCMD(const str_type& command);
public:
	static cmd_map_type cmd_map;
	// Construction Functions
	CMD() = delete;
	CMD(std::unique_ptr<IVirtualFileSystem> vfs_);
	virtual ~CMD() = default;
	CMD(const CMD& other) = delete;
	CMD& operator = (const CMD& other) = delete;
	CMD(CMD&& other) = delete;
	CMD& operator = (CMD&& other) = delete;
	// Member Functions
	void run();
};

#endif
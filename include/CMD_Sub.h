#ifndef CMD_SUB_H
#define CMD_SUB_H

#include "std_headers.h"
#include "CMD.h"

class CMD_Sub_Base {
protected:
	str_type help_message;
	cmd_message_list usage_list;
public:
	// Construction Functions
	CMD_Sub_Base() = default;
	virtual ~CMD_Sub_Base() = default;
	CMD_Sub_Base(const CMD_Sub_Base& other) = delete;
	CMD_Sub_Base& operator = (const CMD_Sub_Base& other) = delete;
	CMD_Sub_Base(CMD_Sub_Base&& other) = delete;
	CMD_Sub_Base& operator = (CMD_Sub_Base&& other) = delete;
	// Member Fuctions
	const str_type& get_help_message();
	const cmd_message_list& get_usage_list();
	virtual cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) = 0;
};

class CMD_Sub_Help : public CMD_Sub_Base {
public:
	CMD_Sub_Help();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Quit : public CMD_Sub_Base {
public:
	CMD_Sub_Quit();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_New : public CMD_Sub_Base {
public:
	CMD_Sub_New();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Openfs : public CMD_Sub_Base {
public:
	CMD_Sub_Openfs();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Listfs : public CMD_Sub_Base {
public:
	CMD_Sub_Listfs();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Deletefs : public CMD_Sub_Base {
public:
	CMD_Sub_Deletefs();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Clearfs : public CMD_Sub_Base {
public:
	CMD_Sub_Clearfs();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Exit : public CMD_Sub_Base {
public:
	CMD_Sub_Exit();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Mkdir : public CMD_Sub_Base {
public:
	CMD_Sub_Mkdir();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Rmdir : public CMD_Sub_Base {
public:
	CMD_Sub_Rmdir();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Chdir : public CMD_Sub_Base {
public:
	CMD_Sub_Chdir();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Pwd : public CMD_Sub_Base {
public:
	CMD_Sub_Pwd();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Cd : public CMD_Sub_Base {
public:
	CMD_Sub_Cd();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Ls : public CMD_Sub_Base {
public:
	CMD_Sub_Ls();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Create : public CMD_Sub_Base {
public:
	CMD_Sub_Create();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Open : public CMD_Sub_Base {
public:
	CMD_Sub_Open();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Close : public CMD_Sub_Base {
public:
	CMD_Sub_Close();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Read : public CMD_Sub_Base {
public:
	CMD_Sub_Read();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Write : public CMD_Sub_Base {
public:
	CMD_Sub_Write();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

class CMD_Sub_Delete : public CMD_Sub_Base {
public:
	CMD_Sub_Delete();
	cmd_code execute(const std::unique_ptr<IVirtualFileSystem>& vfs, const cmd_args_type& args, const size_t& args_num) override;
};

#endif
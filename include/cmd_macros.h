#pragma once

#include "data_macros.h"

class CMD_Sub_Base;
class CMD;

using cmd_map_type = std::map<str_type, std::shared_ptr<CMD_Sub_Base>>;
using cmd_args_type = std::vector<str_type>;
using cmd_argnum_list = std::vector<size_t>;
using cmd_message_pair = std::pair<str_type, str_type>;
using cmd_message_list = std::vector<cmd_message_pair>;
using cmd_code = unsigned int;

// CMD code
constexpr cmd_code CMD_NO_ERR = 0x0;
constexpr cmd_code CMD_QUIT = 0x1;
constexpr cmd_code CMD_SKIP = 0x2;
constexpr cmd_code CMD_INVALID_ARGS = 0x3;
constexpr cmd_code CMD_INVALID_COMMAND = 0x4;
constexpr cmd_code CMD_PARSE_ERROR = 0x5;

constexpr size_t CMD_HELP_PADDING_LEN = 8;
constexpr size_t CMD_USAGE_PADDING_LEN = 24;

// CMD systems
constexpr auto REAL_ROOT_PATH = "R:/";
constexpr auto VIRTUAL_ROOT_PATH = "V:/";
constexpr auto CMD_CURSOR = ">";
constexpr auto DIRECTORY_SLASH = "/";
constexpr auto PARENT_DIRECTORY = "..";

// CHARACTERS
constexpr auto CHAR_SPACE = ' ';

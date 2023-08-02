#pragma once

#include "data_macros.h"

// FCB state
constexpr data_index IS_DIRECTORY = 65535;
constexpr data_index NO_SUBDIRECTORY = 0;
constexpr data_index NO_NEXT = 0;

// FB state
constexpr data_index NOT_READING = 0;

// FCB allocation
constexpr data_index FCB_NOT_ALLOCATED = 0;
constexpr data_index FCB_NO_SPACE_LEFT = 65535;

// FB allocation
constexpr data_index FB_NOT_ALLOCATED = 0;
constexpr data_index FB_ALLOCATED = 1;
constexpr data_index FB_NO_SPACE_LEFT = 65535;

// FileSystem arguments
constexpr data_size FCB_LENGTH = 32;
constexpr data_size BLOCK_LENGTH = 1024;
constexpr data_size FILE_NUM = 1024;

// Data sizes
constexpr data_size INDEX_SIZE = sizeof(data_index);
constexpr data_size DATA_SIZE = sizeof(data_size);
constexpr data_size BLOCK_SIZE = BLOCK_LENGTH * sizeof(data_type);
constexpr data_size FCB_SIZE = FCB_LENGTH * sizeof(data_type);
constexpr data_size FCB_NAME_LENGTH = (FCB_SIZE - INDEX_SIZE * 3 - DATA_SIZE) / sizeof(data_type);
constexpr data_size FB_STATUS_SIZE = 2 * INDEX_SIZE * FILE_NUM;
constexpr data_size FILESYSTEM_DATA_SIZE = FB_STATUS_SIZE + (FCB_SIZE + BLOCK_SIZE) * FILE_NUM;

// Structs
struct FCB {
	//8B
	data_size file_size;
	//2B
	data_index start_index; //65535: IS_DIRECTORY
	//2B
	data_index sub_fcb_index; //0: NO_SUBDIRECTORY
	//2B
	data_index next_fcb_index; //0: NO_NEXT
	//18B
	data_type file_name[FCB_NAME_LENGTH];
};

struct FB {
	//BLOCK_SIZE B
	data_type content[BLOCK_LENGTH];
};

struct FB_Status {
	data_index directory_list[FILE_NUM]; //directory_list[0]: top
	data_index fb_allocation[FILE_NUM]; //fb_block[0]: num
};

struct FileSystem_Data {
	//FCB_SIZE * FILE_NUM B
	FCB fcb_block[FILE_NUM];
	//FB_STATUS_SIZE B
	FB_Status fb_status;
	//BLOCK_SIZE * FILE_NUM B
	FB fb_block[FILE_NUM];
};

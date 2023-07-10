#pragma once

using vfs_err_code = unsigned int;

constexpr vfs_err_code VFS_NO_ERR = 0x0;
constexpr vfs_err_code VFS_FILE_SYSTEM_OPENED = 0x1;
constexpr vfs_err_code VFS_FILE_SYSTEM_CLOSED = 0x2;
constexpr vfs_err_code VFS_FILE_SYSTEM_DOES_NOT_EXIST = 0x3;
constexpr vfs_err_code VFS_FILE_NAME_EXCEEDED = 0x4;
constexpr vfs_err_code VFS_FCB_NO_SPACE_LEFT = 0x5;
constexpr vfs_err_code VFS_DIRECTORY_EXISTS = 0x6;
constexpr vfs_err_code VFS_DIRECTORY_DOES_NOT_EXIST = 0x7;
constexpr vfs_err_code VFS_DIRECTORY_NOT_EMPTY = 0x8;
constexpr vfs_err_code VFS_FB_NO_SPACE_LEFT = 0x9;
constexpr vfs_err_code VFS_FILE_READING = 0xA;
constexpr vfs_err_code VFS_FILE_NOT_READING = 0xB;
constexpr vfs_err_code VFS_FILE_EXISTS = 0xC;
constexpr vfs_err_code VFS_FILE_DOES_NOT_EXIST = 0xD;
constexpr vfs_err_code VFS_FILE_SIZE_EXCEEDED = 0xE;

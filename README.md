# BIT_File_System

## 简介

BIT2023年软件工程“操作系统与分布式计算”实验四

## 要求

在内存中开辟一个虚拟磁盘空间作为文件存储器，在其上实现一个简单的单用户文件系统。在退出这个简单的文件系统时，将该虚拟文件系统保存到磁盘上，以便下次再将它恢复到内存的虚拟磁盘空间中。

## 开发平台

Windows/Linux

处理器架构：x64

## 开发语言/工具链

- C++17
- Visual Studio 2019
- CMake

## 安装步骤

### Windows

1. 运行`git clone https://github.com/Alice2O3/BIT_File_System.git`拉取源码；
2. 打开Visual Studio 2019；
3. 选择“打开本地文件夹”，打开本源码；
4. 切换到`main`文件夹下的`BIT_VFS.cpp`，并选择`调试/开始调试`；
5. 生成后的`BIT_VFS.exe`存放于`run`文件夹下，放到任意位置直接点击运行即可；

### Linux

依次执行以下命令：

```
sudo apt-get install git cmake build-essential
git clone https://github.com/Alice2O3/BIT_File_System.git
cd BIT_File_System
cmake .
make BIT_VFS
cd run
./BIT_VFS
```

生成后的`BIT_VFS`存放于`run`文件夹下，放到任意位置直接执行`./BIT_VFS`即可；

## 操作说明

仿照命令行的使用方式即可，提供以下操作：

- `help`：查询命令列表及用法；
- `quit`：退出程序；
- `new`：建立一个新的简单文件系统；
- `openfs`：打开一个简单文件系统；
- `listfs`：列出当前的文件系统；
- `deletefs`：删除指定的文件系统；
- `clearfs`：清除所有的文件系统；
- `exit`：退出打开的简单文件系统；
- `mkdir`：创建子目录；
- `rmdir`：删除子目录；
- `chdir`：检测子目录是否存在；
- `pwd`：显示当前目录；
- `cd`：更改当前目录；
- `ls`：显示当前目录下所有目录/文件；
- `create`：创建文件；
- `open`：打开文件；
- `close`：关闭文件；
- `read`：读文件；
- `write`：写文件；
- `delete`：删除文件；

当选择创建文件系统时，该程序会在运行目录下创建`FileSystem`目录，并创建后缀名为`.bin`的文件，代表该程序创建的虚拟文件系统。

## 虚拟文件系统参数

本虚拟文件系统采用较为简单的架构，虚拟文件系统采用固定大小，文件块固定大小紧凑分布，每个文件块和文件一一对应，且每个文件对应一个FCB，FCB采用孩子-兄弟法存储，同时专门开辟一块“磁盘状态记录”空间，用于存储当前所在目录以及磁盘块占用信息。

- 虚拟系统总大小：`1085440 B`
- 单个FCB大小：`32 B`
- 文件系统名/文件名最长长度：`18`
- 磁盘状态记录大小：`4096 B`
- 单个文件块大小：`1024 B`
- 文件块个数：`1024`
- 文件最大大小：`1024 B`
- 最多支持文件数：`1023`（第0个文件块以及FCB用于保留）

------------------------------------------------------------------------------------------------------------

I would like to kindly request that my code uploaded to Github not be redistributed to any other platform or social media without my permission.

Furthermore, I do not authorize the use of my code in any form of AI program.

Thanks!

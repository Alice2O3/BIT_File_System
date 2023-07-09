#include "Logger.h"
#include <iostream>

template<typename ...Ts>
void Logger::log_private(const Ts& ...args) {
	(std::cout << ... << args) << std::endl;
}

template<typename ...Ts>
void Logger::put(const Ts& ...args) {
	(std::cout << ... << args);
}

template<typename ...Ts>
void Logger::log(const Ts& ...args) {
	log_private(args...);
}

template<typename ...Ts>
void Logger::log_warning(const Ts& ...args) {
	log_private("[WARNING] ", args...);
}

template<typename ...Ts>
void Logger::log_error(const Ts& ...args) {
	log_private("[ERROR] ", args...);
}
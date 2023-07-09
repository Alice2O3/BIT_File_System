#ifndef LOGGER_H
#define LOGGER_H

#include "std_headers.h"

class Logger {
private:
	template<typename... Ts> static void log_private(const Ts& ...args);
public:
	template<typename... Ts> static void put(const Ts& ...args);
	template<typename... Ts> static void log(const Ts& ...args);
	template<typename... Ts> static void log_warning(const Ts& ...args);
	template<typename... Ts> static void log_error(const Ts& ...args);
};

#endif
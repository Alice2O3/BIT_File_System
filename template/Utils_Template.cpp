#pragma once

#include "Utils.h"

template<typename ...Ts>
str_type Utils::str_build(const Ts& ...args)
{
    std::stringstream ss;
    (ss << ... << args);
    return ss.str();
}
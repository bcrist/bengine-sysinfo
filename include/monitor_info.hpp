#pragma once
#ifndef BE_SYSINFO_MONITOR_INFO_HPP_
#define BE_SYSINFO_MONITOR_INFO_HPP_

#include <be/platform/glfw.hpp>

void log_all_monitor_info();
void log_monitor_info(GLFWmonitor* monitor, int index);

#endif

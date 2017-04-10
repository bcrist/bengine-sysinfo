#pragma once
#ifndef BE_SYSINFO_VERSION_HPP_
#define BE_SYSINFO_VERSION_HPP_

#include <be/core/macros.hpp>

#define BE_SYSINFO_VERSION_MAJOR 0
#define BE_SYSINFO_VERSION_MINOR 1
#define BE_SYSINFO_VERSION_REV 2

/*!! include('common/version', 'BE_SYSINFO', 'sysinfo') !! 6 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#define BE_SYSINFO_VERSION (BE_SYSINFO_VERSION_MAJOR * 100000 + BE_SYSINFO_VERSION_MINOR * 1000 + BE_SYSINFO_VERSION_REV)
#define BE_SYSINFO_VERSION_STRING "sysinfo " BE_STRINGIFY(BE_SYSINFO_VERSION_MAJOR) "." BE_STRINGIFY(BE_SYSINFO_VERSION_MINOR) "." BE_STRINGIFY(BE_SYSINFO_VERSION_REV)

/* ######################### END OF GENERATED CODE ######################### */

#endif

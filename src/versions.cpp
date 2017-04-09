#include "versions.hpp"
#include "version.hpp"
#include <be/core/version.hpp>
#include <be/util/version.hpp>
#include <be/platform/version.hpp>
#include <be/sqlite/version.hpp>
#include <be/gfx/version.hpp>
#include <be/ctable/version.hpp>
#include <be/cli/version.hpp>
#include <be/blt/version.hpp>
#include <be/belua/version.hpp>
#include <be/core/logging.hpp>
#include <GLFW/glfw3.h>
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <glm/glm.hpp>
#include <glbinding/glbinding-version.h>
#include <globjects/globjects-version.h>
#include <zlib/zlib.h>
#include <lua/lua.h>
#include <sqlite3.h>

using namespace be;

void log_versions() {
   be_info() << "Versions"
      & attr("sysinfo") << (BE_SYSINFO_VERSION_STRING)
      & attr("bengine") << (BE_CORE_VERSION_STRING)
      & attr("be::util") << (BE_UTIL_VERSION_STRING)
      & attr("be::cli") << (BE_CLI_VERSION_STRING)
      & attr("be::ctable") << (BE_CTABLE_VERSION_STRING)
      & attr("be::blt") << (BE_BLT_VERSION_STRING)
      & attr("be::belua") << (BE_BELUA_VERSION_STRING)
      & attr("be::sqlite") << (BE_SQLITE_VERSION_STRING)
      & attr("be::gfx") << (BE_GFX_VERSION_STRING)
      & attr("be::platform") << (BE_PLATFORM_VERSION_STRING)
      & attr("Compiler") << BOOST_COMPILER
      & attr("OS") << os_version()
      & attr("Boost") << (BOOST_VERSION / 100000) << '.' << (BOOST_VERSION / 100 % 1000) << '.' << (BOOST_VERSION % 100)
      & attr("GLFW") << glfwGetVersionString()
      & attr("glbinding") << GLBINDING_VERSION << '(' << GLBINDING_VERSION_REVISION << ')'
      & attr("globjects") << GLOBJECTS_VERSION << '(' << GLOBJECTS_VERSION_REVISION << ')'
      & attr("GLM") << GLM_VERSION_MAJOR << '.' << GLM_VERSION_MINOR << '.' << GLM_VERSION_PATCH << '.' << GLM_VERSION_REVISION
      & attr("zlib") << ZLIB_VERSION
      & attr("SQLite") << SQLITE_VERSION
      & attr("Lua") << LUA_RELEASE
      | default_log();
}

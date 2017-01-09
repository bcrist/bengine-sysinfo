#include "versions.hpp"
#include <be/core/logging.hpp>
#include <GLFW/glfw3.h>
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <glm/glm.hpp>
#include <zlib/zlib.h>
#include <lua/lua.h>

using namespace be;

void log_versions() {
   be_info() << "Versions"
      & attr("Compiler") << BOOST_COMPILER
      & attr("OS") << os_version()
      & attr("Boost") << (BOOST_VERSION / 100000) << '.' << (BOOST_VERSION / 100 % 1000) << '.' << (BOOST_VERSION % 100)
      & attr("GLM") << GLM_VERSION_MAJOR << '.' << GLM_VERSION_MINOR << '.' << GLM_VERSION_PATCH << '.' << GLM_VERSION_REVISION
      & attr("zlib") << ZLIB_VERSION
      & attr("GLFW") << glfwGetVersionString()
      & attr("Lua") << LUA_RELEASE
      | default_log();
}

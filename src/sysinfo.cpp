#include "versions.hpp"
#include "memory_status.hpp"
#include "monitor_info.hpp"

#include <be/core/lifecycle.hpp>
#include <be/core/logging.hpp>
#include <be/platform/lifecycle.hpp>

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
   BE_IGNORE2(argc, argv);

   be::CoreInitLifecycle init;
   be::default_log().verbosity_mask(be::v::verbose_or_worse);
   be::PlatformLifecycle platform;
   be::CoreLifecycle core;

   log_versions();
   log_memory_status();
   log_all_monitor_info();

   log_memory_status();

   return 0;
}

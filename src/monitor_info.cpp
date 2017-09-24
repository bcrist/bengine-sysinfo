#include "monitor_info.hpp"
#include <be/core/logging.hpp>
#include BE_NATIVE(platform, glfw.hpp)
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <iomanip>

using namespace be;

///////////////////////////////////////////////////////////////////////////////
void log_all_monitor_info() {
   int monitor_count;
   GLFWmonitor** monitors =  glfwGetMonitors(&monitor_count);

   be_short_info() << monitor_count << " Monitors Detected." | default_log();

   for (int i = 0; i < monitor_count; ++i) {
      GLFWmonitor* monitor = monitors[i];
      log_monitor_info(monitor, i);
   }
}

///////////////////////////////////////////////////////////////////////////////
using RefreshRateCon = std::vector<int>;
struct ModeInfo {
   glm::ivec2 dim;
   glm::ivec3 bits;
   RefreshRateCon refresh_rates;
};

///////////////////////////////////////////////////////////////////////////////
bool operator<(const ModeInfo& a, const ModeInfo& b) {
   if (a.dim.x != b.dim.x) {
      return a.dim.x < b.dim.x;
   }

   if (a.dim.y != b.dim.y) {
      return a.dim.y < b.dim.y;
   }

   int acolor = a.bits.r + a.bits.g + a.bits.b;
   int bcolor = b.bits.r + b.bits.g + b.bits.b;

   if (acolor != bcolor) {
      return acolor < bcolor;
   }

   if (a.bits.r < b.bits.r) {
      return a.bits.r < b.bits.r;
   }

   if (a.bits.g < b.bits.g) {
      return a.bits.g < b.bits.g;
   }

   if (a.bits.b < b.bits.b) {
      return a.bits.b < b.bits.b;
   }

   return false;
}

///////////////////////////////////////////////////////////////////////////////
std::vector<ModeInfo> get_modes(GLFWmonitor* monitor, RefreshRateCon& all_refresh_rates) {
   std::vector<ModeInfo> all_modes;
   int mode_count;
   const GLFWvidmode* modes = glfwGetVideoModes(monitor, &mode_count);
   for (int i = 0; i < mode_count; ++i) {
      ModeInfo info;
      info.dim.x = modes[i].width;
      info.dim.y = modes[i].height;

      info.bits.r = modes[i].redBits;
      info.bits.g = modes[i].greenBits;
      info.bits.b = modes[i].blueBits;

      bool found = false;
      for (ModeInfo& mode : all_modes) {
         if (mode.dim == info.dim && mode.bits == info.bits) {
            found = true;
            mode.refresh_rates.push_back(modes[i].refreshRate);
            std::sort(mode.refresh_rates.begin(), mode.refresh_rates.end());
            break;
         }
      }

      if (!found) {
         info.refresh_rates.push_back(modes[i].refreshRate);
         all_modes.push_back(std::move(info));
      }

      auto it = std::find(all_refresh_rates.begin(), all_refresh_rates.end(), modes[i].refreshRate);
      if (it == all_refresh_rates.end()) {
         all_refresh_rates.push_back(modes[i].refreshRate);
      }
   }
   std::sort(all_modes.begin(), all_modes.end());
   return all_modes;
}

///////////////////////////////////////////////////////////////////////////////
void log_monitor_info(GLFWmonitor* monitor, int index) {
   glm::ivec2 pos;
   glfwGetMonitorPos(monitor, &pos.x, &pos.y);

   glm::ivec2 dim;
   glfwGetMonitorPhysicalSize(monitor, &dim.x, &dim.y);

   RefreshRateCon all_refresh_rates;
   std::vector<ModeInfo> modes = get_modes(monitor, all_refresh_rates);
   std::sort(all_refresh_rates.begin(), all_refresh_rates.end());

   be_info() << "Monitor #" << index << (index == 0 ? " (Primary)" : "")
      & attr("Name") << S(glfwGetMonitorName(monitor))
      & attr("Monitor") << S(glfwGetWin32Monitor(monitor))
      & attr("Adapter") << S(glfwGetWin32Adapter(monitor))
      & attr("Position") << '(' << pos.x << ", " << pos.y << ')'
      & attr("Size") << dim.x << " mm x " << dim.y << " mm"
      | default_log();

   const GLFWvidmode* current = glfwGetVideoMode(monitor);

   for (ModeInfo& mode : modes) {
      using namespace color;

      bool is_current = !!current
         && mode.dim.x == current->width
         && mode.dim.y == current->height
         && mode.bits.r == current->redBits
         && mode.bits.g == current->greenBits
         && mode.bits.b == current->blueBits;

      LogRecord rec;
      auto mode_color = is_current ? yellow : gray;

      be_short_info("") << "Monitor #" << index << " mode: "
         << mode_color << std::right << std::setw(6) << mode.dim.x
         << dark_gray << "x"
         << mode_color << std::left << std::setw(6) << mode.dim.y
         << gray << "  "
         << red << std::setw(2)<< mode.bits.r
         << green << std::setw(2)<< mode.bits.g
         << blue << std::setw(2) << mode.bits.b
         << gray << "  "
         || rec;


      for (int refresh_rate : all_refresh_rates) {
         auto it = std::find(mode.refresh_rates.begin(), mode.refresh_rates.end(), refresh_rate);
         if (it == mode.refresh_rates.end()) {
            log_nil() << dark_gray << ' ' << refresh_rate || rec;
         } else if (is_current && refresh_rate == current->refreshRate) {
            log_nil() << mode_color << ' ' << refresh_rate || rec;
         } else {
            log_nil() << gray << ' ' << refresh_rate || rec;
         }
      }

      rec | default_log();
   }
}

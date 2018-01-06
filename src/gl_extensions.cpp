#include "gl_extensions.hpp"
#include <be/core/logging.hpp>
#include <glfw/glfw3.h>
#include <be/gfx/bgl.hpp>

using namespace be;
using namespace be::gfx::gl;

///////////////////////////////////////////////////////////////////////////////
void log_gl_extensions() {
   glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
   GLFWwindow* wnd = glfwCreateWindow(2, 2, "test", nullptr, nullptr);

   if (!wnd) {
      be_error() << "Failed to create GLFW window";
   } else {
      glfwMakeContextCurrent(wnd);
      init_context();

      int major = glfwGetWindowAttrib(wnd, GLFW_CONTEXT_VERSION_MAJOR);
      int minor = glfwGetWindowAttrib(wnd, GLFW_CONTEXT_VERSION_MINOR);
      int rev = glfwGetWindowAttrib(wnd, GLFW_CONTEXT_REVISION);

      auto vendor = static_cast<const char*>(static_cast<const void*>(glGetString(GL_VENDOR)));
      auto renderer = static_cast<const char*>(static_cast<const void*>(glGetString(GL_RENDERER)));
      auto version = static_cast<const char*>(static_cast<const void*>(glGetString(GL_VERSION)));
      auto glsl_version = static_cast<const char*>(static_cast<const void*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

      be_info() << "OpenGL Info"
         & attr("Version (GLFW)") << major << '.' << minor << '.' << rev
         & attr("Version (GL)") << version
         & attr("Version (GLSL)") << glsl_version
         & attr("Vendor") << vendor
         & attr("Renderer") << renderer
         | default_log();


      std::vector<S> extensions;
      if (major >= 3) {
         GLint n_extensions = 0;
         glGetIntegerv(GL_NUM_EXTENSIONS, &n_extensions);

         for (GLint i = 0; i < n_extensions; ++i) {
            auto ext = static_cast<const char*>(static_cast<const void*>(glGetStringi(GL_EXTENSIONS, i)));
            if (ext) {
               extensions.push_back(ext);
            }
         }
      } else {
         auto exts = static_cast<const char*>(static_cast<const void*>(glGetString(GL_EXTENSIONS)));
         if (exts) {
            for (const char* begin = exts, *it = exts; ; ++it) {
               char c = *it;
               if (c == ' ') {
                  extensions.push_back(S(begin, it));
                  begin = it + 1;
               } else if (c == '\0') {
                  extensions.push_back(S(begin, it));
                  break;
               }
            }
         }
      }

      LogRecord rec;
      be_info("") << "GL Extensions" & attr("Extensions") || rec;
      for (auto& ext : extensions) {
         log_nil() << nl << ext || rec;
      }

      rec | default_log();

      if (GL_KHR_debug) {
         be_short_verbose() << "Supports GL_KHR_debug" | default_log();
      }

      glfwDestroyWindow(wnd);
   }


}

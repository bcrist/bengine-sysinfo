tool { name = 'sysinfo',
   projects = {
      app {
         icon = 'icon/bengine-warm.ico',
         src = {
            'src/*.cpp'
         },
         libs = {
            'core',
            'core-id',
            'util',
            'platform',
            'glfw'
         }
      }
   }
}

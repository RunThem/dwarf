--- xmake configure
set_xmakever('2.6.1')
add_plugindirs('.plugins')

--- Project name
set_project('dwarf')

--- Project version
set_version('0.0.1')

--- Build mode
add_rules('mode.debug', 'mode.release')

--- Macro definition
add_defines('_GNU_SOURCE=1')

--- No warning
set_warnings('all', 'error')

--- Build C flags
add_cflags('-std=gnu2x')

--- Unused variables and functions
add_cflags('-Wno-unused-function', '-Wno-unused-variable')

--- Lambda expressions
local lambda = false
if lambda then
  add_cflags('-fblocks')
  if is_plat('linux') then
    add_ldflags('-lBlocksRuntime')
    add_defines('__linux__=1')
  end
end

-- add_requires('libbacktrace')

--- Project common header file path
add_includedirs('$(projectdir)/src')

--- main target
target('dump', function()
  set_kind('binary')
  add_files('$(projectdir)/src/dump.cpp')

  add_includedirs('/usr/local/include/')
  add_linkdirs('/usr/local/lib/')

  add_ldflags('-static')
  add_links('dwarf++', 'elf++')
end)

target('hello', function()
  set_kind('binary')
  add_files('$(projectdir)/src/hello.c')

  set_strip('all')
  add_cflags('-gdwarf-4')
end)

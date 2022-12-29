project('vrockutils', 'cpp', version: '0.0.1')

src = [
    'src/ByteArray.cpp'
]

utilslib = static_library(meson.project_name(), src,
    include_directories: include_directories('include')
)

utilslib_dep = declare_dependency(
    include_directories: include_directories('include'),
    link_with: utilslib
)
set_variable(meson.project_name() + '_dep', utilslib_dep)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : '',
  subdirs : meson.project_name(),
  libraries : utilslib,
)

####################
##### examples #####
####################

example_ByteArray = executable(
    'example_ByteArray', 'examples/example_ByteArray.cpp',
    dependencies: utilslib_dep
)
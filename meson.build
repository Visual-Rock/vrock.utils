project('vrockutils', 'cpp', version: '0.0.1')

src = [
    'src/ByteArray.cpp'
]

header = [
    'include/vrock/utils/ByteArray.hpp'
    'include/vrock/utils/List.hpp'
]

public_header = include_directories('include')

utilslib = static_library(meson.project_name(), src,
    include_directories: public_header
)

utilslib_dep = declare_dependency(
    include_directories: public_header,
    link_with: utilslib
)
set_variable(meson.project_name() + '_dep', utilslib_dep)

install_headers(header, subdir: meson.project_name())

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
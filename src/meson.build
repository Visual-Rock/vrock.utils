src = [
    'ByteArray.cpp'
]

header = [
    '../include/vrock/utils/ByteArray.hpp',
    '../include/vrock/utils/List.hpp'
]

public_header = include_directories('../include')

lib_type = get_option('default_library')
if lib_type == 'shared' and build_machine.system() == 'windows'
    add_global_arguments('-DVROCKUTILS_SHARED=1', language: 'cpp')
    add_project_arguments('-DVROCKUTILS_EXPORT=1', language: 'cpp')
endif

utilslib = library(meson.project_name(), src,
    include_directories: public_header
)

utilslib_dep = declare_dependency(
    include_directories: public_header,
    link_with: utilslib
)
set_variable(meson.project_name() + '_dep', utilslib_dep)

install_headers(header, subdir: 'vrock/utils')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : '',
  subdirs : meson.project_name(),
  libraries : utilslib,
)
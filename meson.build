project('vrockutils', 'cpp', version: '0.0.2')

src = [
    'src/ByteArray.cpp'
]

header = [
    'include/vrock/utils/ByteArray.hpp',
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

#################
##### tests #####
#################

test_src = [
    'tests/List.test.cpp',
    'tests/ByteArray.test.cpp'
]

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')


tests = executable(
    'tests', test_src,
    dependencies: [ gtest_dep, utilslib_dep ],
    include_directories: include_directories('include')
)

test('gtest tests', tests)

####################
##### examples #####
####################

example_ByteArray = executable(
    'example_ByteArray', 'examples/example_ByteArray.cpp',
    dependencies: utilslib_dep
)
if get_option('tests')

test_src = [
    'List.test.cpp',
    'ByteArray.test.cpp'
]

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')


tests = executable(
    'tests', test_src,
    dependencies: [ gtest_dep, utilslib_dep ],
    include_directories: include_directories('../include')
)

test('gtest tests', tests)

endif
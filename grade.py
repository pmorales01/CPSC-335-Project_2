
from gggg import *

a = Assignment(16, 8)
s = State(a)

horizontal_rule()

s.reject_if_missing_contributors()
s.reject_if_starter_contributors()

s.reject_unless_files_exist(['poly_exp.hpp',
                             'poly_exp.cpp',
                             'poly_exp_test.cpp'])

s.reject_if_file_unchanged('poly_exp.cpp',
                           'cbb6661f058909b3a93404f73e00ec117bb4b9ee19bed70f430c540cba25c956')

s.reject_if_file_changed('poly_exp_test.cpp',
                         'da64f8cb469a03c73cf8a9497c3219e458bd449bd3e7169314042d016c5d21f1')

s.reject_unless_command_succeeds(['make', 'build'])

s.string_removed_test('TODO comments removed', 2, 'TODO', ['poly_exp.cpp'])

s.gtest_run('poly_exp_test')
s.gtest_suite_test('soccer_exhaustive_invalid_argument', 2)
s.gtest_suite_test('soccer_exhaustive_trivial_instances', 2)
s.gtest_suite_test('soccer_exhaustive_general_instances', 2)
s.gtest_suite_test('soccer_dyn_prog_invalid_argument', 2)
s.gtest_suite_test('soccer_dyn_prog_trivial_instances', 2)
s.gtest_suite_test('soccer_dyn_prog_general_instances', 2)
s.gtest_suite_test('soccer_dyn_prog_large_instances', 2)

s.summarize()

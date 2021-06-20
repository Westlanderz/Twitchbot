project('Twitchbot', 'cpp', default_options : ['warning_level=3', 'werror=true'], version: '1.3.0-a.2')

cpp_compiler = meson.get_compiler('cpp')
add_project_arguments('--std=c++20', '-c', '-fcoroutines', '-ggdb', language: 'cpp')
add_project_arguments('-pedantic', '-Wshadow', '-Wpointer-arith', '-Wcast-align', '-Wwrite-strings', '-Wmissing-declarations', '-Wredundant-decls', '-Winline', '-Wno-long-long', '-Wconversion', language: 'cpp')

add_project_link_arguments('-lsockpp', language: 'cpp')

subdir('src')
subdir('tests')
subdir('docs')
#subdir('includes')

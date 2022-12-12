from setuptools import Extension, setup

pcg_cpp = Extension('pcg_cpp',
                 sources = [
                    'src/pypcg/pcg_wrapper.cpp',
                    'src/pypcg/py_cpp_conversion.cpp',
                ],
                 include_dirs = [
                    'src/pcg-cpp/include',
                    'src/pypcg',
                ],
                extra_compile_args=[
                    '-std=c++11',
                ])

setup(ext_modules = [pcg_cpp])
from setuptools import Extension, setup

pcg_cpp = Extension('PCG_CPP',
                 sources = [
                    'src/pypcg/pcg_wrapper.cpp',
                ],
                 include_dirs = ['src/pcg-cpp/include'])

setup(ext_modules = [pcg_cpp])
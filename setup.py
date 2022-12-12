from setuptools import Extension, setup

PCGCPP = Extension(
    'PCGCPP',
    sources = [
        'src/py_pcg/normal_cdf.cpp',
        'src/py_pcg/pcg_wrapper.cpp',
        'src/py_pcg/py_cpp_conversion.cpp',
    ],
    include_dirs = [
        'src/pcg-cpp/include',
        'src/py_pcg',
    ],
    extra_compile_args=[
        '-std=c++11',
    ]
)

setup(ext_modules = [PCGCPP])
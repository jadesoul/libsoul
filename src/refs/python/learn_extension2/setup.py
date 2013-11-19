#coding:utf8

from distutils.core import setup, Extension

setup(
    name = 'Edit Distance',
    version = '1.0',
    # description = 'This is a demo package for run system command',
    ext_modules = [
        Extension('edit_distance', sources = ['edit_distance.cpp'])
    ]
)


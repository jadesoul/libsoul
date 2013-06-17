#coding:utf8

from distutils.core import setup, Extension

setup(
    name = 'Spam system',
    version = '1.0',
    description = 'This is a demo package for run system command',
    ext_modules = [
        Extension('spam',sources = ['spam.cpp'])
    ]
)


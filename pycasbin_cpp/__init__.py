"""
pycasbin-on-cpp: High-performance Python bindings for casbin-cpp

This package provides Python bindings for casbin-cpp, offering
a significant performance improvement over the pure Python implementation.
"""

from pycasbin_cpp._pycasbin_cpp import (
    Enforcer,
    FileAdapter,
    __version__
)

__all__ = [
    'Enforcer',
    'FileAdapter',
    '__version__',
]

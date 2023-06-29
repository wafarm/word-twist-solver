from typing import List
from itertools import permutations
import ctypes

lib = ctypes.WinDLL("solver.dll")
lib.findall.argtypes = [ctypes.c_wchar_p]
lib.findall.restype = ctypes.py_object


def init() -> None:
    lib.init()


def findall(text: str) -> List[str]:
    return lib.findall(text)

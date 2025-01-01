import os
from ctypes import *
from enum import Enum

from scipy.signal import windows

SIZES = [
    1,
    2,
    3,
    4,
    6,
    7,
    8,
    9,
    10,
    16,
    31,
    32,
    33,
    63,
    64,
    100,
    128,
    200,
    256,
    500,
    511,
    512,
    513,
    1024,
    2048,
    4096,
    8192,
]

TESTS = [
    ('rect', 'boxcar'),
    ('triang', 'triang'),
    ('bartlett', 'bartlett'),
    ('parzen', 'parzen'),

    ('cosine', 'cosine'),
    ('bohman', 'bohman'),
    ('hann', 'hann'),
    ('hamming', 'hamming'),
    ('blackman', 'blackman'),
    ('nuttall', 'nuttall'),
    ('blackmanharris', 'blackmanharris'),
    ('flattop', 'flattop'),

    ('barthann', 'barthann'),

    ('lanczos', 'lanczos'),
]


class DataTypes(Enum):
    FLOAT32 = 'float32_t'
    FLOAT64 = 'float64_t'


"""
class Test(object):
    EPSILON = 1e-14
    dll = CDLL('./libwf.dll')

    def __init__(self, dll_wf_name: str, scipy_wf_name: str, has_alpha=False, alpha=0.0):
        self._dll_wf_name = dll_wf_name
        self._scipy_wf_name = scipy_wf_name
        self._has_alpha = has_alpha
        self._alpha = alpha

    def test(self, win_size: int) -> None:
        print(f'test for "{self._dll_wf_name}({
              self._alpha if self._has_alpha else ''})" ... ', end='')
        test_arr = (c_double * win_size)()
        # функции для получения массивов
        wf = getattr(self.dll, self._dll_wf_name)
        scipy_wf = getattr(windows, self._scipy_wf_name)
        # создание массивов
        if not self._has_alpha:
            wf(pointer(test_arr), c_size_t(win_size))
            test_win = scipy_wf(win_size)
        else:
            wf(pointer(test_arr), c_size_t(win_size), c_double(self._alpha))
            if self._scipy_wf_name == 'exponential':
                test_win = scipy_wf(win_size, None, self._alpha)
            elif self._scipy_wf_name == 'kaiser_bessel_derived' and win_size % 2:
                print('passed')
                return 0
            else:
                test_win = scipy_wf(win_size, self._alpha)
        # сравнение массивов
        mismatches = 0
        for i in range(win_size):
            xn = float(test_arr[i])
            ref = float(test_win[i])

            if abs(xn - ref) > self.EPSILON:
                # print(f'[{i:03}]: {xn} != {ref}')
                mismatches += 1

        print(f'{'passed' if not mismatches else f'failed, {mismatches} mismatches'}')

        return mismatches
"""


def gen(file_name):
    # генерация исходника
    with open(f'{file_name}.cpp', '+w') as f:
        f.write("""#include "mf/windows.hpp"

#if defined(_MSC_VER)
#define EXPORT_DLL __declspec(dllexport)
#else
#define EXPORT_DLL
#endif

extern "C" {

EXPORT_DLL int mf_has_float32_t = MF_HAS_FLOAT32_TYPE;
EXPORT_DLL int mf_has_float64_t = MF_HAS_FLOAT64_TYPE;

using namespace mf;

""")

        for d in DataTypes:
            f.write(f"""#if MF_HAS_{d.name}_TYPE""")

            for t in TESTS:
                f.write(f"""
////////////////////////////////////////////////////////////////////////////////
//                                   {t[0]}                                   //
////////////////////////////////////////////////////////////////////////////////""")

                for s in SIZES:
                    f.write(f"""
EXPORT_DLL void {t[0]}_{s}_{d.value}({d.value} *p) {{
    Windows<{d.value}, {s}>::{t[0]}(*({d.value} (*)[{s}])p);
}}""")

            f.write("""
#endif

""")

        f.write("""}
""")


def run(file_name):
    # Добавление папок из переменной PATH в поиск dll библиотек, т.к. собранная либа
    # зависит от dll, находящейся, например, в папке gcc/bin. Подразумевается, что
    # она находится где-то в этой переменной.
    path = os.environ['PATH']
    if os.name == 'nt':
        paths = path.split(';')
    elif os.name == 'posix':
        paths = path.split(':')
    else:
        print('Error: Unknown OS!')
        exit()
    for p in paths:
        if os.path.exists(p):
            os.add_dll_directory(p)

    dll = CDLL(f'./{file_name}.dll')
    for d in DataTypes:
        # проверка макроса MF_HAS_{xxxx}_TYPE
        if cast(getattr(dll, f'mf_has_{d.value}'), POINTER(c_int)).contents.value == 1:
            for t in TESTS:
                for s in SIZES:
                    # выделение памяти под
                    if d == DataTypes.FLOAT32:
                        c_win = (c_float * s)()
                        epsilon = 1e-6
                    elif d == DataTypes.FLOAT64:
                        c_win = (c_double * s)()
                        epsilon = 1e-14
                    out_str = f'test for Windows<{d.value}, {s}>::{t[0]} with {epsilon:.0e} accuracy...\n'
                    # функция из dll
                    c_fn_name = f'{t[0]}_{s}_{d.value}'
                    c_wf = getattr(dll, c_fn_name)
                    # функция из scipy
                    scipy_wf = getattr(windows, t[1])
                    # сравнение окон
                    c_wf(c_win)
                    scipy_win = scipy_wf(s)
                    mismatches = 0
                    for i in range(s):
                        xn = c_win[i]
                        ref = scipy_win[i]

                        if abs(xn - ref) > epsilon:
                            out_str += f'[{i:03}]: {xn} != {ref}\n'
                            mismatches += 1

                    if mismatches != 0:
                        out_str += f'failed, {mismatches} mismatches\n'
                        print(out_str)

import os
from ctypes import *
from enum import Enum

from scipy.signal import windows

SIZES = [
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
    ('nuttall4c', 'nuttall'),
    ('blackmanharris', 'blackmanharris'),
    ('flattop', 'flattop'),

    ('gaussian', 'gaussian', 0.3, 0.5, 0.8),
    ('tukey', 'tukey', 0.3, 0.5, 0.8),
    ('kaiser', 'kaiser', 1.0, 4.0, 9.0),
    ('kaiser_bessel_derived', 'kaiser_bessel_derived', 1.0, 4.0, 9.0),
    ('chebyshev', 'chebwin', 50.0, 90.0, 120.0),
    ('taylor', 'taylor'),
    ('poisson', 'exponential', 0.3, 0.5, 0.8),

    ('barthann', 'barthann'),

    ('lanczos', 'lanczos'),
]


class DataTypes(Enum):
    FLOAT32 = 'float32_t'
    FLOAT64 = 'float64_t'


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
                has_alpha = False
                if len(t) > 2:
                    has_alpha = True
                f.write(f"""
////////////////////////////////////////////////////////////////////////////////
//                                   {t[0]}                                   //
////////////////////////////////////////////////////////////////////////////////""")

                for s in SIZES:
                    if not has_alpha:
                        f.write(f"""
EXPORT_DLL void {t[0]}_{s}_{d.value}(void *p) {{
    windows::{t[0]}(*({d.value} (*)[{s}])p);
}}""")
                    else:
                        f.write(f"""
EXPORT_DLL void {t[0]}_{s}_{d.value}(void *p, double alpha) {{
    windows::{t[0]}(*({d.value} (*)[{s}])p, alpha);
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
        if c_int.in_dll(dll, f'mf_has_{d.value}'):
            for t in TESTS:
                has_alpha = False
                if len(t) > 2:
                    has_alpha = True
                for s in SIZES:
                    # выделение памяти под
                    if d == DataTypes.FLOAT32:
                        c_win = (c_float * s)()
                        epsilon = 1e-6
                    elif d == DataTypes.FLOAT64:
                        c_win = (c_double * s)()
                        if t[0] == 'chebyshev':
                            epsilon = 1e-10
                        else:
                            epsilon = 1e-14

                    # функция из dll
                    c_fn_name = f'{t[0]}_{s}_{d.value}'
                    c_wf = getattr(dll, c_fn_name)
                    # функция из scipy
                    scipy_wf = getattr(windows, t[1])
                    # сравнение окон
                    if not has_alpha:
                        out_str = f'test for Windows<{d.value}, {s}>::{t[0]} with {epsilon:.0e} accuracy...\n'
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
                    else:
                        for alpha in t[2:]:
                            out_str = f'test for Windows<{d.value}, {s}>::{
                                t[0]}({alpha}) with {epsilon:.0e} accuracy...\n'
                            c_wf(c_win, c_double(alpha))
                            if t[1] == 'exponential':
                                scipy_win = scipy_wf(s, None, alpha)
                            elif t[1] == 'kaiser_bessel_derived' and s % 2:
                                continue
                            else:
                                scipy_win = scipy_wf(s, alpha)

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

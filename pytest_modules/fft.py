import os
from ctypes import *
from enum import Enum

import numpy as np
from scipy.fft import fft, rfft

VALID_FFT_SIZES = [
    16,
    32,
    64,
    128,
    256,
    512,
    1024,
    2048,
    4096,
]


class DataTypes(Enum):
    FLOAT32 = 'float32_t'
    FLOAT64 = 'float64_t'


class Test(object):
    def __init__(self, dll, size: int, data_type: DataTypes):
        self._dll = dll
        if size not in VALID_FFT_SIZES:
            print(f'size == {size}, expected one of {VALID_FFT_SIZES}')
            return

        self._size = size
        self._data_type = data_type

        if self._data_type == DataTypes.FLOAT32:
            if size <= 64:
                self._epsilon = 1e-6
            elif size <= 1024:
                self._epsilon = 1e-5
            else:
                self._epsilon = 1e-4

            self._complex_data = (c_float * (self._size * 2))()
            self._real_data = (c_float * (self._size * 2))()
        elif self._data_type == DataTypes.FLOAT64:
            if size <= 256:
                self._epsilon = 1e-14
            else:
                self._epsilon = 1e-13

            self._complex_data = (c_double * (self._size * 2))()
            self._real_data = (c_double * (self._size * 2))()

        self._c_fft = getattr(self._dll, f'cfft_forward_{self._size}_{self._data_type.value}')
        self._c_ifft = getattr(self._dll, f'cfft_inverse_{self._size}_{self._data_type.value}')

        self._c_rfft = getattr(self._dll, f'rfft_forward_{self._size * 2}_{self._data_type.value}')
        self._c_irfft = getattr(self._dll, f'rfft_inverse_{self._size * 2}_{self._data_type.value}')

    def fft_test(self, data_t):
        data_f = fft(data_t)
        self.fft_forward_test(data_t, data_f)
        self.fft_inverse_test(data_t, data_f)

    def fft_forward_test(self, data_t, data_f):
        # print('data:')
        # print(data_t)

        for i in range(self._size):
            self._complex_data[2 * i + 0] = data_t[i].real
            self._complex_data[2 * i + 1] = data_t[i].imag

        self._c_fft(self._complex_data)
        if self._data_type == DataTypes.FLOAT32:
            testing_data = np.array(self._complex_data, dtype=np.float32).view(np.complex64)
        elif self._data_type == DataTypes.FLOAT64:
            testing_data = np.array(self._complex_data, dtype=np.float64).view(np.complex128)
        # print('mf:')
        # print(testing_data)

        out = f'test for cfft<{self._data_type.value}, {self._size}>::forward with {self._epsilon:.0e} accuracy...\n'
        mismatches = 0
        for i in range(testing_data.size):
            xn = testing_data[i]
            ref = data_f[i]

            if abs(xn - ref) > self._epsilon:
                out += f'[{i:03}]: {xn} != {ref}\n'
                mismatches += 1
        if mismatches != 0:
            out += f'failed, {mismatches} mismatches\n'
            print(out)
        return mismatches

    def fft_inverse_test(self, data_t, data_f):
        # print('data:')
        # print(data_f)

        for i in range(self._size):
            self._complex_data[2 * i + 0] = data_f[i].real
            self._complex_data[2 * i + 1] = data_f[i].imag

        self._c_ifft(self._complex_data)
        if self._data_type == DataTypes.FLOAT32:
            testing_data = np.array(self._complex_data, dtype=np.float32).view(np.complex64)
        elif self._data_type == DataTypes.FLOAT64:
            testing_data = np.array(self._complex_data, dtype=np.float64).view(np.complex128)
        # print('mf:')
        # print(testing_data)

        out = f'test for cfft<{self._data_type.value}, {self._size}>::inverse with {self._epsilon:.0e} accuracy...\n'
        mismatches = 0
        for i in range(testing_data.size):
            xn = testing_data[i]
            ref = data_t[i]

            if abs(xn - ref) > self._epsilon:
                out += f'[{i:03}]: {xn} != {ref}\n'
                mismatches += 1
        if mismatches != 0:
            out += f'failed, {mismatches} mismatches\n'
            print(out)
        return mismatches

    def rfft_test(self, data_t):
        data_f = rfft(data_t)
        # cutdown Nyquist frequency
        self.rfft_forward_test(data_t, data_f[:-1])
        self.rfft_inverse_test(data_t, data_f)

    def rfft_forward_test(self, data_t, data_f):
        # print('data:')
        # print(data_t)

        for i in range(self._size * 2):
            self._real_data[i] = data_t[i]

        self._c_rfft(self._real_data, self._complex_data)
        if self._data_type == DataTypes.FLOAT32:
            testing_data = np.array(
                self._complex_data, dtype=np.float32).view(np.complex64)
        elif self._data_type == DataTypes.FLOAT64:
            testing_data = np.array(self._complex_data, dtype=np.float64).view(np.complex128)
        # print('mf:')
        # print(testing_data)

        out = f'test for rfft<{self._data_type.value}, {self._size * 2}>::forward with {self._epsilon:.0e} accuracy...\n'
        mismatches = 0
        for i in range(testing_data.size):
            xn = testing_data[i]
            ref = data_f[i]

            if abs(xn - ref) > self._epsilon:
                out += f'[{i:03}]: {xn} != {ref}\n'
                mismatches += 1
        if mismatches != 0:
            out += f'failed, {mismatches} mismatches\n'
            print(out)
        return mismatches

    def rfft_inverse_test(self, data_t, data_f):
        # print('data:')
        # print(data_f)

        for i in range(self._size):
            self._complex_data[2 * i + 0] = data_f[i].real
            self._complex_data[2 * i + 1] = data_f[i].imag

        self._c_irfft(self._complex_data, self._real_data)
        if self._data_type == DataTypes.FLOAT32:
            testing_data = np.array(self._complex_data, dtype=np.float32).view(np.complex64)
        elif self._data_type == DataTypes.FLOAT64:
            testing_data = np.array(self._complex_data, dtype=np.float64).view(np.complex128)
        # print('mf:')
        # print(testing_data)

        out = f'test for rfft<{self._data_type.value}, {self._size * 2}>::inverse with {self._epsilon:.0e} accuracy...\n'
        mismatches = 0
        for i in range(testing_data.size // 2):
            xn = testing_data[i]
            ref = data_f[i]

            if abs(xn - ref) > self._epsilon:
                out += f'[{i:03}]: {xn} != {ref}\n'
                mismatches += 1
        if mismatches != 0:
            out += f'failed, {mismatches} mismatches\n'
            print(out)
        return mismatches


def gen(file_name):
    # генерация исходника
    with open(f'{file_name}.cpp', '+w') as f:
        f.write("""#include "mf/fft.hpp"

#if defined(_MSC_VER)
#define EXPORT_DLL __declspec(dllexport)
#else
#define EXPORT_DLL
#endif

extern "C" {

EXPORT_DLL int mf_has_float32 = MF_HAS_FLOAT32_TYPE;
EXPORT_DLL int mf_has_float64 = MF_HAS_FLOAT64_TYPE;

using namespace mf;

""")

        for t in DataTypes:
            f.write(f"""////////////////////////////////////////////////////////////////////////////////
//                                {t.name} CFFT                                //
////////////////////////////////////////////////////////////////////////////////
#if MF_HAS_{t.name}_TYPE

""")
            # cfft
            for size in VALID_FFT_SIZES:
                f.write(f"""EXPORT_DLL void cfft_forward_{size}_{t.value}(void *p) {{
    Cfft<{t.value}, {size}> cfft;
    cfft.forward(*(Complex<{t.value}>(*)[{size}])p);
}}

EXPORT_DLL void cfft_inverse_{size}_{t.value}(void *p) {{
    Cfft<{t.value}, {size}> cfft;
    cfft.inverse(*(Complex<{t.value}>(*)[{size}])p);
}}

""")
            # rfft
            for size in VALID_FFT_SIZES:
                f.write(f"""EXPORT_DLL void rfft_forward_{size * 2}_{t.value}(void *p1, void *p2) {{
    Rfft<{t.value}, {size * 2}> rfft;
    rfft.forward(*({t.value}(*)[{size * 2}])p1, *(Complex<{t.value}>(*)[{size}])p2);
}}

EXPORT_DLL void rfft_inverse_{size * 2}_{t.value}(void *p1, void *p2) {{
    Rfft<{t.value}, {size * 2}> rfft;
    rfft.inverse(*(Complex<{t.value}>(*)[{size}])p1, *({t.value}(*)[{size * 2}])p2);
}}

""")

            f.write("""#endif

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
    # 32 bit floating
    if c_int.in_dll(dll, 'mf_has_float32'):
        for size in VALID_FFT_SIZES:
            test = Test(dll, size, DataTypes.FLOAT32)

            x = np.random.rand(size * 2).astype(np.float32).view(np.complex64)
            test.fft_test(x)

            x = np.random.rand(size * 2).astype(np.float32)
            test.rfft_test(x)

    # 64 bit floating
    if c_int.in_dll(dll, 'mf_has_float64'):
        for size in VALID_FFT_SIZES:
            test = Test(dll, size, DataTypes.FLOAT64)

            x = np.random.rand(size * 2).astype(np.float64).view(np.complex128)
            test.fft_test(x)

            x = np.random.rand(size * 2).astype(np.float64)
            test.rfft_test(x)

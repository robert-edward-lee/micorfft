#include <stdlib.h>
#include <windows.h>

#include "print_hist.h"

#define PINS 32

static int terminal_columns;

static int terminal_rows;

static int clp2(int x) {
    return 1 << (31 - __builtin_clz(x));
}

static void get_terminal_size(void) {
    static CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    terminal_columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    terminal_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

static hist_t mean_arith(const hist_t *data, size_t size) {
    const hist_t *it;
    hist_t ret;

    ret = 0;
    for(it = data; it != data + size; ++it) {
        ret += *it;
    }

    return ret / size;
}

void fprint_hist_vert(FILE *f, const hist_t *hist, size_t size, size_t chars) {
    size_t i, j, tmp_size, rate, step;
    hist_t max;
    int align_idx;
    hist_t *tmp;

    if(!hist || !size) {
        return;
    }

    /* получение размеров терминала */
    get_terminal_size();
    tmp_size = clp2(terminal_columns);
    tmp = (hist_t *)malloc(tmp_size * sizeof(hist_t));
    if(!tmp) {
        return;
    }

    if(tmp_size < size) { /* пересчёт по частоте */
        rate = size / tmp_size;

        for(i = 0; i != tmp_size; ++i) {
            tmp[i] = mean_arith(&hist[i * rate], rate);
        }
    } else {
        tmp_size = size;
        for(i = 0; i != tmp_size; ++i) {
            tmp[i] = hist[i];
        }
    }

    /* поиск максимума для нормировки */
    for(i = 0, max = 0; i != tmp_size; ++i) {
        if(tmp[i] > max) {
            max = tmp[i];
        }
    }

    /* нормирование гистограммы */
    for(i = 0; i != tmp_size; ++i) {
        tmp[i] = tmp[i] * (chars / max);
    }

    /* поиск выравнивания для номера индекса */
    i = tmp_size;
    align_idx = 1;
    while(i /= 10) {
        ++align_idx;
    }

    /* печать */
    for(i = 0; i < chars; ++i) {
        fprintf(f, "\n");
        for(j = 0; j < tmp_size; ++j) {
            if(tmp[j] < chars - i) {
                fputc('.', f);
            } else {
                fputc('#', f);
                --tmp[j];
            }
        }
    }
    fputc('\n', f);

    /* печать горизонтальной оси */
    step = tmp_size / PINS;
    fprintf(f, "|%*c", (int)(step - 1), '|');
    for(i = 0; i != PINS - 1; ++i) {
        fprintf(f, "%*c", (int)step, '|');
    }
    fputc('\n', f);

    fprintf(f, "0%*zu", (int)(step - 1), step - 1);
    for(i = 2; i != PINS + 1; ++i) {
        fprintf(f, "%*zu", (int)step, i * step - 1);
    }
    fputc('\n', f);
}

void print_hist_vert(const hist_t *hist, size_t size, size_t chars) {
    fprint_hist_vert(stdout, hist, size, chars);
}

void fprint_hist_horiz(FILE *f, const hist_t *hist, size_t size, size_t chars) {
    size_t i, j;
    hist_t max;
    int align_idx;
    hist_t *tmp;

    if(!hist || !size) {
        return;
    }

    tmp = (hist_t *)malloc(size * sizeof(hist_t));
    if(!tmp) {
        return;
    }
    /* поиск максимума для нормировки */
    for(i = 0, max = 0; i != size; ++i) {
        if(hist[i] > max) {
            max = hist[i];
        }
    }
    /* нормирование гистограммы */
    for(i = 0; i != size; ++i) {
        tmp[i] = hist[i] * (chars / max);
    }
    /* поиск выравнивания для номера индекса */
    i = size;
    align_idx = 1;
    while(i /= 10) {
        ++align_idx;
    }
    /* печать */
    for(i = 0; i != size; ++i) {
        fprintf(f, "[%0*zu]", align_idx, i);
        for(j = 0; j != (size_t)tmp[i]; ++j) {
            fputc('#', f);
        }
        fputc('\n', f);
    }
}

void print_hist_horiz(const hist_t *hist, size_t size, size_t chars) {
    fprint_hist_horiz(stdout, hist, size, chars);
}

#ifndef H_PRINT_HIST
#define H_PRINT_HIST

#include <stddef.h>
#include <stdio.h>

#include "config.h"

#if !defined(HIST_TYPE)
#define HIST_TYPE TEST_FLOAT_T
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef HIST_TYPE hist_t;

void fprint_hist_horiz(FILE *f, const hist_t *hist, size_t size, size_t chars);
void print_hist_horiz(const hist_t *hist, size_t size, size_t chars);

void fprint_hist_vert(FILE *f, const hist_t *hist, size_t size, size_t chars);
void print_hist_vert(const hist_t *hist, size_t size, size_t chars);

#ifdef __cplusplus
}
#endif

#endif /* H_PRINT_HIST */

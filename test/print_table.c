#include <math.h>
#include <stddef.h>
#include <stdio.h>

void print_f32(const float *p, size_t size) {
    float tmp;
    size_t i;

    printf("{");
    for(i = 0; i != size; ++i) {
        if(i % 2) {
            printf(" ");
        } else {
            printf("\n[%02zu]  ", i / 2);
        }
        tmp = fabsf(p[i]) < 1 ? 0 : p[i];
        printf("%+.1e,", tmp);
    }
    printf("\n};\n");
}

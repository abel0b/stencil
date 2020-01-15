#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stencil/stencil.h"
#include "omp.h"

void stencil3d(float * a, float * b) {
    int i, j, k;
    #pragma omp parallel for private(j) private(i)
    for (k = 1; k < SIZEZ - 1; k++) {
        for (i = 1; i < SIZEX - 1; i++) {
            for (j = 1; j < SIZEY - 1; j++) {
                a[k * SIZEY * SIZEX + i * SIZEY + j] = (12 * b[k * SIZEY * SIZEX + i * SIZEY + j] +
                    b[k * SIZEY * SIZEX + i * SIZEY + j + 1] +
                    b[k * SIZEY * SIZEX + i * SIZEY + j - 1] +
                    b[k * SIZEY * SIZEX + (i + 1) * SIZEY + j + 1] +
                    b[k * SIZEY * SIZEX + (i - 1) * SIZEY + j - 1] +
                    b[(k + 1) * SIZEY * SIZEX + i * SIZEY + j + 1] +
                    b[(k + 1) * SIZEY * SIZEX + i * SIZEY + j - 1] +
                    b[(k + 1) * SIZEY * SIZEX + (i + 1) * SIZEY + j + 1] +
                    b[(k + 1) * SIZEY * SIZEX + (i - 1) * SIZEY + j - 1] +
                    b[(k - 1) * SIZEY * SIZEX + i * SIZEY + j + 1] +
                    b[(k - 1) * SIZEY * SIZEX + i * SIZEY + j - 1] +
                    b[(k - 1) * SIZEY * SIZEX + (i + 1) * SIZEY + j + 1] +
                    b[(k - 1) * SIZEY * SIZEX + (i - 1) * SIZEY + j - 1]) / 13;
            }
        }
    }
}

int main() {
    int i, j, k, h;
    float * a, * b;
    a = (float * ) malloc(sizeof(float) * SIZEX * SIZEY * SIZEZ);
    b = (float * ) malloc(sizeof(float) * SIZEX * SIZEY * SIZEZ);
    float s = 0;
    /* Initialization */
    #pragma omp parallel for private(i) private(j)
    for (k = 0; k < SIZEZ; k++) {
        for (i = 0; i < SIZEX; i++) {
            for (j = 0; j < SIZEY; j++) {
                a[k * SIZEY * SIZEX + i * SIZEY + j] = b[k * SIZEY * SIZEX + i * SIZEY + j] = (j + 1.) / ((k + 1) * (i + 1));
            }
        }
    }

    #pragma omp parallel for private(j)
    for (i = SIZEX / 4; i < SIZEX / 2; i++) {
        for (j = SIZEY / 4; j < SIZEY / 2; j++) {
            b[i * SIZEY + j] = a[i * SIZEY + j] = 1;
        }
    }

    for (h = 0; h < TIMESTEPS; h++) {
        stencil3d(a, b);
   
        #pragma omp parallel for private(i) private(j) reduction(+:s)
        for (k = 0; k < SIZEZ; k++) {
            for (i = 0; i < SIZEX; i++) {
                for (j = 0; j < SIZEY; j++) {
                    s = s + a[k * SIZEY * SIZEX + i * SIZEY + j];
                }
            }
        }

        stencil3d(b, a);
        
        fprintf(stderr, ".");
    }
    
    fprintf(stderr, "%f\n", s);
    
    free(a);
    free(b);
    
    return EXIT_SUCCESS;
}

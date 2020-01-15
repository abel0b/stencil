#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stencil/stencil.h"
#include "omp.h"

float * a = NULL;
float * b = NULL;

#define ELT(MAT,X,Y,Z) (MAT)[((X)/BLOCKSIZE)*BLOCKSIZE*SIZEY*SIZEZ+((Y)/BLOCKSIZE)*BLOCKSIZE*BLOCKSIZE*SIZEZ+((Z)/BLOCKSIZE)*BLOCKSIZE*BLOCKSIZE+((X)%BLOCKSIZE)*BLOCKSIZE*BLOCKSIZE+((Y)%BLOCKSIZE)*BLOCKSIZE+(Z)%BLOCKSIZE]

void stencil3d(float * a, float * b) {
    int i, j, k;
    /*int bi, bj, bk;
    int maxbj = SIZEY/BLOCKSIZE;
    int maxbi = SIZEX/BLOCKSIZE;
    int maxbk = SIZEZ/BLOCKSIZE;
    
    #pragma omp parallel for collapse(3) private(k) private(i) private(j)
    for(bk=0;bk++;bk<maxbk) {
        for(bi=0;bi++;bi<maxbi) {
            for(bj=0;bj++;bj<maxbj) {
                for (k = max(bk*BLOCKSIZE, 1); k < min((bk+1)*BLOCKSIZE, SIZEZ-1); k++) {
                    for (i = max(bi*BLOCKSIZE, 1); i < min((bi+1)*BLOCKSIZE, SIZEX-1); i++) {
                        for (j = max(bj*BLOCKSIZE, 1); j < min((bj+1)*BLOCKSIZE, SIZEY-1); j++) {*/

    // #pragma omp parallel for private(i) private(j)
    for (k = 0; k < SIZEZ; k++) {
        for (i = 0; i < SIZEX; i++) {
            for (j = 0; j < SIZEY; j++) {
                ELT(a,i,j,k) = (12 * ELT(b,i,j,k) +
                    ELT(b,i,j+1,k) +
                    ELT(b,i,j-1,k) +
                    ELT(b,i+1,j+1,k) +
                    ELT(b,i-1,j-1,k) +
                    ELT(b,i,j+1,k+1) +
                    ELT(b,i,j-1,k+1) +
                    ELT(b,i+1,j+1,k+1) +
                    ELT(b,i-1,j-1,k+1) +
                    ELT(b,i,j+1,k-1) +
                    ELT(b,i,j-1,k-1) +
                    ELT(b,i+1,j+1,k-1) +
                    ELT(b,i-1,j-1,k-1)) / 13.0;
            }
        }
    }
}

int main() {
    int i, j, k, h;
    a = (float * ) malloc(sizeof(float) * SIZEX * SIZEY * SIZEZ);
    b = (float * ) malloc(sizeof(float) * SIZEX * SIZEY * SIZEZ);
    float s = 0;
    /* Initialization */
    // #pragma omp parallel for private(i) private(j)
    for (k = 0; k < SIZEZ; k++) {
        for (i = 0; i < SIZEX; i++) {
            for (j = 0; j < SIZEY; j++) {
                ELT(a,i,j,k) = ELT(b,i,j,k) = (j + 1.) / ((k + 1) * (i + 1));
            }
        }
    }

    // #pragma omp parallel for private(j)
    for (i = SIZEX / 4; i < SIZEX / 2; i++) {
        for (j = SIZEY / 4; j < SIZEY / 2; j++) {
            ELT(b,i,j,0) = ELT(a,i,j,0) = 1;
        }
    }

    for (h = 0; h < TIMESTEPS; h++) {
        stencil3d(a, b);
        
        // #pragma omp parallel for private(i) private(j)
        for (k = 0; k < SIZEZ; k++) {
            for (i = 0; i < SIZEX; i++) {
                for (j = 0; j < SIZEY; j++) {
                    s += ELT(a,i,j,k);
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

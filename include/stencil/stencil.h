#ifndef STENCIL_H
#define STENCIL_H

#define abs(a)((a) > 0 ? (a) : -(a))

#ifndef SIZEX
#define SIZEX 128
#endif

#ifndef SIZEY
#define SIZEY 128
#endif

#ifndef SIZEZ
#define SIZEZ 128
#endif

#ifndef BLOCKSIZE
#define BLOCKSIZE 4
#endif

#ifndef TIMESTEPS
#define TIMESTEPS 32
#endif

inline int max(int a, int b) {
    return (a>=b)? a : b;
}

inline int min(int a, int b) {
    return (a<=b)? a : b;
}

#endif

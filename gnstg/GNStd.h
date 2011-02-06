#ifndef __GN_STD_H
#define __GN_STD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include <time.h>

#ifdef SysOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef unsigned int uint;
typedef float GNFloat;
typedef double GNDouble;
typedef char GNBool;
#define Yes 1
#define No 0
#define GNInitFailure (-1)

#define xrandFloat(lower,upper) (((upper) - (lower) + 1) * (float)random() / RAND_MAX + (lower))
#define xrandInt(lower,upper) (((upper) - (lower) + 1) * random() / RAND_MAX + (lower))

#define xrandFloatWithRand(rand,lower,upper) (((upper) - (lower) + 1) * (float)(rand) / RAND_MAX + (lower))

#endif

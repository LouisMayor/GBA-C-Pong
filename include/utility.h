/* SOF - UTILITY */

#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include "types.h"

static inline rgb15 RGB15(int r, int g, int b) {
	return r | (g << 5) | (b << 10);
}

static inline int ClampInt(int t, int min, int max) {
	return ( t < min ? min : ( t > max ? max : t ) );
}

#endif

/* EOF - UTILITY */
/* SOF - UTILITY */

#include "types.h"

static inline rgb15 RGB15(int r, int g, int b)
{
	return r | (g << 5) | (b << 10);
}

/* EOF - UTILITY */
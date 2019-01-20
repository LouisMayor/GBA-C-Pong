/* SOF - PONG TYPES */

// for any pong specific code

#ifndef PONG_TYPES_HEADER
#define PONG_TYPES_HEADER

#include "types.h"
#include "utility.h"

typedef struct paddle {
	int velocity;	// 1D velocity going in Y
	int positionX;	// pixel x
	int positionY;	// pixel y
	int dimensionX;	// sprite x length
	int dimensionY;	// sprite y length
	uint8 dirty;
} paddle;

typedef struct ball {
	int velocityX;	// velocity x
	int velocityY;	// velocity y
	int positionX;	// pixel x
	int positionY;	// pixel y
	int dimensionX;	// sprite x length
	int dimensionY;	// sprite y length
	uint8 dirty;
} ball;

#endif

/* EOF - PONG TYPES */
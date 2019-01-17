/* SOF - TYPES */

#ifndef TYPES_HEADER
#define TYPES_HEADER

typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned int	uint32;

typedef uint16 rgb15;

typedef struct obj_attributes {
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 padding;
} __attribute__((packed, aligned(4))) obj_attributes;

// colour palette storing 512 tiles (per block) storing 6 blocks in vram.
typedef uint32 tile_4bpp[8];
typedef tile_4bpp tile_block[512];

#endif

/* EOF - TYPES */
// CommonMacros.h

#define _COMMON_MACROS_H

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10

#define BOOL unsigned char
#define FALSE 0
#define TRUE 1

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define BIT_VEC(name, size) unsigned char name[(((size) - 1) >> 3) + 1]
#define BIT_VEC_ZERO(vec, size) for (short n = (size - 1) >> 3; n >= 0; n--) vec[n] = 0;
#define BIT_BLOCK(bit) ((bit) >> 3)
#define BIT_OFFSET(bit) ((bit) & 7)
#define BIT_SET(vec, bit) (vec[BIT_BLOCK(bit)] |= ((unsigned char)1 << BIT_OFFSET(bit)))
#define BIT_TEST(vec, bit) (vec[BIT_BLOCK(bit)] & ((unsigned char)1 << BIT_OFFSET(bit)))
#define BIT_UNION(first, second, size) for (short n = (size - 1) >> 3; n >= 0; n--) first[n] |= second[n];

#define SWAP(a, b, type) { type temp = (a); (a) = (b); (b) = temp; }
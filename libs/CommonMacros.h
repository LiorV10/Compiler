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

#define SWAP(a, b, type) { type temp = (a); (a) = (b); (b) = temp; }
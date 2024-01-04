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
#define ONE_HUNDRED 100

#define DAYS_IN_YEAR 360
#define DAYS_IN_MONTH 30

#define BOOL unsigned char
#define FALSE 0
#define TRUE 1

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define EVEN(num) (!(num & ONE))
#define ODD(num) (num & ONE)
#define DIVISIBLE_BY(num, divisor) (!(num % divisor))
#define SUM(a, b) (a + b)
#define ABS(n) (n > ZERO ? n : -(n))
#define POSITIVE_MIN(a,b) (a * b <= ZERO ? MAX(a, b) : MIN(a, b))
#define IS_DIGIT(str) (!((str) < '0' || (str) > '9'))
#include "TetrisTimeAttack.h"

/**
 * Takes the base to the power of the exponent
 * @param base Base of the exponent (A -> A^B)
 * @param exp Power of the exponent (B -> A^B)
 * @return base^exp
 */
long scorePow(int base, int exp) {
    long powOut = base;
    while (exp > 1) {
        powOut *= base;
        exp--;
    }
    return powOut;
}
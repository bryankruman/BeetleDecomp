/*
 * Shifts an unsigned 64-bit value right by the stock count argument. The
 * original body uses the MIPS3 variable logical shift; no count mask or
 * caller-domain guard is added.
 */
#line 1 "src/libultra/libc/ll.c"
unsigned long long __ull_rshift(unsigned long long a0, unsigned long long a1) {
    return a0 >> a1;
}

/*
 * Returns an unsigned 64-bit remainder. The original DDIVU body retains its
 * division-by-zero trap; no new source guard is introduced.
 */
#line 5 "src/libultra/libc/ll.c"
unsigned long long __ull_rem(unsigned long long a0, unsigned long long a1) {
    return a0 % a1;
}

/*
 * Returns an unsigned 64-bit quotient. The original DDIVU body retains its
 * division-by-zero trap; no new source guard is introduced.
 */
#line 9 "src/libultra/libc/ll.c"
unsigned long long __ull_div(unsigned long long a0, unsigned long long a1) {
    return a0 / a1;
}

/*
 * Shifts the stock unsigned 64-bit operand left. The public helper name and
 * unsigned parameter types remain literal; the original body uses MIPS3
 * DSLLV.
 */
#line 13 "src/libultra/libc/ll.c"
unsigned long long __ll_lshift(unsigned long long a0, unsigned long long a1) {
    return a0 << a1;
}

/*
 * Computes the remainder after unsigned operand conversion, then returns
 * through the stock signed result type. The original body uses DDIVU; the
 * helper name does not imply signed division.
 */
#line 17 "src/libultra/libc/ll.c"
long long __ll_rem(unsigned long long a0, long long a1) {
    return a0 % a1;
}

/*
 * Returns the signed 64-bit quotient. The original DDIV body preserves
 * divide-by-zero and signed-overflow traps; the stock C expression is
 * unchanged.
 */
#line 21 "src/libultra/libc/ll.c"
long long __ll_div(long long a0, long long a1) {
    return a0 / a1;
}

/*
 * Returns the low 64 bits of the unsigned product through the stock unsigned
 * result type. The original MIPS3 body uses DMULTU and takes its low product.
 */
#line 25 "src/libultra/libc/ll.c"
unsigned long long __ll_mul(unsigned long long a0, unsigned long long a1) {
    return a0 * a1;
}

/*
 * Stores the quotient through div, then stores the remainder through rem. The
 * original body performs the stores in that order and reloads operands
 * between divisions; pointer aliasing is not rewritten.
 *
 * RE_UNKNOWN: The stock declaration says unsigned short, but both the
 * original and the matched compiler output load its argument home slot with
 * signed LH. High-bit divisor usage and the historical caller domain remain
 * unresolved; the declaration and machine behavior are preserved.
 */
#line 29 "src/libultra/libc/ll.c"
void __ull_divremi(unsigned long long* div, unsigned long long* rem, unsigned long long a2, unsigned short a3) {
    *div = a2 / a3;
    *rem = a2 % a3;
}

/*
 * Starts with the signed remainder and adds the divisor when a nonzero
 * remainder has the opposite sign. This preserves the original sign tests and
 * the divisor-directed modulo adjustment.
 */
#line 34 "src/libultra/libc/ll.c"
long long __ll_mod(long long a0, long long a1) {
    long long tmp = a0 % a1;

    if ((tmp < 0 && a1 > 0) || (tmp > 0 && a1 < 0)) {
        tmp += a1;
    }

    return tmp;
}

/*
 * Shifts a signed 64-bit value right through the stock signed expression. The
 * original body uses the MIPS3 variable arithmetic right shift; no count mask
 * or caller-domain guard is added.
 */
#line 44 "src/libultra/libc/ll.c"
long long __ll_rshift(long long a0, long long a1) {
    return a0 >> a1;
}

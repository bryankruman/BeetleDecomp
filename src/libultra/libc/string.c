#include "PR/ultratypes.h"
#include "string.h"

// TODO: this comes from a header
#ident "$Revision: 1.23 $"

/* Search using the converted char value; the terminator itself can match. */ char* strchr(const char* s, int c) {
    const char ch = c;
    while (*s != ch) {
        if (*s == 0) {
            return NULL;
        }
        s++;
    }
    return (char*)s;
}

/* Count bytes up to the first terminator; input validity is the caller contract. */ size_t strlen(const char* s) {
    const char* sc = s;
    while (*sc != 0) {
        sc++;
    }
    return sc - s;
}

/* Copy bytes forward and return the original destination; no overlap repair. */ void* memcpy(void* s1, const void* s2, size_t n) {
    char* su1 = (char*)s1;
    const char* su2 = (const char*)s2;
    while (n > 0) {
        *su1 = *su2;
        su1++;
        su2++;
        n--;
    }
    return (void*)s1;
}

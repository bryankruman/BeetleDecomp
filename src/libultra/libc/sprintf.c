#include "xstdio.h"
#include "string.h"
#include "os.h"

// TODO: this comes from a header
#ident "$Revision: 1.23 $"

static void* proutSprintf(void* s, const char* buf, size_t n);

/* Format through _Printf; append a terminator only for a nonnegative result. */ int sprintf(char* s, const char* fmt, ...) {
    int ans;
    va_list ap;
    va_start(ap, fmt);
    ans = _Printf(proutSprintf, s, fmt, ap);
    if (ans >= 0) {
        s[ans] = 0;
    }
    return ans;
}
/* Copy this formatter chunk and return the next destination address. */ static void* proutSprintf(void* s, const char* buf, size_t n) {
    return (char*)memcpy(s, buf, n) + n;
}

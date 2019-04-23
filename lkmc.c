/* https://github.com/cirosantilli/linux-kernel-module-cheat#lkmc-c */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <lkmc.h>

void lkmc_assert(bool condition) {
    if (!condition)
        lkmc_assert_fail();
}

void lkmc_assert_fail(void) {
    puts("lkmc_test_fail");
    exit(1);
}

#if defined(__aarch64__)
#define LKMC_SYSREG_READ_WRITE(type, name) \
    type LKMC_CONCAT(LKMC_CONCAT(LKMC_SYSREG_SYMBOL_PREFIX, name), _read(void)) { \
        type name; \
        __asm__ __volatile__("mrs %0, " #name : "=r" (name) : : ); \
        return name; \
    } \
    void LKMC_CONCAT(LKMC_CONCAT(LKMC_SYSREG_SYMBOL_PREFIX, name), _write(type name)) { \
        __asm__ __volatile__("msr " #name ", %0" : : "r" (name) : ); \
    }
LKMC_SYSREG_OPS
#undef LKMC_SYSREG_READ_WRITE
#endif

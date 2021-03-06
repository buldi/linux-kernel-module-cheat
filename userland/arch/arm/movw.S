/* https://github.com/cirosantilli/linux-kernel-module-cheat#arm-movw-and-movt-instructions */

#include <lkmc.h>

LKMC_PROLOGUE

    /* movt (top) and movw (TODO what is w) set the higher
     * and lower 16 bits of the register.
     */
    movw r0, 0xFFFF
    movt r0, 0x1234
    add r0, 1
    LKMC_ASSERT_EQ(r0, =0x12350000)

    /* movw also zeroes out the top bits, allowing small 16-bit
     * C constants to be assigned in a single instruction.
     *
     * It differs from mov because mov can only encode 8 bits
     * at a time, while movw can encode 16.
     *
     * movt does not modify the lower bits however.
     */
    ldr r0, =0x12345678
    movw r0, 0x1111
    LKMC_ASSERT_EQ(r0, =0x00001111)

LKMC_EPILOGUE

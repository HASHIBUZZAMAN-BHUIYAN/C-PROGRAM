/*
 * Intermediate Day 07 — Bit Manipulation
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdint.h>

void print_bits(uint32_t n) {
    for (int i=31; i>=0; i--) {
        printf("%d", (n>>i)&1);
        if (i%8==0 && i>0) printf(" ");
    }
}

/* Bit operations */
uint32_t bit_set(uint32_t n, int pos)    { return n | (1u<<pos); }
uint32_t bit_clear(uint32_t n, int pos)  { return n & ~(1u<<pos); }
uint32_t bit_toggle(uint32_t n, int pos) { return n ^ (1u<<pos); }
int      bit_test(uint32_t n, int pos)   { return (n>>pos)&1; }
int      popcount(uint32_t n)            { int c=0; while(n){c+=n&1;n>>=1;} return c; }
int      is_power_of_2(uint32_t n)       { return n && !(n&(n-1)); }
uint32_t lowest_set_bit(uint32_t n)      { return n & (-n); } /* two's complement trick */

/* Bit flag permissions */
#define PERM_READ    (1u<<0)  /* 0b001 */
#define PERM_WRITE   (1u<<1)  /* 0b010 */
#define PERM_EXECUTE (1u<<2)  /* 0b100 */

void print_permissions(uint32_t p) {
    printf("[%s%s%s]",
           p&PERM_READ    ? "R" : "-",
           p&PERM_WRITE   ? "W" : "-",
           p&PERM_EXECUTE ? "X" : "-");
}

int main(void) {
    printf("=== Intermediate Day 07: Bit Manipulation ===\n\n");

    uint32_t n = 0b10110100;
    printf("n = %u\nBits: ", n); print_bits(n); printf("\n");

    printf("\n--- Bit Operations on n=%u ---\n", n);
    printf("set bit 0   : "); print_bits(bit_set(n,0));    printf(" = %u\n", bit_set(n,0));
    printf("clear bit 2 : "); print_bits(bit_clear(n,2));  printf(" = %u\n", bit_clear(n,2));
    printf("toggle bit 4: "); print_bits(bit_toggle(n,4)); printf(" = %u\n", bit_toggle(n,4));
    printf("test bit 4  : %d\n", bit_test(n,4));
    printf("popcount    : %d\n", popcount(n));

    printf("\n--- Power of 2 check ---\n");
    uint32_t tests[] = {1,2,3,4,16,15,256,100};
    for (int i=0;i<8;i++) printf("  %3u: %s\n", tests[i], is_power_of_2(tests[i])?"yes":"no");

    printf("\n--- Lowest Set Bit ---\n");
    printf("  lowest_set_bit(12) = %u  (12=0b1100, lowest=0b0100=4)\n", lowest_set_bit(12));

    printf("\n--- Shift operations ---\n");
    printf("  5 << 3 = %d  (multiply by 2^3=8)\n", 5<<3);
    printf("  80 >> 4 = %d (divide by 2^4=16)\n",  80>>4);

    printf("\n--- File Permission Flags ---\n");
    uint32_t owner = PERM_READ | PERM_WRITE | PERM_EXECUTE;
    uint32_t group = PERM_READ | PERM_EXECUTE;
    uint32_t other = PERM_READ;
    printf("Owner: "); print_permissions(owner); printf("\n");
    printf("Group: "); print_permissions(group); printf("\n");
    printf("Other: "); print_permissions(other); printf("\n");

    /* Packed nibbles: store 4-bit values in a uint32_t */
    printf("\n--- Packed Nibbles (4 values in 32 bits) ---\n");
    uint32_t packed = 0;
    int vals[] = {3, 7, 12, 5};
    for (int i=0;i<4;i++) packed |= ((uint32_t)vals[i] & 0xF) << (i*8);
    for (int i=0;i<4;i++) printf("  nibble[%d] = %u\n", i, (packed>>(i*8))&0xF);

    return 0;
}

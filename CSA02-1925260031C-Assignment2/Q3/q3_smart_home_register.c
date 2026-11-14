#include <stdio.h>

enum { LIGHT = 0, FAN = 1, AC = 2, HEATER = 3, PUMP = 4, ALARM = 5, CAMERA = 6, ROUTER = 7 };

unsigned char switch_on(unsigned char reg, int dev)  { return (unsigned char)(reg | (1u << dev)); }
unsigned char switch_off(unsigned char reg, int dev) { return (unsigned char)(reg & ~(1u << dev)); }
unsigned char toggle(unsigned char reg, int dev)     { return (unsigned char)(reg ^ (1u << dev)); }
int is_on(unsigned char reg, int dev)                { return (reg >> dev) & 1u; }

/* Count ON devices using Brian Kernighan's bitwise algorithm */
int count_on_devices(unsigned char reg) {
    int count = 0;
    while (reg != 0) {
        reg &= (unsigned char)(reg - 1u);
        count++;
    }
    return count;
}

void print_binary(unsigned char reg) {
    for (int b = 7; b >= 0; b--) {
        putchar(((reg >> b) & 1u) ? '1' : '0');
    }
}

int main(void) {
    unsigned char reg = 0;
    printf("=== Q3: SMART-HOME BITWISE REGISTER TRACE ===\n");
    printf("Initial reg               : "); print_binary(reg); printf(" (dec=%u, ON=%d)\n", reg, count_on_devices(reg));

    reg = switch_on(reg, LIGHT);
    printf("After switch_on(LIGHT=0)  : "); print_binary(reg); printf(" (dec=%u, ON=%d)\n", reg, count_on_devices(reg));

    reg = switch_on(reg, AC);
    printf("After switch_on(AC=2)     : "); print_binary(reg); printf(" (dec=%u, ON=%d)\n", reg, count_on_devices(reg));

    reg = switch_on(reg, ROUTER);
    printf("After switch_on(ROUTER=7) : "); print_binary(reg); printf(" (dec=%u, ON=%d)\n", reg, count_on_devices(reg));

    reg = toggle(reg, FAN);
    printf("After toggle(FAN=1)       : "); print_binary(reg); printf(" (dec=%u, ON=%d)\n", reg, count_on_devices(reg));

    reg = switch_off(reg, LIGHT);
    printf("After switch_off(LIGHT=0) : "); print_binary(reg); printf(" (dec=%u, ON=%d)\n", reg, count_on_devices(reg));

    int dev = 2;
    printf("\nPrecedence Check (reg=%u, dev=%d):\n", reg, dev);
    printf("  reg & 1 << dev   = %u (evaluates reg & (1 << 2) = 134 & 4 = 4)\n", reg & 1 << dev);
    printf("  (reg & 1) << dev = %u (evaluates (134 & 1) << 2 = 0 << 2 = 0)\n", (reg & 1) << dev);

    size_t homes = 1000000;
    printf("\nMemory for 1,000,000 homes:\n");
    printf("  Bitwise unsigned char : %zu bytes (%.2f MB)\n", homes * sizeof(unsigned char), (homes * 1.0) / (1024 * 1024));
    printf("  Array char state[8]   : %zu bytes (%.2f MB)\n", homes * 8 * sizeof(char), (homes * 8.0) / (1024 * 1024));
    return 0;
}

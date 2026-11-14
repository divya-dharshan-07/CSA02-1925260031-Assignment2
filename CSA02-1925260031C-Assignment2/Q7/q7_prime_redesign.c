#include <stdio.h>

int is_prime_original(unsigned long n, unsigned long *divisions) {
    *divisions = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i <= n / i; i++) {
        (*divisions)++;
        if (n % i == 0) return 0;
    }
    return 1;
}

int is_prime_redesigned(unsigned long n, unsigned long *divisions) {
    *divisions = 0;
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;

    (*divisions)++;
    if (n % 2 == 0) return 0;

    (*divisions)++;
    if (n % 3 == 0) return 0;

    for (unsigned long i = 5; i <= n / i; i += 6) {
        (*divisions)++;
        if (n % i == 0) return 0;

        if (i + 2 <= n / (i + 2)) {
            (*divisions)++;
            if (n % (i + 2) == 0) return 0;
        }
    }
    return 1;
}

int main(void) {
    unsigned long test_inputs[] = {2, 3, 97, 100, 7919, 104729, 1000003, 99999989};
    int count = sizeof(test_inputs) / sizeof(test_inputs[0]);

    printf("=== Q7: DAY-4 DESIGN CHALLENGE (ORIGINAL vs 6k +/- 1 REDESIGN) ===\n");
    printf("%10s | %-9s | Orig Divs | Redesign Divs | Reduction\n", "Ticket", "Status");
    printf("-----------+-----------+-----------+---------------+----------\n");

    for (int k = 0; k < count; k++) {
        unsigned long n = test_inputs[k];
        unsigned long d_orig = 0, d_red = 0;
        int p1 = is_prime_original(n, &d_orig);
        int p2 = is_prime_redesigned(n, &d_red);

        if (p1 != p2) {
            printf("VALIDATION ERROR on %lu!\n", n);
            return 1;
        }
        double pct = (d_orig > 0) ? (100.0 * (d_orig - d_red) / d_orig) : 0.0;
        printf("%10lu | %-9s | %9lu | %13lu | %7.1f%%\n",
               n, p2 ? "prime" : "not prime", d_orig, d_red, pct);
    }
    return 0;
}

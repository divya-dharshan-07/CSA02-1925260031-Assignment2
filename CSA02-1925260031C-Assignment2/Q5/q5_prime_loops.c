#include <stdio.h>
#include <stdlib.h>

int is_prime_naive_for(unsigned long n, unsigned long *checks) {
    *checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i < n; i++) {
        (*checks)++;
        if (n % i == 0) return 0;
    }
    return 1;
}

int is_prime_sqrt_for(unsigned long n, unsigned long *checks) {
    *checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i <= n / i; i++) {
        (*checks)++;
        if (n % i == 0) return 0;
    }
    return 1;
}

int is_prime_sqrt_while(unsigned long n, unsigned long *checks) {
    *checks = 0;
    if (n < 2) return 0;
    unsigned long i = 2;
    while (i <= n / i) {
        (*checks)++;
        if (n % i == 0) return 0;
        i++;
    }
    return 1;
}

int is_prime_sqrt_dowhile(unsigned long n, unsigned long *checks) {
    *checks = 0;
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    unsigned long i = 2;
    do {
        (*checks)++;
        if (n % i == 0) return 0;
        i++;
    } while (i <= n / i);
    return 1;
}

void benchmark_sieve(unsigned long max_n) {
    unsigned char *is_p = (unsigned char *)malloc(max_n + 1);
    if (!is_p) return;
    for (unsigned long i = 0; i <= max_n; i++) is_p[i] = 1;
    is_p[0] = is_p[1] = 0;

    unsigned long sieve_ops = 0;
    for (unsigned long p = 2; p <= max_n / p; p++) {
        if (is_p[p]) {
            for (unsigned long m = p * p; m <= max_n; m += p) {
                is_p[m] = 0;
                sieve_ops++;
            }
        }
    }
    printf("\n=== SIEVE OF ERATOSTHENES (N = %lu) ===\n", max_n);
    printf("Precomputation composite markings: %lu ops | Memory: %lu bytes (%.2f KB)\n",
           sieve_ops, max_n + 1, (max_n + 1) / 1024.0);
    printf("O(1) Query Check -> 97:%d, 100:%d, 7919:%d, 1000003:%d\n",
           is_p[97], is_p[100], is_p[7919], is_p[1000003]);
    free(is_p);
}

int main(void) {
    unsigned long tickets[] = {2, 3, 97, 100, 7919, 1000003};
    int count = sizeof(tickets) / sizeof(tickets[0]);

    printf("=== Q5: DIVISION COUNTS ACROSS LOOP CONSTRUCTS ===\n");
    printf("Ticket   | Result    | Naive (i<n) | sqrt for | sqrt while | sqrt do-while\n");
    printf("---------+-----------+-------------+----------+------------+--------------\n");
    for (int k = 0; k < count; k++) {
        unsigned long n = tickets[k];
        unsigned long c_naive, c_for, c_while, c_do;
        int p1 = is_prime_naive_for(n, &c_naive);
        int p2 = is_prime_sqrt_for(n, &c_for);
        int p3 = is_prime_sqrt_while(n, &c_while);
        int p4 = is_prime_sqrt_dowhile(n, &c_do);

        if (p1 != p2 || p2 != p3 || p3 != p4) {
            printf("ERROR: Mismatch for n=%lu\n", n);
        }
        printf("%8lu | %-9s | %11lu | %8lu | %10lu | %13lu\n",
               n, p2 ? "prime" : "not prime", c_naive, c_for, c_while, c_do);
    }

    benchmark_sieve(1000003);
    return 0;
}

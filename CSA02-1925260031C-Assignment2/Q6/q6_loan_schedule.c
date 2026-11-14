#include <stdio.h>
#include <math.h>

#define MAX_MONTHS 360
#define EPSILON 0.005

int simulate_loan(double principal, double monthly_rate, double emi, int print_table, double *out_total_interest) {
    double balance = principal;
    double total_interest = 0.0;
    int month = 0;

    if (print_table) {
        printf("Month | Opening Bal | Interest | Payment  | Closing Bal\n");
        printf("------+-------------+----------+----------+------------\n");
    }

    while (balance > EPSILON) {
        if (month >= MAX_MONTHS) {
            if (print_table) {
                printf("ALERT: Safety limit of %d months reached! Repayment (%.2f) may be too low.\n",
                       MAX_MONTHS, emi);
            }
            if (out_total_interest) *out_total_interest = total_interest;
            return -1;
        }

        month++;
        double opening = balance;
        double interest = opening * monthly_rate;
        double due = opening + interest;
        double payment = (due < emi) ? due : emi;
        balance = due - payment;
        total_interest += interest;

        if (print_table) {
            printf("%5d | %11.2f | %8.2f | %8.2f | %11.2f\n",
                   month, opening, interest, payment, balance);
        }
    }

    if (out_total_interest) *out_total_interest = total_interest;
    return month;
}

int main(void) {
    printf("=== Q6: SELF-HELP GROUP MICRO-LOAN SCHEDULE ===\n");
    printf("Loan: Rs 10,000 | Monthly Interest: 2.0%% | Fixed Repayment: Rs 2,000\n\n");
    double tot_int = 0.0;
    int months = simulate_loan(10000.0, 0.02, 2000.0, 1, &tot_int);
    printf("\nSummary -> Repaid in %d months | Total Interest Paid = Rs %.2f\n", months, tot_int);

    double P = 10000.0, r = 0.02, E = 2000.0;
    double exact_n = -log(1.0 - (r * P) / E) / log(1.0 + r);
    printf("Closed-Form Formula -> exact n = %.4f months (ceil = %d)\n", exact_n, (int)ceil(exact_n));

    printf("\n=== GROWTH INVESTIGATION (P = Rs 10,000, r = 2%% -> Initial Interest = Rs 200) ===\n");
    double test_emis[] = {2000.0, 1000.0, 500.0, 300.0, 220.0, 205.0, 200.0, 180.0};
    for (int i = 0; i < 8; i++) {
        double e = test_emis[i];
        double ti = 0.0;
        int m = simulate_loan(10000.0, 0.02, e, 0, &ti);
        if (m == -1) {
            printf("EMI = Rs %7.2f -> EXCEEDED %d MONTHS (Non-terminating / Cap hit)\n", e, MAX_MONTHS);
        } else {
            printf("EMI = Rs %7.2f -> Months = %3d | Total Interest = Rs %9.2f\n", e, m, ti);
        }
    }
    return 0;
}

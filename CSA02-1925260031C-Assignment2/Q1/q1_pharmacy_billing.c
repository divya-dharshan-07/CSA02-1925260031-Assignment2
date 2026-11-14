#include <stdio.h>

/* Buggy expression from legacy developer */
int buggy_total(int price, int qty, int senior) {
    return price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
}

int buggy_net(int total) {
    return total > 1000 ? total - 50 : total;
}

/* Corrected & readable version using intermediate variables and proper grouping */
int corrected_net(int price, int qty, int senior, int *out_gross, int *out_disc, int *out_gst, int *out_total) {
    int gross = price * qty;
    /* Multiply before dividing to avoid premature integer truncation */
    int discount = senior ? (gross * 15) / 100 : 0;
    int taxable = gross - discount; /* GST applies after trade discount */
    int gst = (taxable * 5) / 100;
    int total = taxable + gst;
    int net = (total > 1000) ? (total - 50) : total;

    if (out_gross) *out_gross = gross;
    if (out_disc)  *out_disc  = discount;
    if (out_gst)   *out_gst   = gst;
    if (out_total) *out_total = total;
    return net;
}

int main(void) {
    struct { int price; int qty; int senior; const char *desc; } bills[] = {
        {6, 1, 1, "Bill 1: Small senior bill (price=6, qty=1, senior=1)"},
        {500, 3, 1, "Bill 2: Large senior bill (price=500, qty=3, senior=1)"},
        {250, 4, 0, "Bill 3: Borderline regular bill (price=250, qty=4, senior=0)"}
    };

    printf("=== Q1: JAN AUSHADHI PHARMACY BILLING COMPARISON ===\n");
    for (int i = 0; i < 3; i++) {
        int p = bills[i].price, q = bills[i].qty, s = bills[i].senior;
        int b_tot = buggy_total(p, q, s);
        int b_net = buggy_net(b_tot);

        int gross, disc, gst, c_tot;
        int c_net = corrected_net(p, q, s, &gross, &disc, &gst, &c_tot);

        printf("\n%s\n", bills[i].desc);
        printf("  Buggy     -> total = %d, net = %d\n", b_tot, b_net);
        printf("  Corrected -> gross = %d, discount = %d, gst = %d, total = %d, net = %d\n",
               gross, disc, gst, c_tot, c_net);
    }

    /* Safe replacement for undefined `count = count++ + 1;` */
    int count = 5;
    count += 1;
    printf("\nSafe increment result (count started at 5): %d\n", count);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

static int slow_calls = 0;
static int audit_entries = 0;

/* Simulates a slow remote server call to verify disability card */
int verify_disability_card(int passenger_id, int has_valid_card) {
    slow_calls++;
    audit_entries++;
    (void)passenger_id;
    return has_valid_card;
}

int main(void) {
    const char *paths[] = {
        "passengers_1000.csv",
        "Q2/passengers_1000.csv",
        "CSA02-1925260031C-Assignment2/Q2/passengers_1000.csv"
    };
    FILE *fp = NULL;
    for (int p = 0; p < 3 && !fp; p++) {
        fp = fopen(paths[p], "r");
    }
    if (!fp) {
        perror("Failed to open passengers_1000.csv");
        return 1;
    }

    int ids[1000], senior[1000], eligible[1000], disability[1000];
    char header[128];
    if (!fgets(header, sizeof(header), fp)) {
        fclose(fp);
        return 1;
    }

    int n = 0;
    while (n < 1000 && fscanf(fp, "%d,%d,%d,%d", &ids[n], &senior[n], &eligible[n], &disability[n]) == 4) {
        n++;
    }
    fclose(fp);

    printf("=== Q2: SHORT-CIRCUIT EVALUATION EXPERIMENTS (%d PASSENGERS) ===\n\n", n);

    /* Order 1: Slow check FIRST: verify_disability_card() || (senior && eligible) */
    slow_calls = 0; audit_entries = 0;
    int granted1 = 0;
    for (int i = 0; i < n; i++) {
        if (verify_disability_card(ids[i], disability[i]) || (senior[i] && eligible[i])) {
            granted1++;
        }
    }
    printf("1. Slow check FIRST  [verify() || (senior && eligible)] -> Slow calls: %4d | Granted: %d\n",
           slow_calls, granted1);

    /* Order 2: Cheap checks FIRST: (senior && eligible) || verify_disability_card() */
    slow_calls = 0; audit_entries = 0;
    int granted2 = 0;
    for (int i = 0; i < n; i++) {
        if ((senior[i] && eligible[i]) || verify_disability_card(ids[i], disability[i])) {
            granted2++;
        }
    }
    printf("2. Cheap check FIRST [(senior && eligible) || verify()] -> Slow calls: %4d | Granted: %d\n",
           slow_calls, granted2);

    /* Order 3: Bitwise non-short-circuit (& and |) */
    slow_calls = 0; audit_entries = 0;
    int granted3 = 0;
    for (int i = 0; i < n; i++) {
        if ((senior[i] & eligible[i]) | verify_disability_card(ids[i], disability[i])) {
            granted3++;
        }
    }
    printf("3. Bitwise (& and |) [(senior & eligible) | verify()]   -> Slow calls: %4d | Granted: %d\n",
           slow_calls, granted3);

    /* Changed Condition: Audit log requires recording EVERY disability-card applicant */
    slow_calls = 0; audit_entries = 0;
    int granted4 = 0;
    for (int i = 0; i < n; i++) {
        int card_ok = verify_disability_card(ids[i], disability[i]);
        if (card_ok || (senior[i] && eligible[i])) {
            granted4++;
        }
    }
    printf("4. Audit-Mandatory Order (verify() always logged)       -> Slow calls: %4d | Audit rows: %d\n",
           slow_calls, audit_entries);

    return 0;
}

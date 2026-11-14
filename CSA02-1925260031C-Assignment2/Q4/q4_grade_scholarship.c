#include <stdio.h>

char grade_elseif(int marks) {
    if (marks < 0 || marks > 100) return '?';
    else if (marks >= 90) return 'S';
    else if (marks >= 80) return 'A';
    else if (marks >= 70) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 50) return 'D';
    else return 'F';
}

char grade_switch(int marks) {
    if (marks < 0 || marks > 100) return '?';
    switch (marks / 10) {
        case 10:
        case 9:  return 'S';
        case 8:  return 'A';
        case 7:  return 'B';
        case 6:  return 'C';
        case 5:  return 'D';
        default: return 'F';
    }
}

char grade_switch_fallthrough_bug(int marks) {
    if (marks < 0 || marks > 100) return '?';
    char g = '?';
    switch (marks / 10) {
        case 10:
        case 9: g = 'S'; break;
        case 8: g = 'A'; /* MISSING break! Falls through into case 7 */
        case 7: g = 'B'; break;
        case 6: g = 'C'; break;
        case 5: g = 'D'; break;
        default: g = 'F'; break;
    }
    return g;
}

char grade_lookup(int marks) {
    if (marks < 0 || marks > 100) return '?';
    static const char grades[11] = {'F','F','F','F','F','D','C','B','A','S','S'};
    return grades[marks / 10];
}

const char* scholarship_category(char g, int annual_income) {
    if (annual_income < 0) return "Invalid Income";
    switch (g) {
        case 'S':
            if (annual_income <= 250000) return "100% Merit-cum-Means Waiver";
            else if (annual_income <= 600000) return "75% Merit Scholarship";
            else return "50% Chancellor Honor Waiver";
        case 'A':
            if (annual_income <= 250000) return "75% Merit-cum-Means Waiver";
            else if (annual_income <= 600000) return "40% Merit Scholarship";
            else return "No Scholarship";
        case 'B':
            if (annual_income <= 200000) return "25% Need-Based Grant";
            else return "No Scholarship";
        default:
            return "Not Eligible";
    }
}

int main(void) {
    int boundary_tests[] = {101, 100, 90, 89, 80, 79, 50, 49, 0, -1};
    int n = sizeof(boundary_tests) / sizeof(boundary_tests[0]);

    printf("=== Q4: BOUNDARY & IMPLEMENTATION COMPARISON ===\n");
    printf("Marks | else-if | switch | Lookup | Fall-through Bug\n");
    printf("------+---------+--------+--------+-----------------\n");
    for (int i = 0; i < n; i++) {
        int m = boundary_tests[i];
        printf("%5d |    %c    |   %c    |   %c    |        %c\n",
               m, grade_elseif(m), grade_switch(m), grade_lookup(m), grade_switch_fallthrough_bug(m));
    }

    printf("\n=== SCHOLARSHIP CLASSIFICATION ===\n");
    printf("Grade S, Income 200,000 -> %s\n", scholarship_category('S', 200000));
    printf("Grade A, Income 450,000 -> %s\n", scholarship_category('A', 450000));
    printf("Grade B, Income 180,000 -> %s\n", scholarship_category('B', 180000));
    printf("Grade C, Income 100,000 -> %s\n", scholarship_category('C', 100000));
    return 0;
}

# CSA02 - C Programming: Assignment 2 (CO2)
**Operators, Decision-Making, Looping Constructs & Algorithmic Optimization**

- **Student Name:** Divya Dharshan
- **Register Number:** 1925260031C
- **Repository Name:** `CSA02-1925260031C-Assignment2`
- **Compiler & Version:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`

## Repository Structure
```
CSA02-1925260031C-Assignment2/
├── README.md
├── Q1/
│   ├── q1_pharmacy_billing.c
│   ├── Q1_Analysis.md
│   └── output_log.txt
├── Q2/
│   ├── q2_short_circuit.c
│   ├── passengers_1000.csv
│   ├── Q2_Analysis.md
│   └── output_log.txt
├── Q3/
│   ├── q3_complete_code.c
│   ├── q3_smart_home_register.c
│   ├── Q3_Analysis.md
│   └── output_log.txt
├── Q4/
│   ├── q4_complete_code.c
│   ├── q4_grade_scholarship.c
│   ├── Q4_Analysis.md
│   └── output_log.txt
├── Q5/
│   ├── q5_complete_code.c
│   ├── q5_prime_loops.c
│   ├── Q5_Analysis.md
│   └── output_log.txt
├── Q6/
│   ├── q6_loan_schedule.c
│   ├── Q6_Analysis.md
│   └── output_log.txt
└── Q7/
    ├── q7_prime_redesign.c
    ├── Q7_Design_Challenge.md
    └── output_log.txt
```

## Exact GCC Compilation & Execution Commands
All programs compile cleanly with strict warning flags (`-Wall -Wextra -std=c11`):
```bash
# Q1: Precedence, Associativity & Discount Bug
gcc -Wall -Wextra -std=c11 Q1/q1_pharmacy_billing.c -o Q1/q1_pharmacy_billing
./Q1/q1_pharmacy_billing

# Q2: Short-Circuit Evaluation & Audit Log Trade-off
gcc -Wall -Wextra -std=c11 Q2/q2_short_circuit.c -o Q2/q2_short_circuit
./Q2/q2_short_circuit

# Q3: Bitwise Device-Status Register (Complete the Code + Full Popcount/Register Demo)
gcc -Wall -Wextra -std=c11 Q3/q3_complete_code.c -o Q3/q3_complete_code
./Q3/q3_complete_code
gcc -Wall -Wextra -std=c11 Q3/q3_smart_home_register.c -o Q3/q3_smart_home_register
./Q3/q3_smart_home_register

# Q4: else-if Ladder vs switch vs Lookup Table
gcc -Wall -Wextra -std=c11 Q4/q4_complete_code.c -o Q4/q4_complete_code
./Q4/q4_complete_code
gcc -Wall -Wextra -std=c11 Q4/q4_grade_scholarship.c -o Q4/q4_grade_scholarship
./Q4/q4_grade_scholarship

# Q5: Prime Verification Loops (for, while, do-while & Sieve Comparison)
gcc -Wall -Wextra -std=c11 Q5/q5_complete_code.c -o Q5/q5_complete_code
./Q5/q5_complete_code
gcc -Wall -Wextra -std=c11 Q5/q5_prime_loops.c -o Q5/q5_prime_loops -lm
./Q5/q5_prime_loops

# Q6: Self-Help Group Micro-Loan Repayment Schedule
gcc -Wall -Wextra -std=c11 Q6/q6_loan_schedule.c -o Q6/q6_loan_schedule -lm
./Q6/q6_loan_schedule

# Q7: Day-4 Design Challenge (6k +/- 1 Trial Division Redesign & Validation)
gcc -Wall -Wextra -std=c11 Q7/q7_prime_redesign.c -o Q7/q7_prime_redesign
./Q7/q7_prime_redesign
```

## Summary of Results
- **Q1 (Precedence & Associativity):** Demonstrated how missing parentheses in `price * qty * 15 / 100 * senior` cause premature integer truncation (`0` when `price * qty < 7`) and explained why `count = count++ + 1` triggers `-Wsequence-point` undefined behavior. Verified corrected intermediate-variable calculation.
- **Q2 (Short-Circuit Evaluation):** Measured slow server verification calls across 1,000 passengers: placing the cheapest, most-likely-false check first cut calls from **1,000** (bitwise `&`/`|`) down to **753** (`&&`/`||`). Re-ordered checks when audit logging is mandatory.
- **Q3 (Bitwise Smart-Home Register):** Implemented `switch_on`, `switch_off`, `toggle`, `is_on`, binary display, and Brian Kernighan's bit-count in 1 byte (`unsigned char`), saving **~6.68 MB** across 1,000,000 homes compared to `char state[8]`.
- **Q4 (Decision Structures):** Compared `else-if`, `switch (marks / 10)`, and $O(1)$ lookup table across boundary values (`100, 90, 89, 0, -1, 101`), demonstrated `switch` fall-through when `break` is omitted, and designed a clean scholarship classifier.
- **Q5 (Loop Work Counts):** Reduced divisions for `1,000,003` from **1,000,001** ($O(n)$) to **999** ($O(\sqrt{n})$) using `i <= n / i` (avoiding `i * i` overflow), verified across `for`, `while`, `do-while`, and compared with $O(N \log \log N)$ Sieve of Eratosthenes.
- **Q6 (Loan Termination):** Implemented `while (balance > 0.005)` with a `360`-month safety `break`, verified against hand-calculated Rs 10,000 loan (6 months, Rs 645.38 total interest), and analyzed divergence as repayment approaches monthly interest.
- **Q7 (Design Challenge):** Redesigned prime verification using $6k \pm 1$ wheel factorization (skipping multiples of 2 and 3), reducing divisions for `1,000,003` from **999** down to **333** (**66.7% reduction**).

> **Note on Git Commits:** Commit each folder (`Q1` through `Q7`) individually with clear commit messages so the progressive commit history is visible.

# Q6 – Loops That Must Terminate: Loan Repayment Schedule (8 Marks | K5 – Evaluate)

## 1. Loop Design & Termination Analysis
- **Why `while` Matches Best:** The number of months is unknown prior to execution (entry-controlled), and if `principal == 0`, zero iterations should run (`do-while` would wrongly execute Month 1).
- **Why `balance != 0` Is Dangerous with Floating-Point:** Binary IEEE-754 floating-point cannot represent decimal fractions like `0.02` exactly, leaving tiny residual dust (`1.13e-13` or `-2.27e-13`), which causes `balance != 0.0` to loop infinitely. Using **`while (balance > 0.005)`** (half a paisa tolerance) guarantees clean termination.
- **Final Month Handling:** When `opening + interest < emi`, the borrower pays only `payment = opening + interest` so `balance` becomes `0.0` instead of overpaying into a negative balance.
- **Repayment $\le$ Monthly Interest ($E \le P \cdot r$):** If repayment does not exceed monthly interest (`Rs 200` on `Rs 10,000` at `2%`), `balance` stays constant or grows exponentially—an **infinite loop** unless guarded.

## 2. Hand-Verified Schedule (`Rs 10,000` at `2%/month`, `Rs 2,000` Repayment)
| Month | Opening Balance | Interest (`2%`) | Repayment | Closing Balance |
| :---: | :---: | :---: | :---: | :---: |
| **1** | 10,000.00 | 200.00 | 2,000.00 | 8,200.00 |
| **2** | 8,200.00 | 164.00 | 2,000.00 | 6,364.00 |
| **3** | 6,364.00 | 127.28 | 2,000.00 | 4,491.28 |
| **4** | 4,491.28 | 89.83 | 2,000.00 | 2,581.11 |
| **5** | 2,581.11 | 51.62 | 2,000.00 | 632.73 |
| **6** | 632.73 | 12.65 | 645.38 | 0.00 |
| **Total** | — | **Rs 645.38** | **Rs 10,645.38** | — |

## 3. Deployment Decision (360-Month Safety `break`)
- **Decision:** Enforce `if (month >= 360) break;` (30-year maximum tenure) and emit an explicit diagnostic message: `"ALERT: Safety limit of 360 months reached! Repayment is insufficient to amortize interest."`
- **Defence:** Prevents CPU hangs in production banking services while distinguishing an unserviceable loan from a normal completed schedule.

## 4. Alternative Concept & Complexity Analysis (`n = -log(1 - r*P/E) / log(1 + r)`)
- **Closed-Form Formula:**
  - **Time Complexity:** **$O(1)$** (two `log()` transcendental calls regardless of tenure) vs. **$O(n)$** iterations for monthly simulation.
  - **Space Complexity:** **$O(1)$** in both.
  - **Precision & Domain Trade-Offs:** When $r \cdot P / E \approx 1$, `1 - r*P/E` suffers **catastrophic floating-point cancellation**, and if $E \le r \cdot P$, the argument to `log()` is $\le 0$, producing `NaN`/`-inf`. Furthermore, the closed-form formula only gives the total month count—it cannot generate the month-by-month amortization table or handle irregular final-month rounding.

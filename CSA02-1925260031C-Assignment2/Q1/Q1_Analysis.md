# Q1 – Precedence, Associativity and the Discount Bug (6 Marks | K4 – Analyse)

## 1. Pre-Execution Predictions & Operator-by-Operator Trace
### C Precedence & Associativity Rules Applied
1. **Multiplicative (`*`, `/`)** — Precedence Level 3, **Left-to-Right** associativity.
2. **Additive (`+`, `-`)** — Precedence Level 4, **Left-to-Right** associativity.
3. **Relational (`>`)** — Precedence Level 6, **Left-to-Right** associativity.
4. **Conditional (`?:`)** — Precedence Level 13, **Right-to-Left** associativity.
5. **Assignment (`=`)** — Precedence Level 14, **Right-to-Left** associativity.

### Step-by-Step Evaluation of Buggy Expression
`total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;`
Because `*` and `/` share equal precedence and associate **left-to-right**, each multiplicative chain evaluates left-to-right before `-` and `+`:
- Term A: `(price * qty)`
- Term B: `((((price * qty) * 15) / 100) * senior)`
- Term C: `(((price * qty) * 5) / 100)`
- Result: `(Term A - Term B) + Term C`

### Predictions for Three Bills
| Test Case | Inputs (`price, qty, senior`) | Buggy Predicted (`total`, `net`) | Pharmacist Intended (`total`, `net`) | Discrepancy Cause |
| :--- | :--- | :--- | :--- | :--- |
| **Bill 1** | `6, 1, 1` | `total = 6 - 0 + 0 = 6`, `net = 6` | `6 - 0.90 + 0.255 = 5.36` (int: `6`) | Integer division `(6*15)/100 = 0` wipes out the 15% senior discount completely. |
| **Bill 2** | `500, 3, 1` | `total = 1500 - 225 + 75 = 1350`, `net = 1300` | `gross=1500, disc=225, taxable=1275, gst=63, total=1338, net=1288` | Buggy code computes 5% GST on full `gross` (`1500`) instead of post-discount `taxable` (`1275`), overcharging Rs 12. |
| **Bill 3** | `250, 4, 0` | `total = 1000 - 0 + 50 = 1050`, `net = 1000` | `total = 1050, net = 1000` | Matches when `senior == 0` and `gross` is a multiple of 100. |

---

## 2. Inquiry: Undefined Behaviour in `count = count++ + 1;`
- **Why It Is Undefined Behaviour (UB):** Under the C11 standard (Section 6.5/2), modifying a scalar object (`count++`) and writing to the same object (`count = ...`) without an intervening sequence point causes **undefined behaviour**. The compiler is free to store the incremented value before or after the assignment, yielding `6`, `7`, or arbitrary values depending on optimization level (`-O0` vs `-O2`).
- **Compiler Diagnostic (`gcc -Wall`):** GCC emits:
  `warning: operation on 'count' may be undefined [-Wsequence-point]`

---

## 3. Design Decision & Alternative Concept Complexity Analysis
- **Decision:** Use **both intermediate variables (`gross`, `discount`, `taxable`, `gst`) and explicit parentheses** so business rules (GST on post-discount price) are self-documenting and immune to precedence bugs.
- **Alternative Concept Comparison (Single Expression vs. Intermediate Variables):**
  - **Time Complexity:** **$O(1)$** in both. Modern compilers (`gcc -O1`/`-O2`) perform copy propagation and register allocation, compiling both versions to identical machine instructions (zero extra runtime cycles).
  - **Space Complexity:** **$O(1)$**. Intermediate `int` variables live in CPU registers (or 4 bytes each on the stack frame in `-O0`), adding negligible memory overhead (~16 bytes max) while dramatically improving maintainability and debuggability.

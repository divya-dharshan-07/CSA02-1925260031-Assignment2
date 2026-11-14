# Q2 – When Does Short-Circuit Evaluation Matter? (4 Marks | K4 – Analyse)

## 1. Mechanics of Short-Circuit Evaluation (`&&` vs `||` vs `&`)
- **Logical AND (`A && B`):** Evaluates `A` first. If `A` is `0` (false), `B` is **not evaluated** because `0 && anything` is guaranteed to be `0`.
- **Logical OR (`A || B`):** Evaluates `A` first. If `A` is non-zero (true), `B` is **not evaluated** because `1 || anything` is guaranteed to be `1`.
- **Bitwise AND/OR (`A & B`, `A | B`):** Evaluates **both** operands unconditionally regardless of the left operand's truth value, and performs bit-by-bit arithmetic (which can fail if truthy integers have non-overlapping bits, e.g., `1 & 2 == 0`).

## 2. Ordering Rules & When Order Is Irrelevant
- **For `&&` (Conjunction):** Place the **cheapest and most-likely-false** condition first (`senior && eligible`) so evaluation aborts early at near-zero cost.
- **For `||` (Disjunction):** Place the **cheapest and most-likely-true** condition first (`(senior && eligible) || verify_disability_card()`) so true cases skip the expensive remote verification call.
- **When Order Is Irrelevant:** When all operands are pure, side-effect-free register variables of equal O(1) cost (e.g., `a > 0 && b > 0`), or when bitwise `&` / `|` forces evaluation of all operands.

## 3. Changed Condition: Mandatory Audit Logging
- **Re-evaluation:** If `verify_disability_card()` writes a mandatory compliance record to an audit log, placing it second in `(senior && eligible) || verify_disability_card()` **skips logging** whenever a passenger is already an eligible senior citizen!
- **Revised Recommendation:** Place `verify_disability_card()` first (or evaluate `int card_ok = verify_disability_card(...)` before the `if`) whenever side effects such as audit logging are legally required, accepting the $O(n)$ server call cost for compliance completeness.

## 4. Alternative Concept & Complexity Analysis
- **Nested `if` Statements:**
  ```c
  if (senior) {
      if (eligible) granted++;
      else if (verify_disability_card()) granted++;
  } else if (verify_disability_card()) {
      granted++;
  }
  ```
  - *Calls to slow function:* Identical to short-circuit `&&`/`||` ($k \le n$ calls, skipping eligible seniors), **Time: $O(n)$** with smaller constant factor, but duplicates the `verify_disability_card()` branch.
- **Bitwise `&` and `|`:**
  - *Calls to slow function:* Always executes **$n$ calls** (1,000/1,000) because no short-circuiting occurs, **Time: $O(n)$** with maximum network latency.

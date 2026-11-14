# Q4 – else–if Ladder or switch? (6 Marks | K4 – Analyse)

## 1. Boundary Behaviour & Fall-Through Analysis
- **Boundary Verification (`100, 90, 89, 0, -1, 101`):**
  - Both `else-if` and `switch (marks / 10)` (with explicit `if (marks < 0 || marks > 100) return '?';` guard) handle all boundary values identically: `100 -> S`, `90 -> S`, `89 -> A`, `0 -> F`, `-1 -> ?`, `101 -> ?`.
  - *Crucial Trap:* Without the range guard first, `-5 / 10 == 0` in C (truncation toward zero), which would falsely enter `default` (`'F'`) instead of `'?'`, and `105 / 10 == 10` would falsely match `case 10:` (`'S'`)!
- **Effect of Missing `break` (Fall-Through):**
  - If `break` (or `return`) is removed from `case 8:`, execution falls straight into `case 7:`, overwriting `'A'` with `'B'` so `83` outputs `'B'` instead of `'A'`.
- **Why `switch` Cannot Test Arbitrary Ranges (`75–84`):**
  - Standard ISO C `switch` requires **integer constant expressions** (`case 75:`) and lacks GNU range syntax (`case 75 ... 84:`) in portable C11. Because `75 / 10 == 7` and `84 / 10 == 8` overlap with `70–74` and `85–89`, integer division cannot isolate `75–84`.
- **Ease of Boundary Modification:**
  - The **`else-if` ladder** is far easier to modify when boundaries shift to non-multiples of 10 (e.g., `S >= 92`, `A >= 85`), whereas `switch (marks / 10)` breaks completely if boundaries are not aligned to multiples of 10.

## 2. Design Decision: Scholarship Rule Structure
- **Chosen Structure:** **`switch (grade)` outer dispatch with `else-if` income bands inside each case**.
- **Defence:** `grade` is a discrete single-character enum/domain (`'S'`, `'A'`, `'B'`, etc.), making `switch` clean and exhaustive, while `annual_income` is a continuous numeric range (`<= 250000`, `<= 600000`), which maps naturally to `else-if` range checks without deeply nested pyramids.

## 3. Alternative Concept & Complexity Analysis (Lookup Table `grades[11]`)
- **Time Complexity:**
  - *Lookup Table (`grades[marks / 10]`):* **$O(1)$** worst-case and average-case (1 division + 1 array offset load, zero branches).
  - *`else-if` Ladder:* **$O(k)$** comparisons where $k = 6$ grade tiers (1 comparison for `'S'`, up to 6 comparisons for `'F'`).
- **Space Complexity:**
  - *Lookup Table:* **$O(1)$** — exactly **11 bytes** (`static const char grades[11]`) in `.rodata` read-only memory.

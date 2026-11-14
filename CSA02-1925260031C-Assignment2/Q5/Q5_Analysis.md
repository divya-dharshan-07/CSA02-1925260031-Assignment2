# Q5 – Count the Work Done by a Loop (7 Marks | K4 – Analyse)

## 1. Derivation of the Loop Condition & Early Exit
- **Mathematical Principle:** If $n = a \times b$ is composite, both factors cannot exceed $\sqrt{n}$ (otherwise $a \times b > \sqrt{n} \times \sqrt{n} = n$). Hence at least one factor satisfies $i \le \sqrt{n}$, which is equivalent to $i^2 \le n$ or **$i \le \lfloor n / i \rfloor$** without calling `sqrt()`.
- **Early Termination:** `if (n % i == 0) return 0;` immediately exits on the smallest factor (`i = 2` for `100`, taking **1 division** instead of 9).

## 2. Inquiry: `do–while` Boundary Cases & `i * i` Overflow
1. **Why `do–while` Needs Special Care for $n = 2$ and $n = 3$:**
   - A `do–while` loop executes its body **at least once before checking the condition**.
   - For $n = 2$ (and $n = 3$), starting at $i = 2$ would execute `2 % 2 == 0` inside the body before evaluating `while (2 <= 2 / 2)`, falsely classifying `2` as composite! Adding `if (n == 2 || n == 3) return 1;` prevents this bug.
2. **Why `i * i <= n` Can Overflow:**
   - If `n` is close to `ULONG_MAX` (e.g., `4294967291` on 32-bit `unsigned long`), when `i = 65536`, `i * i` wraps around modulo $2^{32}$ to `0`, making `0 <= n` permanently true and causing an **infinite loop**.
   - Writing **`i <= n / i`** is completely overflow-safe for all positive integers.

## 3. Alternative Concept & Complexity Analysis (Sieve of Eratosthenes)
| Metric | Trial Division ($O(\sqrt{n})$) | Sieve of Eratosthenes |
| :--- | :--- | :--- |
| **Precomputation Time** | **$O(1)$** (none) | **$O(N \log \log N)$** (~1.94M markings once for $N = 1,000,003$) |
| **Time per Ticket Query** | **$O(\sqrt{n})$** (up to 999 divisions) | **$O(1)$** (single array lookup `is_prime[ticket]`) |
| **Space Complexity** | **$O(1)$** (~32 bytes of stack scalars) | **$O(N)$** (~976 KB byte-array for $N = 10^6$) |
| **Best Use Case** | Checking a handful of tickets ($Q < 1,000$) | High-throughput fest booth verifying tens of thousands of tickets |

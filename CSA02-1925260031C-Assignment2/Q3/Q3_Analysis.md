# Q3 – Engineer a Device-Status Register with Bitwise Operators (6 Marks | K4 – Analyse)

## 1. Pre-Execution Register Prediction (`main()` Trace)
| Statement in `main()` | Binary (`bit 7..0`) | Decimal | Devices ON |
| :--- | :--- | :--- | :--- |
| `unsigned char reg = 0;` | `00000000` | `0` | None |
| `reg = switch_on(reg, LIGHT);` (`dev=0`) | `00000001` | `1` | `LIGHT` |
| `reg = switch_on(reg, AC);` (`dev=2`) | `00000101` | `5` | `LIGHT, AC` |
| `reg = toggle(reg, FAN);` (`dev=1`) | `00000111` | `7` | `LIGHT, FAN, AC` |
| `reg = switch_off(reg, LIGHT);` (`dev=0`) | `00000110` | `6` | `FAN, AC` |

---

## 2. Inquiry: Precedence & Signedness Hazards
1. **`reg & 1 << dev` vs. `(reg & 1) << dev`:**
   - Bitwise shift (`<<`) has **higher precedence** than bitwise AND (`&`).
   - Thus `reg & 1 << dev` parses as `reg & (1 << dev)`, creating a mask at bit `dev` and testing bit `dev` of `reg`.
   - Conversely, `(reg & 1) << dev` masks bit `0` of `reg` first (`0` or `1`) and shifts that LSB left by `dev` positions—completely ignoring bit `dev`!
2. **Using `signed char` When Bit 7 Is Set:**
   - On 8-bit two's-complement systems, bit 7 is the **sign bit** (`10000000` = `-128`).
   - Performing `1 << 7` on a 32-bit `int` gives `128`, which overflows `signed char` (`[-128, 127]`) upon assignment (implementation-defined).
   - Worse, right-shifting a negative `signed char` (`reg >> 7`) performs an **arithmetic shift** (sign-extension), filling upper bits with `1`s (`11111111` = `-1` instead of `1`), breaking `is_on()`. Always use `unsigned char` and `1u`.

---

## 3. Alternative Concept & Complexity Analysis (`char state[8]` vs. Bitwise `unsigned char`)
| Metric | Bitwise `unsigned char` (1 Byte) | Byte Array `char state[8]` (8 Bytes) |
| :--- | :--- | :--- |
| **Set / Clear / Toggle / Test** | **$O(1)$** (1–2 CPU ALU bit instructions) | **$O(1)$** (1 indexed memory load/store `state[dev]`) |
| **Count ON Devices** | **$O(k)$** where $k \le 8$ set bits via `reg &= (reg - 1)` (or $O(1)$ hardware `POPCNT`) | **$O(8) = O(1)$** (must loop over all 8 array elements unconditionally) |
| **Space for 1,000,000 Homes** | **$1,000,000\text{ bytes} \approx 0.95\text{ MB}$** | **$8,000,000\text{ bytes} \approx 7.63\text{ MB}$** (**8x more RAM**, higher L1/L2 cache misses) |

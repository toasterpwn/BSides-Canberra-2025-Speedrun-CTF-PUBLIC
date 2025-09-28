# fib

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Tiebreaker (Finals)     |   ssparrow    | SlidyBat    | SlidyBat    |

<details>
  <summary>(SPOILER) Writeup</summary>

The binary XORs the input with fibonacci numbers, and then compares with a string:
```c
004015f6            while (sx.q(var_238_1) u< strlen(&buf))
00401597                int32_t var_234_1 = var_240
004015a3                var_240 += var_23c
004015af                var_23c = var_234_1
004015d5                *(&var_128 + sx.q(var_238_1)) = var_240.b ^ *(&buf + sx.q(var_238_1))
004015dc                var_238_1 += 1
004015dc            
00401620            if (memcmp(&var_128, "@PLLHF", 0xb) != 0)
00401651                puts(str: "password WRONG!")
00401656                result = 1
00401620            else
0040163b                printf(format: "Correct! Your flag is bsides{%s}\n", &buf)
00401640                result = 0
```
Simply reproduce the sequence and XOR with the encrypted string to get the flag.
</details>

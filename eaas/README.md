# eaas

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Tiebreaker (Unused)     |   N/A   | N/A  | N/A   |

<details>
  <summary>(SPOILER) Writeup</summary>

User input is passed directly to printf
```c
while (1) {
      printf("[EAAS]> ");
      read(0, input, sizeof(input));
      printf(input);
  }
```
Since the flag was read onto the stack, you can trivially leak it off by passing `%<number>$x`

</details>

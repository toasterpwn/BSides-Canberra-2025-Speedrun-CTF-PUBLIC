# stack

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Quals     | N/A      | N/A      | N/A    |

Quals times:
- 1\. **ssparrow** — 7.17 — 99
- 2\. **ItsIronicIInsist** — 9.56 — 99
- 3\. **Sly** — 11.38 — 99
- 4\. **Slidybat** — 12.57 — 99
- 5\. **hashkitten** — 13.56 — 99
- 6\. **Gorg** — 14.06 — 99

<details>
  <summary>(SPOILER) Writeup</summary>

Stack push/pop operations lack bounds checks:
```c
void push(int8_t* stack, int8_t val) {
	stack[sp] = val;
	sp++; // can go OOB
}

void pop(int8_t* stack) {
	r = stack[sp];
	sp--; // can go OOB
}
```
We can pop the `sp` to land on `exit@got`, then push each byte of the win function, and exit the program.
</details>

# numbers

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn |  Finals    |   ItsIronicIInsist   | stackotter  | ItsIronicIInsist |

<details>
  <summary>(SPOILER) Writeup</summary>

If you pass a large enough size to malloc, it can fail. 
```c
 numbers = malloc(num_numbers * sizeof(unsigned short)); // can fail
```
Now, writes are offset from `0`, allowing for arbitrary write, so we can overwrite `exit@got` with `win`.

</details>

# postcard

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Finals     |   ssparrow    | teddy    | ssparrow    |

<details>
  <summary>(SPOILER) Writeup</summary>

There are 2 buffer overflows:
```c
ret = read(0, name, 0x100);
if (name[ret - 1] == '\n') {
    name[ret - 1] = 0;

}
printf("Enter the message to send to %s: ", name);
ret = read(0, message, 0x100);
if (message[ret - 1] == '\n') {
    message[ret - 1] = 0;

}
```
Use the first to overwrite the null byte of the canary, which is returned back via `printf`. Use the second to corrupt the saved return address and jump to the `win` function.
</details>

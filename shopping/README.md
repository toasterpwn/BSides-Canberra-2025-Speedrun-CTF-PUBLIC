# shopping

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Finals     |   ssparrow    | slidybat    | N/A    |

<details>
  <summary>(SPOILER) Writeup</summary>

`snprintf` return value can be larger than it's length parameter:
```c
ret = snprintf(listp, sizeof(list) - listlen, "%d) %s\n", idx, item); // ret can be longer than expected if the string gets truncated
puts(list);
listp += ret;
listlen += ret;
idx++;
```
We can overflow out of the list buffer and over the canary to corrupt the return address with the win function.

</details>

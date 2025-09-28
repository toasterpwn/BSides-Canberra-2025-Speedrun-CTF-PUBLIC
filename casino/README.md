# casino

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Tiebreaker (unused)     |   N/A   | N/A    | N/A   |

<details>
  <summary>(SPOILER) Writeup</summary>

The program does not validate that you have bet a positive amount:
```py
amount = int(input("Amount? "))
if amount > PLAYER_MONEY:
    print("You don't have enough money!")
    exit()

number = int(input("Lucky number? "))
delta = roulette(number, amount)
PLAYER_MONEY += delta
```
We can bet negative, lose, and get essentially unlimited money. 
</details>

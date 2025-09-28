# toasterpwn

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| HexF | Finals |   Gorg    | SlidyBat | SlidyBat |

<details>
  <summary>(SPOILER) Writeup</summary>

The toasterpwn challenge is a hardware challenge which mimics a 'smart toaster', with profiles. The flag is printed after a 1 hour long toast runs, which needs to be reduced to a reasonable time.
RP2040 (and lots of other MCUs) mirror RAM in different regions. The code blacklists writing to specific memory addresses for the different toasting profiles, but does not block writing to one of the mirrors.
</details>

# oracle

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Quals     | N/A      | N/A      | N/A    |

No Solves during the qualifiers

<details>
  <summary>(SPOILER) Writeup</summary>

Abuse RSA's multiplicative homomorphic property:
```math
\begin{aligned}
E(\texttt{flag}) &= (\texttt{flag})^e \pmod{n} \\
E(2) &= 2^e \pmod{n} \\
E(\texttt{flag}) \cdot E(2) &= (\texttt{flag}^e)(2^e) \equiv (2 \cdot \texttt{flag})^e \pmod{n} \\
D(E(\texttt{flag}) \cdot E(2)) &= (2 \cdot \texttt{flag})^{ed} \equiv 2 \cdot \texttt{flag} \pmod{n} \\
\therefore \quad \frac{D(E(\texttt{flag}) \cdot E(2))}{2} &= \texttt{flag}
\end{aligned}
```
</details>

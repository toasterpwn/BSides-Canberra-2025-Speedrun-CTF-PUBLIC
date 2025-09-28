# realsmooth

|   Author   | **Round** | **Player 1** | **Player 2** | **Winner** |
|------------|-------|----------|----------|--------|
| toasterpwn | Finals     |   hashkitten    | slidybat    | slidybat    |

<details>
  <summary>(SPOILER) Writeup</summary>

Identify chacha20 strings in the binary:
```c
00401f09            
00401f0d            if (result == 0)
00401f32                __assert_fail(assertion: "0 != counter[1]", file: "chacha20.c", line: 0x59, 
00401f32                    function: "chacha20_block_next")
```

You can either notice that the chacha20 constant has changes as so, and decrypt using the new constant:
```c
0040151f        *(arg1 + 0x80) = sub_40145b("Expand-32-byte k")
00401539        *(arg1 + 0x84) = sub_40145b("nd-32-byte k")
00401553        *(arg1 + 0x88) = sub_40145b("2-byte k")
0040156d        *(arg1 + 0x8c) = sub_40145b("te k")
```
Or, feed the encrypted flag in the binary back through as the input, break on memcmp, and the flag will be in `rdi`:
```bash
pwndbg> b memcmp
Breakpoint 1 at 0x1090
pwndbg> r < flag.enc
Starting program: /home/debian/ctf/speedrun/chal < flag.enc
/bin/bash: warning: setlocale: LC_ALL: cannot change locale (en_AU.UTF-8)
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Enter your input:
Breakpoint 1, 0x00007ffff7f2f260 in ?? () from /lib/x86_64-linux-gnu/libc.so.6
LEGEND: STACK | HEAP | CODE | DATA | WX | RODATA
─────────────────────────────────────────────────────────────────────────
 RAX  0x7fffffffe130 ◂— 'bsides{d0ubl3_ch3ck_y0ur_c0nst4nts!}\n'
 RBX  0x7fffffffe358 —▸ 0x7fffffffe5c2 ◂— '/home/debian/ctf/speedrun/chal'
 RCX  0x555555559080 ◂— 0x44f8b39fcc7e3ae1
 RDX  0x100
 RDI  0x7fffffffe130 ◂— 'bsides{d0ubl3_ch3ck_y0ur_c0nst4nts!}\n'
```
</details>

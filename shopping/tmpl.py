from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0 # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()

io = r = p # use whichever you like for communication

def add(name):
    p.sendafter(b": ", name)
    return p.recvuntil(b"Enter", drop=True)

def exit_prog():
    p.sendafter(b": ", b"\n")


add_item("Bread")



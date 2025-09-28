from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0 # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()

io = r = p # use whichever you like for communication

def echo(text):
    p.sendlineafter(b"[EAAS]> ", text)
    return p.recvline().decode().strip();


echo("joseph")

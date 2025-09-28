from pwn import *
from Crypto.Util.number import long_to_bytes, bytes_to_long
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0  # Change to 1 to run the exploit on the remote instance

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = process(["python3", "src.py"])

io = r = p  # use whichever you like for communication


def encrypt(msg):
    p.sendlineafter(b"choice>", b"1")
    p.sendlineafter(b"message>", msg.hex().encode())
    p.recvuntil(b"ciphertext> ")
    return bytes.fromhex(p.recvline().decode().strip())


def decrypt(ct):
    p.sendlineafter(b"choice>", b"2")
    p.sendlineafter(b"ciphertext>", ct.hex().encode())
    p.recvuntil(b"message> ")
    return bytes.fromhex(p.recvline().decode().strip())


def encrypt_flag():
    p.sendlineafter(b"choice>", b"3")
    p.recvuntil(b"ciphertext> ")
    return bytes.fromhex(p.recvline().decode().strip())


# Good luck!

x = encrypt(b"AAA")
print(x)
print(decrypt(x))

print(decrypt(encrypt_flag()))

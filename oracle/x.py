from pwn import remote, process
from Crypto.Util.number import long_to_bytes as l2b, bytes_to_long as b2l

#p = process(["python3", "src.py"])
p = remote("127.0.0.1", 13337)

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

enc_flag = b2l(encrypt_flag())
enc_2 = b2l(encrypt(l2b(2)))

dec = b2l(decrypt(l2b(enc_flag * enc_2)))

print(l2b(dec // 2).decode())

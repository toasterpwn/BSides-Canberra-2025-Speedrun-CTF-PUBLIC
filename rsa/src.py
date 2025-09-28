from Crypto.Util.number import getStrongPrime, bytes_to_long
from secrets import randbelow
from math import gcd

m = bytes_to_long(open("flag.txt", "rb").read())

p = getStrongPrime(1024)
q = getStrongPrime(1024)

n = p * q
phi = (p - 1) * (q - 1)
e = randbelow(2**10)

while gcd(e, phi) != 1:
    e = randbelow(2**10)
    continue

c = pow(m, e, n)

print(f"{c = }")
print(f"{n = }")
print(f"{p = }")

PASSWORD = "BSIDES2025!"

curr = 1
prev = 1
tmp = 0

enc = []
key = []

for c in PASSWORD:
    tmp = curr
    curr += prev
    prev = tmp
    enc.append(ord(c) ^ curr)
    key.append(curr)

print(key)
print(enc)



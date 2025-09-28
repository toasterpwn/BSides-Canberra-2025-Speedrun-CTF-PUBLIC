from Crypto.Util.number import long_to_bytes, bytes_to_long, getPrime

flag = open("flag.txt", "rb").read()

p = getPrime(512)
q = getPrime(512)
n = p * q
e = 0x10001
d = pow(e, -1, (p-1) * (q-1))

def encrypt(msg):
    msg_long = bytes_to_long(msg)
    return long_to_bytes(pow(msg_long, e, n)).hex()

def decrypt(ct):
    ct_long = bytes_to_long(ct)
    pt = pow(ct_long, d, n)
    if pt == bytes_to_long(flag):
        return "deadbeef"
    return long_to_bytes(pt).hex()

def encrypt_flag():
    flag_long = bytes_to_long(flag)
    return long_to_bytes(pow(flag_long, e, n)).hex()

def main():
    while True:
        print("1. Encrypt message")
        print("2. Decrypt message")
        print("3. Get Encrypted flag")
        print("4. Exit")
        choice = int(input("choice> "))
        if choice == 1:
            msg = input("message> ")
            print("ciphertext>", encrypt(bytes.fromhex(msg)))
        elif choice == 2:
            ct = input("ciphertext> ")
            print("message>", decrypt(bytes.fromhex(ct)))
        elif choice == 3:
             print("ciphertext>", encrypt_flag())
        else:
            exit(0)
    
if __name__ == "__main__":
    main()

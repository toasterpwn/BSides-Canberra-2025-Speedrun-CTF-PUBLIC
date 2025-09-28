import secrets

FLAG_PRICE = 1000000000
PLAYER_MONEY = 10

FLAG = open("flag.txt").read()

def roulette(choice, amount):
    spin = secrets.randbelow(37)
    print(f"The wheel spins... landed on {spin}")
    if spin == choice:
        print("You win!")
        return amount * 35
    else:
        print("You lose!")
        return -amount

def main():
    global PLAYER_MONEY
    while True:
        print("1) Buy")
        print("2) Gamble")
        choice = int(input("Choice? "))

        if choice == 1:
            if PLAYER_MONEY > FLAG_PRICE:
                print("SOLD!")
                print(FLAG)
                exit()
            print("You can't afford that!")
        elif choice == 2:
            amount = int(input("Amount? "))
            if amount > PLAYER_MONEY:
                print("You don't have enough money!")
                exit()

            number = int(input("Lucky number? "))
            delta = roulette(number, amount)
            PLAYER_MONEY += delta

        else:
            print("Invalid choice")
            exit()


if __name__ == "__main__":
    main()

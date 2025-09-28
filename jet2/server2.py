import jwt # pip install pyjwt

FLAG = open("flag.txt", "r").read()

while True:
    boarding_pass = input("Boarding Pass: ")
    try:
        data = jwt.decode(boarding_pass, key=FLAG, algorithms=["HS256"])

        if data["cabin"] == "cockpit":
            print(f"Hello captain, here is todays flight plan: {FLAG}")
        else:
            print(f"Hello {data['name']}, please take your seat")
    except Exception:
        print("Error scanning")
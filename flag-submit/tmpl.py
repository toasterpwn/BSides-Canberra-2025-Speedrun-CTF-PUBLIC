from config import REMOTE_ADDR, REMOTE_PORT
import requests

def submit(flag):
    url = f"http://{REMOTE_ADDR}:{REMOTE_PORT}/submit"
    r = requests.post(url, json={"flag": flag})
    try:
        return r.json()
    except ValueError:
        return r.text

print(submit("abcd"))


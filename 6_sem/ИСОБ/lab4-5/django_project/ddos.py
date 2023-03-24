import requests
import threading 

all_done = False

def worker(i: int):
    global all_done    

    try:
        n = 1_000_000
        while (n:=n-1) > 0 and not all_done:
            r = requests.get('http://localhost:8000/')
            print(r.status_code)
            if not r.ok:
                all_done = True
                print(r.text)
                break
    except Exception:
        ...


for i in range(100):
    print(f"Worker {i} is in.")
    threading.Thread(target=worker, args=(i,)).start()

print("All workers are in.")





import requests
import threading 

all_done = False

def worker(i: int):
    global all_done    

    try:
        n = 1_000_000
        while (n:=n-1) > 0 and not all_done:
            #print(f'Worker {i} sent {1_000_000 - n}th request.')
            requests.get('http://localhost:8000', data='posts')
    except ConnectionError as ce:
        all_done = True
        print(ce)
    finally:
        print(f"Worker {i} is out")


for i in range(1_000):
    print(f"Worker {i} is in.")
    threading.Thread(target=worker, args=(i,)).start()

print("All workers are in.")





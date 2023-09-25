import asyncio

import numpy as np
from threading import Thread, Lock
from time import sleep
from enum import Enum

intensity_min = 0.4
service_time_min = 3

sec_multiplier = 1e-3
intensity = intensity_min / 60.
service_time = service_time_min * 60

def wait(sec = 1):
    sleep(sec * sec_multiplier)

class CMO:
    def __init__(self):
        self.locker = Lock()
        self.init_stats_items()
        
    
    def init_stats_items(self):
        self.current_time = 0
        self.completed_requests = 0
        self.rejected_requests = 0
        self.total_requests = 0
    
    
    def init_working_items(self):
        self.working = False
        self.timer: Thread
    
    
    def start_work(self):
        self.working = True
        self.current_time = 0
        self.timer = Thread(target=self.timer_worker, args=[self])
        self.timer.start()
        
        
    def stop_work(self):
        self.working = False
    
    
    def timer_worker(self):
        while self.working:
            wait(1)
            self.current_time += 1
    
    
    def process_request(self, request):
        if (not self.working):
            return
        
        self.all_requests += 1
        
        if self.locker.locked():
            self.reject_request(request)
            return
        
        self.accept_request(request)
    
    
    def accept_request(self, request):
        with (self.locker):
            request.proceed()
        self.completed_requests += 1
        
        
    def reject_request(self):
        self.rejected_requests += 1
        
        
    def get_stats(self):
        return {
            'current_time': self.current_time, 
            'total_requests': self.total_requests,
            'completed_requests': self.completed_requests,
            'rejected_requests': self.rejected_requests,
        }
    
    
class Status(Enum):
        NONE = 0
        REJECTED = 1
        COMPLETED = 2    

        
class Request:
    def __init__(self):
        self.status = Status.NONE
        self.service_time = np.random.exponential(service_time)
        self.worker: Thread

    def proceed(self):
        wait(self.service_time)
        self.status = Status.COMPLETED
        
        
class RequestSender():
    def __init__(self):
        ...
        
        
    def __start(self, cmo):
        while True:
            self.send_request(cmo)            
            wait(1)
            
          
    def start(self, cmo):
        self.worker = Thread(target=self.__start, args=(self, cmo))
        self.worker.start()
            
            
    def send_request(self, cmo):
        request = Request()
        cmo.process_request(request)
        
    

cmo = CMO()
sender = RequestSender()

sender.start(cmo)
cmo.start_work()

while True:
    print(cmo.working)
    print(cmo.get_stats())
    sleep(1)
from ast import Tuple
from threading import Thread, Event

class StoppableThread(Thread):
    """Thread class with a stop() method. The thread itself has to check
    regularly for the stopped() condition."""

    def __init__(self, *args, **kwargs):
        super(StoppableThread, self).__init__(*args, **kwargs)
        self._stop_event = Event()

    def stop(self):
        self._stop_event.set()

    def stopped(self):
        return self._stop_event.is_set()


class MyThread:
    def __init__(self, conn, function, args:Tuple=()):
        self.conn=conn
        self.function=function
        self.args=args
        self.thread = StoppableThread(target = self.function, args = self.args)
    def start(self):
        self.thread.start()
    def join(self):
        self.thread.join()
    def stop(self):
        self.thread.stop()


    
class Attender:
    def __init__(self):
        self.clients={}
    def attend(self, conn, addr, function, args:Tuple=()):
        self.clients[addr]=MyThread(conn, function, args)
        self.clients[addr].start()
        return addr
    def get(self,addr):
        return self.clients[addr]
    def join(self,addr):
        self.clients[addr].join()
    def stop(self,addr):
        self.clients[addr].stop()
    def close(self,addr):
        self.clients[addr].conn.close()
        del self.clients[addr]
    
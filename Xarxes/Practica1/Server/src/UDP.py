import socket

from Server.src.Attender import Attender


class UDP:
    attendant=Attender()
    def __init__(self, port, ip='localhost'):
        self.ip = ip
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((self.ip, self.port))

    def send(self, data):
        self.sock.sendto(data, (self.ip, self.port))

    def recive(self, size):
        data, addr = self.sock.recvfrom(size)
        return addr, data
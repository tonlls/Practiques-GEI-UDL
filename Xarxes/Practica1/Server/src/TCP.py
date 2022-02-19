import socket

from Server.src.Attender import Attender


class TCP:
    attender=Attender()
    # defines the TCP server class
    def __init__(self, port,ip='localhost'):
        self.ip = ip
        self.port = port
        self.sock = None
        self.connections = {}
    def start(self):
        # starts the TCP server
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.bind((self.ip, self.port))
        # listen for connections 
        self.sock.listen(1) 
        while True:
            connection, client_address = self.sock.accept()
            self.attender.attend(connection, client_address)
    def serve():
        pass
    @staticmethod
    def recive(conn,size):
        # recives data from the client
        buffer = conn.recv(size)
        return buffer
    @staticmethod
    def send(conn, data):
        # sends data to the client
        conn.send(data)
    @staticmethod
    def close(conn):
        # closes the server
        conn.close()
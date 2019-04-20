import socket
from threading import Thread
import module.const_value as values


class ServerThread(Thread):
    def __init__(self, window):
        Thread.__init__(self)
        self.window = window

    def run(self):
        TCP_IP = '0.0.0.0'
        TCP_PORT = values.PORT
        BUFFER_SIZE = values.BUFFER_SIZE
        tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcpServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        tcpServer.bind((TCP_IP, TCP_PORT))
        threads = []

        tcpServer.listen(10)
        while True:
            print("Multithreaded Python server : Waiting for connections from TCP clients...")
            global conn
            (conn, (ip, port)) = tcpServer.accept()
            newthread = ClientThread(ip, self.window, is_server=True)
            newthread.start()
            threads.append(newthread)

        for t in threads:
            t.join()


class ClientThread(Thread):

    def __init__(self, ip, window, is_server=False):
        Thread.__init__(self)
        self.window = window
        self.ip = ip
        self.port = values.PORT
        self.is_server = is_server
        print("[+] New server socket thread started for " + ip + ":" + str(self.port))

    def run(self):
        global conn

        if self.is_server is True:
            pass
        else:
            conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            conn.connect((self.ip, self.port))

        while True:
            # (conn, (self.ip,self.port)) = serverThread.tcpServer.accept()

            data = conn.recv(values.BUFFER_SIZE)
            self.window.chat.append(data.decode("utf-8"))
            print(data)

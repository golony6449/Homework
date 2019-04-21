import socket
from threading import Thread
from time import sleep
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

        if self.is_server is True:
            pass
        else:
            global conn
            conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            conn.connect((self.ip, self.port))

        while True:
            # (conn, (self.ip,self.port)) = serverThread.tcpServer.accept()
            # TODO: 리팩토링 필요, 각각의 메서드에서 FLAG만 수정하고 실제 처리는 run에서 하도록 해야 할듯
            data = conn.recv(values.BUFFER_SIZE)
            data = data.decode('utf-8')
            self.res = data
            if self.is_server:
                self.server_process(data)

            print('Received Data: ', data)

    def login(self, username):
        req = str(values.METHOD_LOGIN_REQUEST) + " " + username

        # "METHOD USERNAME"
        conn.send(req.encode('utf-8'))
        # res = conn.recv(values.BUFFER_SIZE)
        sleep(1)
        res = self.res
        res = res.split()

        if int(res[0]) == values.METHOD_LOGIN_RESPONSE and int(res[1]) == values.SUCCESS:
            print('login successfully')
            return True
        elif int(res[0]) == values.METHOD_LOGIN_RESPONSE and int(res[1]) == values.ERROR:
            print('login fail')
            return False
        else:
            print("ERROR: WRONG MESSAGE", res)
            return False

    def server_process(self, decoded_data):
        processed = decoded_data.split()
        method = int(processed[0])

        if method == values.METHOD_LOGIN_REQUEST:
            if processed[1] in values.USER_LIST:
                res = str(values.METHOD_LOGIN_RESPONSE) + " " + str(values.SUCCESS)
            else:
                res = str(values.METHOD_LOGIN_RESPONSE) + " " + str(values.ERROR)
            print("send data: ", res)
            conn.send(res.encode('utf-8'))

        if method == values.METHOD_SEND_OBJ_REQUEST:
            pass

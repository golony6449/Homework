import socket
from threading import Thread
from time import sleep
import module.const_value as values
import pickle


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
            newthread = ServerChildThread(ip, self.window)
            newthread.start()
            threads.append(newthread)

        for t in threads:
            t.join()

    # def broadcast_slot(self, threads):
    #     for t in threads:
    #         if t.broadcast_flag is True:


# TODO: 서버측 소켓 분리
class ServerChildThread(Thread):
    def __init__(self, ip, window):
        Thread.__init__(self)
        self.window = window
        self.ip = ip
        self.port = values.PORT
        self.is_server = True
        self.broadcast_flag = True
        self.broadcast_data = None
        print("[+] New server socket thread started for " + ip + ":" + str(self.port))

    def run(self):
        # 데이터 수신시 처리할 일
        while True:
            # TODO: 리팩토링 필요, 각각의 메서드에서 FLAG만 수정하고 실제 처리는 run에서 하도록 해야 할듯
            data = conn.recv(values.BUFFER_SIZE)
            data = data.decode('utf-8')
            self.res = data

            self.server_process(data)

            print('Received Data: ', data)

    def login(self, username):
        req = str(values.METHOD_LOGIN_REQUEST) + " " + username

        # "METHOD USERNAME"
        conn.send(req.encode('utf-8'))
        sleep(1)
        res = self.res  # 수신은 run의 무한루프에서 진행
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
            self.broadcast_flag = True
            self.broadcast_data = pickle.loads(processed[1])


class ClientThread(Thread):
    def __init__(self, ip, window):
        Thread.__init__(self)
        self.window = window
        self.ip = ip
        self.port = values.PORT
        self.res = None
        self.connection = None
        print("[+] New server socket thread started for " + ip + ":" + str(self.port))

    def run(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect((self.ip, self.port))

        # 데이터 수신시 처리할 일
        while True:
            # TODO: 리팩토링 필요, 각각의 메서드에서 FLAG만 수정하고 실제 처리는 run에서 하도록 해야 할듯
            data = self.connection.recv(values.BUFFER_SIZE)
            data = data.decode('utf-8')
            self.res = data

            print('Received Data: ', data)

    def login(self, username):
        req = str(values.METHOD_LOGIN_REQUEST) + " " + username

        # "METHOD USERNAME"
        self.connection.send(req.encode('utf-8'))
        sleep(1)
        res = self.res      # 수신은 run의 무한루프에서 진행
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

    def broadcast_obj_list(self, obj_list):
        data_string = pickle.dumps(obj_list)
        self.connection.send(data_string)
        sleep(1)
        print('OBJ SEND Successfully')
        pass

    def client_process(self, decoded_data):
        processed = decoded_data.split()
        method = int(processed[0])

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
        global threads
        threads = []

        tcpServer.listen(10)
        while True:
            print("Multithreaded Python server : Waiting for connections from TCP clients...")
            # global conn
            (conn, (ip, port)) = tcpServer.accept()
            newthread = ServerChildThread(ip, self.window, conn)
            newthread.start()
            threads.append(newthread)

        for t in threads:
            t.join()

    # def broadcast_slot(self, threads):
    #     for t in threads:
    #         if t.broadcast_flag is True:


# TODO: 서버측 소켓 분리
class ServerChildThread(Thread):
    def __init__(self, ip, window, conn):
        Thread.__init__(self)
        self.window = window
        self.ip = ip
        self.port = values.PORT
        self.is_server = True   # TODO: 제거 예정
        self.conn = conn
        print("[+] New server socket thread started for " + ip + ":" + str(self.port))

    def run(self):
        # 데이터 수신시 처리할 일
        while True:
            # 모든 패킷 수신
            data = b''
            while True:
                part = self.conn.recv(values.BUFFER_SIZE)
                data += part
                if len(part) < values.BUFFER_SIZE:
                    # either 0 or end of data
                    break
            # data = self.conn.recv(values.BUFFER_SIZE)

            print('Server Received Data: ', data)

            # data = data.decode('utf-8')
            self.res = splited_data = [data[:4].decode('utf-8'), data[5:]]

            self.server_process(splited_data)

    def server_process(self, splited_data):
        method = splited_data[0]
        print('Server splited data: ', splited_data)
        if method == values.METHOD_LOGIN_REQUEST:
            encoded_name = splited_data[1].decode('utf-8')
            if encoded_name in values.USER_LIST:
                res = values.METHOD_LOGIN_RESPONSE + " " + str(values.SUCCESS)
            else:
                res = values.METHOD_LOGIN_RESPONSE + " " + str(values.ERROR)

            print("send to Client: ", res)   # 테스트 코드
            self.conn.send(res.encode('utf-8'))

        elif method == values.METHOD_SEND_OBJ_REQUEST:
            # TODO: 도착한 OBJ LIST를 브로드캐스트
            # self.broadcast_flag = True
            # self.broadcast_data = pickle.loads(processed[1])

            res = (values.METHOD_SEND_OBJ_RESPONSE + " ").encode('utf-8') + splited_data[1]

            global threads
            for thread in threads:
                thread.conn.sendall(res)

        else:
            raise ValueError("잘못된 method code", method)


class ClientThread(Thread):
    def __init__(self, ip, window):
        Thread.__init__(self)
        self.window = window
        self.ip = ip
        self.port = values.PORT
        self.res = None
        self.conn = None
        print("[+] New client socket thread started for " + ip + ":" + str(self.port))

    def run(self):
        self.conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.conn.connect((self.ip, self.port))

        # 데이터 수신시 처리할 일
        while True:
            # TODO: 리팩토링 필요, 각각의 메서드에서 FLAG만 수정하고 실제 처리는 run에서 하도록 해야 할듯
            # 모든 패킷 수신
            data = b''
            while True:
                part = self.conn.recv(values.BUFFER_SIZE)
                data += part
                if len(part) < values.BUFFER_SIZE:
                    # either 0 or end of data
                    break

            # data = self.connection.recv(values.BUFFER_SIZE)
            plain_data = data
            # data = data.decode('utf-8')
            self.res = data

            self.client_process(plain_data)

    def client_process(self, plain_data):
        # processed = decoded_data.split()
        # method = int(processed[0])
        method = plain_data[:4].decode('utf-8')
        print('Client Received plain_data: ', plain_data)
        print('method: ', method, 'type: ', type(method))

        if method == values.METHOD_LOGIN_RESPONSE:
            pass
        elif method == values.METHOD_SEND_OBJ_RESPONSE:
            # print('Received: ', processed[1])
            # print('To_bytes: ', bytes(processed[1], 'utf-8'))
            # print('Encode__: ', processed[1][2:-1].encode('utf-8'))

            # obj_list = bytes(processed[1], 'utf-8') # TODO: 수정필요
            # obj_list = pickle.loads(processed[1][2:-1].encode('utf-8'))
            print('to_unpickle', plain_data[5:])
            obj_list = pickle.loads(plain_data[5:])
            print('pre_obj: \t', obj_list)
            print('post_obj: \t', self.window.object_list)
            self.window.object_list = obj_list
            self.window.update()
        else:
            print('CLIENT_ERROR: Invalid Method')

    def login(self, username):
        req = values.METHOD_LOGIN_REQUEST + " " + username

        # "METHOD USERNAME"
        self.conn.send(req.encode('utf-8'))
        sleep(1)
        res = self.res      # 수신은 run의 무한루프에서 진행
        res = [res[:4].decode('utf-8'), res[5:].decode('utf-8')]

        if res[0] == values.METHOD_LOGIN_RESPONSE and int(res[1]) == values.SUCCESS:
            print('login successfully')
            return True
        elif res[0] == values.METHOD_LOGIN_RESPONSE and int(res[1]) == values.ERROR:
            print('login fail')
            return False
        else:
            print("ERROR: WRONG LOGIN METHOD", res)
            return False

    def broadcast_obj_list(self, obj_list):
        data_string = pickle.dumps(obj_list)
        res = (values.METHOD_SEND_OBJ_REQUEST + " ").encode('utf-8') + data_string

        self.conn.sendall(res)
        sleep(1)
        print('OBJ SEND Successfully')


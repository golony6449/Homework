# https://seolin.tistory.com/98?category=762768

from socket import *
import threading

def send(sock):
    while True:
        data = input('>>> ')
        sock.send(data.encode('utf-8'))

def receive(sock):
    while True:
        data = sock.recv(1024)
        print('상대방: ', data.decode('utf-8'))

serverSock = socket(AF_INET, SOCK_STREAM)
serverSock.bind(('', 8080))
serverSock.listen(1)
connectionSock, addr = serverSock.accept()

print(str(addr), '에서 접속이 확인되었습니다.')

sender = threading.Thread(target=send, args=(connectionSock,))
receiver = threading.Thread(target=receive, args=(connectionSock,))

sender.start()
receiver.start()

while True:
    pass

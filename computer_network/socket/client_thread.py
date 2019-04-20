# https://seolin.tistory.com/98?category=762768

from socket import *
import threading

clientSock = socket(AF_INET, SOCK_STREAM)
clientSock.connect(('127.0.0.1', 8080))

def send(sock):
    while True:
        data = input('>>> ')
        sock.send(data.encode('utf-8'))

def receive(sock):
    while True:
        data = sock.recv(1024)
        print('상대방: ', data.decode('utf-8'))

print('연결 확인 됐습니다.')

sender = threading.Thread(target=send, args=(clientSock, ))
receiver = threading.Thread(target=receive, args=(clientSock, ))

sender.start()
receiver.start()

while True:
    pass

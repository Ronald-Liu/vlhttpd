import socket
import time

def sendReq():
	HOST = '127.0.0.1'    # The remote host
	PORT = 8081              # The same port as used by the server
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((HOST, PORT))
	s.sendall('Hello, worl1d'*1023)
	time.sleep(1)
	s.sendall('df\n')
	s.close()

sendReq()
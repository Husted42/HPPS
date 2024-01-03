import socket
import sys
import socketserver

from shared import *
from threading import Lock

# A handler function, called on each incoming message to the server
class PorchHandler(socketserver.StreamRequestHandler):
    lock = Lock()
    with lock:
        def handle(self):
            # Read the message
            msg = self.request.recv(MAX_MSG_LEN)

            if b'-' in msg:
                body = msg[msg.index(b'-')+1:]
                msg = msg[:msg.index(b'-')]

            if msg.startswith(b'problem'):
                '''For test: '''
                # print("PorchHandler got message: ", msg)
                # print("Elf: ", elf_host, elf_port)
                # print("Elf list: ", self.server.elf_counter)
                elf_host = body[:body.index(b':')].decode()
                elf_port = int(body[body.index(b':')+1:].decode())
                

                # Locking for thread safety
                # with self.server.lock:
                self.server.elf_counter.append((elf_host, elf_port))
                if len(self.server.elf_counter) >= 3:
                    for host, port in self.server.elf_counter:
                        sending_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                        sending_socket.connect((host, port))
                        sending_socket.sendall(MSG_SORT_PROBLEM)
                        sending_socket.close()
                        # Clear the elf counter when 3 elves have reported

                    self.server.elf_counter.clear()
            else:
                print("Error - PorchHandler got message: ", msg)
    pass

# A socketserver class to run the porch as a constant server
class PorchServer(socketserver.ThreadingTCPServer):
    # Constructor for our custom class. If we wish to add more variables or
    # arguments this is where we could do it
    def __init__(self, server_address, elf_group, santa_host, santa_port, request_handler_class):
        # Call the parent classes constructor
        super().__init__(server_address, request_handler_class)
        # Record the expected number of elves, and santas address
        self.elf_group = elf_group
        self.santa_host = santa_host
        self.santa_port = santa_port
        # Setup the list for collecting elf addresses
        self.elf_counter = []
        # Setup lock for accessing shared list
        self.elf_lock = Lock()
 
# Base porch function, to be called as a process
def porch(my_host, my_port, santa_host, santa_port, elf_group):
    # Start a socketserver to always be listening
    with PorchServer((my_host, my_port), elf_group, santa_host, santa_port, PorchHandler) as porch_server:
        try:
            # Always be able to handle incoming messages
            porch_server.serve_forever()
        finally:
            # If we keyboard interupt this will wrap up all the backend stuff
            porch_server.server_close()

# As an alternative to using the true_santa_problem.py, you may start a 
# standalone porch as described in the handout
if __name__ == "__main__":
    process = Process(target=porch, args=(sys.argv[1:]))
    process.start()
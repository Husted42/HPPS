import socket
import sys
import socketserver

from shared import *
from threading import Lock

# A handler function, called on each incoming message to the server
class PorchHandler(socketserver.StreamRequestHandler):
    # lock = Lock()
    # with lock:
    #     def handle(self):
    #         elf_counter = []
    #         # Read the message
    #         msg = self.request.recv(MAX_MSG_LEN)

    #         if b'-' in msg:
    #             body = msg[msg.index(b'-')+1:]
    #             msg = msg[:msg.index(b'-')]

    #         if msg.startswith(b'over'):
    #             # Part of the message will be the address of the elf, separate
    #             # the two parts
    #             elf_host = body[:body.index(b':')].decode()
    #             elf_port = int(body[body.index(b':')+1:].decode())

    #             # Append them to a list of collected elf addresses
    #             self.server.elf_counter.append((elf_host, elf_port))
                
    #             # self.server.elf_counter.append((self.server.santa_host, self.server.santa_port))

    #             # If we've collected all elf addresses, then tell them all 
    #             # that we can deliver
    #             print("No. of elf: ", len(self.server.elf_counter))
    #             if len(self.server.elf_counter) <= 3:
    #                 # Deliver presents               
    #                 self.server.elf_counter.append((self.server.santa_host, self.server.santa_port)) 
    #                 print(f"The stable is full of {self.server.num_elf} elfs")
    #                 # Tell each elf to deliver
    #                 for host, port in self.server.elf_counter:
    #                     sending_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #                     sending_socket.connect((host, port))
    #                     sending_socket.sendall(MSG_SORT_PROBLEM)
    #                     sending_socket.close()
    #                 # Reset the elf address collection
    #                 self.server.elf_counter.clear()  
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
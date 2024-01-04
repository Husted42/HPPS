import socket
import sys

from shared import *
      
# Base santa function, to be called as a process
def santa(host, port, num_reindeer, elf_group):
    # Open a listening socket. Doing so early means its definately open before 
    # we might need it
    listening_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listening_socket.bind((host, port))
    listening_socket.listen()

    # Setup the lists for collecting reindeer and elf addresses (hint)
    reindeer_counter = []
    elf_counter = []

    # Run forever, its a thankless life always being awoken by these reindeer 
    # and elves
    while (1):
        # Wait on the listening port to get a connection request
        connection, _ = listening_socket.accept()

        # Read the message
        msg = connection.recv(MAX_MSG_LEN)

        # If the message has an additional payload, then separate the variables
        if b'-' in msg:
            body = msg[msg.index(b'-')+1:]
            msg = msg[:msg.index(b'-')]

        # This message will be sent by each reindeer in turn, as they finish 
        # their holiday
        if msg == MSG_HOLIDAY_OVER:
            # Part of the message will be the address of the reindeer, separate
            # the two parts
            reindeer_host = body[:body.index(b':')].decode()
            reindeer_port = int(body[body.index(b':')+1:].decode())

            # Append them to a list of collected reindeer addresses
            reindeer_counter.append((reindeer_host, reindeer_port))

            # If we've collected all reindeer addresses, then tell them all 
            # that we can deliver
            if len(reindeer_counter) == num_reindeer:
                # Deliver presents                
                print(f"Santa is delivering presents with all {num_reindeer} the reindeer")
                # Tell each reindeer to deliver
                for host, port in reindeer_counter:
                    sending_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    sending_socket.connect((host, port))
                    sending_socket.sendall(MSG_DELIVER_PRESENTS)
                    sending_socket.close()
                # Reset the reindeer address collection
                reindeer_counter = []

        # This message will be sent by any elves that encounter a problem
        elif msg == MSG_PROBLEM:
            # Append the elf address to the list of collected elf addresses
            elf_host = body[:body.index(b':')].decode()
            elf_port = int(body[body.index(b':')+1:].decode())

            # Append them to a list of collected elf addresses
            elf_counter.append((elf_host, elf_port))

            # If we've collected a group of 3 elves, then respond to them
            if len(elf_counter) == 3:
                # Respond to the group of elves
                print(f"Santa is responding to a group of 3 elves")
                for host, port in elf_counter:
                    sending_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    sending_socket.connect((host, port))
                    sending_socket.sendall(MSG_SORT_PROBLEM)
                    sending_socket.close()
                # Reset the elf address collection
                elf_counter = []

        # If we get something we didn't expect then abort
        else:
            print(f"Santa recieved an unknown instruction")
            exit()

# As an alternative to using the naive_santa_problem.py, you may start a 
# standalone santa as described in the handout
if __name__ == "__main__":
    my_host = sys.argv[1]
    my_port = int(sys.argv[2])
    num_reindeer = int(sys.argv[3])
    elf_group = int(sys.argv[4])
    process = Process(target=santa, args=(my_host, my_port, num_reindeer, elf_group))
    process.start()
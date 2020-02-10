import socket
import sys
import os

"""Function
Checks to see if the program has the correct amount of
parameters when entered in the console. If it does not
it will quit out of the program.
"""


def check_startup():
    if len(sys.argv) < 2:
        print("Format of input should be:")
        print("python3 chatserve.py <port>")
        quit(0)


"""Function
Allows user to select the handle they would like to be known as,
limit of 10 characters can be entered. 
"""


def choose_handle():
    handle = input("What would you like your username to be (Limit 10 Characters):")

    while len(handle) > 10:
        handle = input("Please choose a handle that is less than 10 characters:")

    print("Your handle is:", handle)

    return handle


"""Function
Starts the server. Code taken and modularized 
from CS 372 Lecture 15.
"""


def start_server():
    port_number = int(sys.argv[1])
    user_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    user_socket.bind(("", port_number))
    user_socket.listen(1)
    return user_socket


"""Function
Function to allow the program to read bytes from
the socket.
"""


def receive_msg(conn):
    return conn.recv(1024)


"""Function
FUnction to send bytes to the socket to 
relay message to host B.
"""


def send_msg(conn, handle):
    user_msg = input(handle + ": ")
# Encoded version of string above will be sent. Encodes to 'UTF-8'
    conn.send((handle + ": " + user_msg).encode())
    return user_msg

def main():
    check_startup()
    handle = choose_handle()
    new_server = start_server()
    online = True
    conn_waiting = False
    os.system('clear')
    print("Waiting for a message from the client")
    conn, addr = new_server.accept()

    while online:
        if conn_waiting:
            conn, addr = new_server.accept()
            conn_waiting = False
        received = receive_msg(conn)
        if "/quit" in str(received):
            print("Waiting for a message from a new client")
            conn_waiting = True
            continue
        new_message = str(received)
        print(new_message[2:-1])
        sent = send_msg(conn, handle)
        if "/quit" in sent:
            print("You have now exited the program")
            online = False
            break
    conn.close()


if __name__ == '__main__':
    main()


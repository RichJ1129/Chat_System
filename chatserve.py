import socket
import sys
import os

def check_startup():
    if len(sys.argv) < 2:
        print("Format of input should be:")
        print("python3 chatserve.py <port>")
        quit(0)



def choose_handle():
    handle = input("What would you like your username to be (Limit 10 Characters):")

    while len(handle) > 11:
        handle = input("Please choose a handle that is less than 10 characters:")

    print("Your handle is:", handle)

    return handle


def start_server():
    port_number = int(sys.argv[1])
    user_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    user_socket.bind(("", port_number))
    user_socket.listen(1)
    return user_socket


def receive_msg(msg):
    return msg.recv(256)


def send_msg(conn, handle):
    user_msg = input(handle + ": ")
    conn.send((handle + ": " + user_msg).encode())
    return user_msg


def main():
    # check_startup()
    handle = choose_handle()
    new_server = start_server()

    online = True

    while 1:
        os.system('clear')
        print("Awaiting message from the client")
        waiting = True
        conn, addr = new_server.accept()
        while 1:
            received = receive_msg(conn)
            # if "\quit" in received:
            #     break
            # if waiting:
            #     os.system('clear')
            #     print("-Messages-")
            # waiting = False
            print(received)
            sent = send_msg(conn, handle)
            if "\quit" in sent:
                break
    conn.close()


if __name__ == '__main__':
    main()
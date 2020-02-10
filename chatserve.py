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


def receive_msg(conn):
    return conn.recv(256)


def send_msg(conn, handle):
    user_msg = input(handle + ": ")
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
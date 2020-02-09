import socket
import sys
import os


def check_startup():
    if len(sys.argv) < 2:
        print("Format of input should be:")
        print("python3 chatserve.py <port>")


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


def send_msg(msg, handle):
    user_msg = input(handle + ": ")
    msg.send(handle, ":", user_msg)
    return user_msg


def main():
    check_startup()
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
            if "\quit" in received:
                break
            if waiting:
                os.system('clear')
                print("-Messages-")
            waiting = False
            print(received)
            sent = send_msg(conn, handle)
            if "\quit" in sent:
                break
    conn.close()


    # TCP_IP = 'localhost'
    # TCP_PORT = 11299
    # BUFFER_SIZE = 256  # Normally 1024, but we want fast response
    #
    # s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # s.bind((TCP_IP, TCP_PORT))
    # s.listen(1)
    #
    # conn, addr = s.accept()
    # print('Connection address:', addr)
    # while 1:
    #     data = conn.recv(BUFFER_SIZE)
    #     if not data: break
    #     print("received data:", data)
    #     conn.send(data)  # echo
    # conn.close()

if __name__ == '__main__':
    main()
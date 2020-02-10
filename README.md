## Simple Chat System
#### Created by Richard Joseph
#### Status: In-Progress
#### Languages: C++ Chat Server and Python Chat Client
> #### Sources: 
> - http://www.linuxhowtos.org/C_C++/socket.htm 
> - https://docs.python.org/3.8/howto/sockets.html
> - https://wiki.python.org/moin/TcpCommunication
#### Description     
* Simple chat system that works for a pair of users.
* Program able to send messages of up to 500 characters.

#### Instructions:
1. Compile the cpp file by typing in the command line 'gcc chatClient.cpp -o client'.
    * Note: client can be interchanged with any name to make running easier.
2. Run the following command on the flip server 'python3 changeServe.py <Port #>'.
    1. Enter in your user's handle
3. Run chatClient.cpp by typing in the command line './client <Server Name> <Port #>'.
    1. Enter in your user's handle.
    2. Enter in a message and press enter.
4. Server will receive this message and server can now enter a message and press enter.
5. To exit out of the programs type in /quit into the message.

    



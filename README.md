# TCP-Network-Connection-Running-a-command
The following program is a computer network implementation using TCP communication model. The communication takes place between the client which is the user, and the server where the user command will be executed

# Program Working: 
1.	The server turns on and a server side socket is created. The socket () function is used to create the socket and this function will return the socket ID which will then be used in communication throughout the program. The port number is hardcoded which is 8080. 
2.	If the socket creation function fails, an error message is printed. 
3.	Once the socket is created successfully, the socket binding process takes place. Binding is when the socket is assigned a port number and an IP address. The IP address of the server is automatically known which is of the device. 
4.	 The server is now in the listening mode. This is when the server is activated and is now waiting for client requests. 
5.	On the other end, the socket on the client side is also created.
6.	The client then connects to the server using the server IP and port number. 
7.	Once the connection is established, the client side then asks the user to enter a valid Linux command. This user input is written into the buffer and this data is then sent over the socket to the server side. This is done by using the client and server socket ID. 
8.	The important thing at this point is that the buffer can send a maximum of 80 bytes of data at a time. This won’t be an issue here since the Linux command will be less than 80 bytes anyways even if it involves two arguments. 
9.	The server side will then receive the data. The data from the socket will be read using the read function and this data will be written into the server side buffer. The command received will be printed on the server’s terminal. 
10.	 Since our requirement was to run the command and store the output to a temporary file, we will concatenate ‘> filename’ with the command received. The ‘>’ operator will write the output automatically to the file name. So suppose that the output given by the client is ‘ls’, after concatenation, the command will be: 
Ls > filename
11.	 The command is then executed and I have used the system function for this purpose. The system function takes the command as an input in string type and runs it on the terminal on the server side. The output of the command is then written to the temporary file which I have named as ‘outputfile.txt’ in the code. 
12.	 Now, the server needs to send this file to the client. 
13.	 The server now sends the file 80 bytes at a time by writing it on the buffer and then on the socket. The important thing is to check when the file ends. This can be either done by adding EOF at the end of the file. 
14.	The client side creates a file pointer and creates a file ‘received.txt’. It then opens this file in write mode. The 80 bytes of data that it continuously receives form the socket, it writes it down on the new file until the whole data is written. 
15.	 The new file created is stored on the client’s local directory which in most cases is the root directory. 
16.	 Once the new file with the output is saved in the client’s system, we now need to display the file contents on the terminal. 
17.	 For that, we have declared a string which is the new command (used to display file contents on the terminal). The command used is ‘cat file name’ and again, the system command is used to run it on the terminal. 
18.	 Once the contents are displayed on the terminal, the task has been achieved and the socket is now closed. This means no communication can take place. 

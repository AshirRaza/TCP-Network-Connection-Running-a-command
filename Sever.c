#include <stdio.h>                             //Libraries
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80                                 // Size of buffer is set to 80 
#define PORT 8080                              // Communication will take place on port 8080
#define SA struct sockaddr

void func(int connfd, int sockfd)              // Function that allows sending and receiving of data and files between server and client.
{
    char buff[MAX];                            // Buffer is initialized. It's size is 80
    char* command;                             // This is the command that will be received from the client. 
    
    FILE *fp;                                  // Stores the file pointer of the new file created. THis file will have the output of the command.
    char *filename = "outputfile.txt";         // Name of the file that will be sent to the client
       
     
    read(connfd, buff, sizeof(buff));          // Reading the value of the buffer. THe buffer currently contains the command sent by the client.
    printf("\nCommand Received is: %s", buff); // Printing command on server interface
    command = strcat(buff, " > outputfile.txt");  // > filename is concatenated with the command so that the command output is stored in the file
    system(command);                              // command executed on the terminal.
    bzero(buff, MAX);                             // buffer reset to zero so that it can now have the file contents
    
    fp = fopen(filename, "r");                    // File now opened in read mode.
    if (fp == NULL) {                             // file not opened succesfully. Print an error message
        perror("\n[-]Error in reading file.\n");
        exit(1);
    }
               
    while (1) {                                        // Data is continously sent over the socket until the end of file
        size_t data = fread(buff, 1, MAX, fp);         // File data is read. fread function reads data from file fp, MAX (80) bits at a time.
        if (data == 0) {                               // If the read data is 0, function will break. This means end of file. 
            break;
        }

        int val = write(sockfd, buff, data);           // This is to write or send the data on the socket represented by the socket number. This will return a value if sent succesfully
        if (val < 0) {                        
            perror("\nAn error has occured while writing to the socket\n");    // Error if data not written succesfully. 
            exit(EXIT_FAILURE);
        }
        else if (val == 0) {
            break;
        }
    }
    bzero(buff, MAX);                  //buffer reset
}

int main()                                  //main function
{ 
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);   //socket creation and verification. This function activates the socket. The socket function creates a socket and returns the socket id
    if (sockfd == -1) {
       printf("socket creation failed...\n");   //socket creation unsuccessful 
       exit(0);
    }
    
    else
       printf("Socket successfully created..\n");
       
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;               // This peice of code assigns IP address.
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {  // Binding function
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

// At this point, server is ready and is listening for client requests.
 
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);        // Accept the data packet from client and verification
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    
    else
        printf("server accept the client...\n");

    func(connfd, sockfd);                           //user defined function for client and server communication
    close(sockfd);                                  // socket closed after communication takes place.
}

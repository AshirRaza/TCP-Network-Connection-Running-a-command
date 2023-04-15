#include <arpa/inet.h>  // required libraries
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> 
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80                 // size of buffer is set to 80
#define PORT 8080              // port over which the communication takes place
#define SA struct sockaddr

void func(int sockfd)          // function which takes linux command as input, print files etc. It provides the basic functionality
{
    char buff[MAX];            // buffer initialized
    bzero(buff, sizeof(buff)); // buffer reset
    printf("\nEnter a valid Linux command : ");   // user enter a linux command
    scanf("%s",buff);                             // input taken from user
    write(sockfd, buff, sizeof(buff));            // user command is sent over the netowrk to the server
  
    int val;                                      // This variable is use to check for end of file. THis is basically for the file that will be received and it will have the output of the command.
    FILE* fp;                                     // File that will be created at the client's end. THe file will contain the command output.
    const char* filename = "received.txt";        // Name of the new file that will be created
    
    fp = fopen(filename, "w");                   // New file created and opened in write mode
    while (1) {
        int val = read(sockfd, buff, MAX);                       // Data is being read from socket with id socket_id. The function read returns data if read correctly
        if (val < 0) {                                           // A non integer value indicates data read properly from the socket
            perror("Error occured while reading the socket\n"); 
        }
        else if (val == 0) {                                     // Used to ckeck for end of file
            break;
        }

        fwrite(buff, 1, val, fp);                                // Data writen into the file whose pointer is stored in fp
    }
    
            
    char* new_command = "cat received.txt";        //command that will print the contents of the file on the terminal. Stored as a string
    system(new_command);                             //command run at the terminal on the client side.
    
    bzero(buff, MAX);                                //buffer reset

   
}

int main()                                           //main function
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);           // socket create and verification
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
        
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;                               // assign IP, PORT
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");           // THis is the IP address of the client
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!= 0) {     // connect the client socket to server socket
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    func(sockfd);                              // function for communication
    close(sockfd);                             // Socket closed after communication takes place.
}

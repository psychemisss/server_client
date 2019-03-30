#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "dump.h"

#define PORT 7890
#define BUFFER_SIZE 1024

int main(void){
    int sockfd = 0;
    struct sockaddr_in server_addr;
    char *buffer[BUFFER_SIZE];
    size_t buf_size = BUFFER_SIZE;

    if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
        throw_exeption("Network Services", "Socket Init", "0x801"); 
        //0x8xx will be Networking error cods, and sure that sould be in debuger
        //all "throw_exeption functions should be changed for debuger functions"
    debug_msg("Network Services", "Socket Init Success");
    //and that should be in console, so all "debug_msg" functions should be in console 
    //OK? I think you got it) and I'm sure that you could handle it

    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "192.168.43.123", &server_addr.sin_addr) == -1)
        throw_exeption("Network Services", "Converting Address", "0x802");
    debug_msg("Network Services", "Address Convertation Success");

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        throw_exeption("Network Services", "Connecting to Server", "0x803");
    debug_msg("Network Services", "Connection Success");

    send(sockfd, buffer, /*strlen(*buffer)*/ buf_size, 0); //here was seg fault when I used strlen()
    debug_msg("Network Services", "Data Successfully sended"); 
    return 0;
}

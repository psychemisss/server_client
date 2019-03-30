#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "dump.h"

#define PORT 7890
#define PACKAGE_SIZE 2048

int main(void){
    int sockfd, new_sockfd;
    struct sockaddr_in host_addr, client_addr;
    socklen_t sin_size;
    int recive_length = 1, yes = 1;
    char buffer[PACKAGE_SIZE];

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw_exeption("Network Service", "Socket Init", "0x811");
    debug_msg("Network Service", "Socket Init Success");

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        throw_exeption("Network Services", "Socket Setup", "0x812");
    debug_msg("Network Service", "Socket Setup Success");

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(host_addr.sin_zero), '\0', 8);

    if(bind(sockfd, (struct sockaddr *)&host_addr, sizeof(host_addr)) == -1 )
        throw_exeption("[Network Service]", "Connection with socket", "0x813");
    debug_msg("Network Service", "Socket Connected");

    if(listen(sockfd, 5) == -1)
        throw_exeption("[Network Service]", "Socket listening", "0x814");
    debug_msg("Network Service", "Socket Listening Started");

    while(1){
        sin_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        if(new_sockfd == -1)
            throw_exeption("[Network Services", "Connection Acception", "0x815");
        debug_msg("Network Service", "Connection Accepted");

        printf("Server: get %s on port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        send(new_sockfd, "Hello\n", 8, 0);
        recive_length = recv(new_sockfd, &buffer, PACKAGE_SIZE, 0);
        while(recive_length > 0){
            printf("RECIVED: %d bytes\n", recive_length);
            dump(buffer, recive_length);
            recive_length = recv(new_sockfd, &buffer, PACKAGE_SIZE, 0);
        }
        shutdown(new_sockfd, SHUT_RDWR);
    }
    return 0;
}
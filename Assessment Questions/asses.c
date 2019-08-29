#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h> 

#define PORTNO 9999
#define IP "172.16.58.159"


struct packet
{
	pid_t serverpid;
	char response[100];
};
	
void terminateSocket(int sockfd)
{
	close(sockfd);
}

int  createClientSocket()
{
	return(socket(AF_INET,SOCK_STREAM,0));
}
struct sockaddr_in createClientAddress()
{
	//int result , sockfd;
	struct sockaddr_in address;
    address.sin_family = AF_INET ;
	address.sin_addr.s_addr = inet_addr(IP);
	address.sin_port = htons(PORTNO);
	return(address);
}

	/*result = connect(sockfd,(struct sockaddr *)&address , sizeof(address));
	int res[]={result,sockfd};
	int * ptr = res ;
	return ptr ;*/


void performClientTask(int sockfd)
{
	
	printf("Enter a charecter");
	char ch;
	struct packet packet1;
	scanf("%c",&ch);
    write(sockfd,&ch,1);
    printf("Charecter sent ");
    read(sockfd,&packet1,sizeof(struct packet));
	printf("PID %d",packet1.serverpid);
	printf("Response %s",packet1.response);
	terminateSocket(sockfd);
	
	
}

int main()
{
	int sockfd;
	struct sockaddr_in address;
	sockfd=createClientSocket();
	address=createClientAddress();
	int result = connect(sockfd,(struct sockaddr *)&address , sizeof(address));
	performClientTask(sockfd);

}
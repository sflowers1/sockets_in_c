#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define PORT_NO		37
#define MSG_SIZE	1000

int main(int argc, char *argv[])
{
   int sockfd,n;
   struct sockaddr_in servaddr;
   char sendline[MSG_SIZE];
   char recvline[MSG_SIZE];

   if (argc != 2)
   {
      printf("incorrect number of arguments\n");
      exit(1);
   }

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   memset(&servaddr,'0',sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port=htons(PORT_NO);
   
   if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0)
   {
      printf("\n inet_pton error occured\n");
      return 1;
    }

   printf("\nEnter a string:");

   while (fgets(sendline, MSG_SIZE, stdin) != NULL)
   {
      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      recvline[n]=0;
      printf("UDP server responded with: %s",recvline);
      printf("\nEnter a string:");
   }
   
   return 0;
}

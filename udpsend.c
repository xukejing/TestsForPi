#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main()
{
    struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(60001);
 //   addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_addr.s_addr = inet_addr("192.168.1.101");
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
  //  bind(sock, (struct sockaddr *)&addr, sizeof(addr)); 

    char buff[64];
	int i = 1;
	for (i = 1; i < 10; i++)
	{
		sprintf(buff, "%d", i);
		printf("%d\n", i);
		sendto(sock, buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr));
		sleep(1);
	}
	
  //  struct sockaddr_in clientAddr;
  //  int n;
  //  int len = sizeof(clientAddr);
	/*
    while (1)
    {
        n = recvfrom(sock, buff, 64, 0, (struct sockaddr*)&clientAddr, &len);
        float *tmpf=(float*)buff;
        printf("%s %u says: %f %f %f\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), tmpf[0],tmpf[1],tmpf[2]);
       // sendto(sock, buff, n, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
    }
	*/
    return 0;
}

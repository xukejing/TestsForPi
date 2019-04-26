#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>  
#include <netdb.h> 
#include <errno.h> 

#define err_sys(msg) \
	do { perror(msg); exit(-1); } while(0)
#define err_exit(msg) \
	do { fprintf(stderr, msg); exit(-1); } while(0)

void *thread_udp_server(void *arg);

void udpBuff2int(char *inChar, int *outData);


int main()
{
	pthread_t tid_udp_server;
	char* p_udp_server = NULL;

	pthread_create(&tid_udp_server, NULL, thread_udp_server, NULL);


	sleep(5);
	
	pthread_join(tid_udp_server, (void **)&p_udp_server);

	//printf("message: %s\n", p_udp_server);

	return 0;
}
void *thread_udp_server(void *arg)
{
	time_t timep;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(60001);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	printf("udp server is started!\n");
	char buff[64];
	int udpData[8] = {0};
	struct sockaddr_in clientAddr;
	int n;
	int len = sizeof(clientAddr);
	int i;
	while (1)
	{
		n = recvfrom(sock, buff, 64, 0, (struct sockaddr*)&clientAddr, &len);
		if (n > 0)
		{
			buff[n] = '\0';
			printf("%s %u says: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buff);
			switch (buff[0])
			{
			case 's':
				udpBuff2int(buff, udpData);
				time(&timep);
				printf("%d\t%d\t%d\t%s", udpData[0], udpData[1], udpData[2], ctime(&timep));

				break;
			default:
				break;
			}	
			n = 0;
		}	
	}
}
void udpBuff2int(char *inChar,int *outData)
{
	int i,j;
	i = 0;
	j = 0;
	for (i = 0; i < 8; i++)
		outData[i] = 0;
	for (i = 1; i < 64; i++)
	{
		if (inChar[i] == ',')
		{
			j++;
			if (j >= 8)
				return;
		}
		else
		{
			outData[j] = outData[j] * 10 + (inChar[i] - '0');
		}
	}
}


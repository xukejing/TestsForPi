//脸部定位算法不在这里做
//x86的桌面电脑计算完人脸定位信息然后用UDP发给派
//派发现距离合适，角度合适，就打开led
#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

#define	JD	0

int main()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(60001);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sock, (struct sockaddr *)&addr, sizeof(addr)); 

    char buff[64];
    struct sockaddr_in clientAddr;
    int n;
    int len = sizeof(clientAddr);
    
    wiringPiSetup () ;
    pinMode (JD, OUTPUT) ;
    while (1)
    {
        n = recvfrom(sock, buff, 64, 0, (struct sockaddr*)&clientAddr, &len);
        float *tmpf=(float*)buff;
        printf("%s %u says: %f %f %f\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), tmpf[0],tmpf[1],tmpf[2]);
        if(tmpf[0]>1.00)
           digitalWrite (JD, HIGH);
        if(tmpf[0]<0.90)
           digitalWrite (JD, LOW);
       // sendto(sock, buff, n, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
    }
    return 0;
}

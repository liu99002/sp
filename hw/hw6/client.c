#include "net.h"

int main(int argc, char *argv[]) {
  int port = (argc >= 2) ? atoi(argv[1]) : PORT;
  char *host = (argc >= 3) ? argv[2] : "localhost";
  net_t net;
  net_init(&net, TCP, CLIENT, port, host);
  net_connect(&net);
  char cmd[SMAX], recvBuff[TMAX], op[SMAX], line[SMAX], path[SMAX];
  printf("connect to server %s success!\n", net.serv_ip);
  while (1) { 
    sleep(1);                                // 休息一秒鐘
    int n = read(net.sock_fd, recvBuff, TMAX-1);  // 讀取 server 傳回來的訊息
    assert(n > 0);
    recvBuff[n-1] = '\0';                    // 字串結尾，把最後一個 \n 去掉!
    printf("======================Result======================\n");
    puts(recvBuff);                         // 顯示回應訊息
    printf("\n");
  }
  close(net.sock_fd);
  return 0;
}

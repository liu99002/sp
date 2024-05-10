#include "../net.h"

int serv(int connfd) {
  close(STDOUT_FILENO);                    // 關閉 stdout
  dup2(connfd, STDOUT_FILENO);             // 用 connfd 取代 stdout
  dup2(connfd, STDERR_FILENO);             // 用 connfd 取代 stderr
  while (1) {
    char cmd[SMAX];
    //read(int fd 是要讀取的文件描述符,void *buf 是用於存放讀取數據的緩衝區,size_t count 是要讀取的最大字節數)
    int len = read(connfd, cmd, SMAX);     // 讀入 client 傳來的命令 
    if (len <= 0) break;                   // 若沒讀到就結束了！
    strtok(cmd, "\n");                     // 把 \n 去除
    fprintf(stderr, "cmd=%s\n", cmd);      // 印出命令方便觀察
    if (strncmp(cmd, "exit", 4)==0) break; // 若是 exit 則離開！
    system(cmd);                           // 執行該命令 (由於 connfd 取代了 stdout，所以命令的輸出會直接傳回給 client)
    write(connfd, "\n", 1); // 至少要回應 1byte ，否則 client 會讀不到而導致當掉
  }
  close(connfd);            // 關閉連線
  exit(0);                  // 結束此子行程
}

int main(int argc, char *argv[]) {
    // 解析命令行參數以獲取要使用的端口號，如果未提供則使用預設端口號
    int port = (argc >= 2) ? atoi(argv[1]) : PORT;
    // 初始化一個 TCP 網路結構體 net
    net_t net;
    net_init(&net, TCP, SERVER, port, NULL);
    // 使用 net_bind 函式將網路結構體綁定到指定端口
    net_bind(&net);
    // 使用 net_listen 函式開始監聽來自客戶端的連接
    net_listen(&net);
    // 進入無限循環，等待客戶端的連接
    while(1) {
        // 使用 net_accept 函式接受客戶端的連接，返回一個新的連接描述符
        int connfd = net_accept(&net);
        assert(connfd >= 0);
        // 如果 fork() 返回值小於等於 0，表示出錯或是在子進程中，則在子進程中執行 serv 函式，為客戶端提供服務
        if (fork() <= 0) {
            serv(connfd); // 子行程開始執行 serv()
        }
    }
}

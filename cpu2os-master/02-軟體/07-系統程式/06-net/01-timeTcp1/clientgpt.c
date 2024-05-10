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
#include <assert.h>
#include <sys/wait.h>

#define PORT 8080

int main(int argc, char *argv[]) {
    // 創建用於存儲服務器地址的 sockaddr_in 結構體
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr)); // 初始化為 0
    serv_addr.sin_family = AF_INET; // 設置地址家族為 IPv4
    serv_addr.sin_port = htons(PORT); // 設置端口號為指定的端口，並進行字節序轉換

    // 將 IP 地址 "127.0.0.1" 轉換成二進制格式，並存儲在 serv_addr.sin_addr 中
    assert(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) > 0);

    // 創建 TCP 套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0); // 確認套接字創建成功

    // 連接到指定的服務器地址和端口
    assert(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0);

    // 用於接收數據的緩衝區
    char recvBuff[1024];
    int n;
    // 循環從套接字中讀取數據，並將其輸出到標準輸出(stdout)
    while ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
        recvBuff[n] = 0; // 添加字符串結束符
        fputs(recvBuff, stdout); // 將接收到的數據輸出到標準輸出(stdout)
    }
    // 程式結束
    return 0;
}

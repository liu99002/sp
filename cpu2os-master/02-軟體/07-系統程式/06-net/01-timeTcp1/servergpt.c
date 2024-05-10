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
#include <time.h>
#include <assert.h>
#include <sys/wait.h>

#define PORT 8080 // 定義端口號

int main(int argc, char *argv[]) {
  int listenfd = socket(AF_INET, SOCK_STREAM, 0); // 創建一個 TCP 套接字
  assert(listenfd >= 0); // 確認套接字是否創建成功

  // 初始化伺服器地址結構
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET; // 使用 IPv4 位址族
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 將伺服器位址設置為本機任意可用位址
  serv_addr.sin_port = htons(PORT); // 設置伺服器端口

  assert(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) >= 0); // 綁定套接字到伺服器地址
  assert(listen(listenfd, 10) >= 0); // 監聽連接，設置最大同時連接數為10

  char sendBuff[1025]; // 定義發送緩衝區
  memset(sendBuff, 0, sizeof(sendBuff)); // 清空發送緩衝區

  // 服務器主循環，不斷接受客戶端連接請求
  while(1) {
    int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); // 接受客戶端連接
    assert(connfd >= 0); // 確認是否成功接受客戶端連接

    time_t ticks = time(NULL); // 獲取當前時間
    snprintf(sendBuff, sizeof(sendBuff), "%s\r\n", ctime(&ticks)); // 將當前時間轉換成字符串格式

    assert(write(connfd, sendBuff, strlen(sendBuff)) >=0); // 將時間信息發送給客戶端
    close(connfd); // 關閉與客戶端的連接
    sleep(1); // 等待一秒
  }
}

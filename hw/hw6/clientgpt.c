#include "net.h" // 引入自定義的網路函式庫

int main(int argc, char *argv[]) {
	// 解析命令行參數以設置連接的端口和主機地址
	int port = (argc >= 2) ? atoi(argv[1]) : PORT;
	char *host = (argc >= 3) ? argv[2] : "localhost";
	// 初始化網路結構體
	net_t net;
	net_init(&net, TCP, CLIENT, port, host);
	// 連接到指定的主機和端口
	net_connect(&net);
	// 宣告變數來存儲命令、接收的數據、操作符、路徑
	char cmd[SMAX], recvBuff[TMAX], op[SMAX], line[SMAX], path[SMAX];
	// 打印連接成功的消息
	printf("connect to server %s success!\n", net.serv_ip);
	// 主循環：等待用戶輸入命令，然後發送請求給服務器，並接收回應。
	while (1) {
		// 印出提示信息，包括服務器 IP 和當前路徑
		printf("%s %s\n$ ", net.serv_ip, path);
		// 等待用戶輸入命令
		fgets(cmd, SMAX, stdin);
		// 如果路徑不為空，則將命令設置為 'cd <path>; <cmd>' 的形式，否則直接為 <cmd>
		if (strlen(path) > 0)
		sprintf(line, "cd %s;%s", path, cmd);
		else
		sprintf(line, "%s", cmd);
		// 將命令發送給服務器
		write(net.sock_fd, line, strlen(line));
		// 解析命令，獲取操作符
		sscanf(cmd, "%s", op);
		// 如果操作符為 "exit"，則退出循環
		if (strncmp(op, "exit", 4) == 0) 
		break;
		sleep(1);
		// 讀取服務器發送的回應數據
		int n = read(net.sock_fd, recvBuff, TMAX - 1);
		assert(n > 0);
		recvBuff[n - 1] = '\0';
		// 處理回應中的路徑信息
		char *p = recvBuff + n - 1;
		while ((*p != '\n')) 
		p--;
		*p = '\0';
		strcpy(path, p + 1);
		// 打印回應數據
		printf("path=%s\n", path);
		puts(recvBuff);
	}
	// 關閉套接字
	close(net.sock_fd);
	return 0;
}

#include "net.h" // 包含自定義的網絡函式庫

int readText(char *file, char *text, int size) {
	FILE *f = fopen(file, "r");
	int n = fread(text, 1, size, f);
	fclose(f);
	return n;
}

int serv(int connfd) {
  	// 關閉標準輸出，並將 connfd 複製到標準輸出和標準錯誤
	close(STDOUT_FILENO);                    
	dup2(connfd, STDOUT_FILENO);             
	dup2(connfd, STDERR_FILENO);             
  	while (1) {
		char cmd[SMAX], fullcmd[SMAX];
		// 讀取客戶端傳來的命令
		int len = read(connfd, cmd, SMAX);     
		if (len <= 0) break;                   
		strtok(cmd, "\n");                     // 去除命令末尾的換行符
		fprintf(stderr, "cmd=%s\n", cmd);      // 在標準錯誤流中打印收到的命令
		if (strncmp(cmd, "exit", 4)==0) break; // 如果命令是 "exit"，則退出迴圈
		// 將命令加上路徑設定，然後執行該命令，將輸出重定向到客戶端連接
		snprintf(fullcmd, SMAX, "%s;echo $PWD", cmd); 
		system(fullcmd);                       
  	}
	// 關閉與客戶端的連接
	close(connfd);
	exit(0);
}

int myshell(int connfd){
	char ipath[SMAX], path[SMAX], cmd[SMAX], fullcmd[SMAX], pathFile[SMAX];
	getcwd(ipath, SMAX-1); // 取得初始路徑
	strcpy(path, ipath);   // path = ipath
	sprintf(pathFile, "%s/path.txt", ipath); // pathFile=<ipath>/path.txt
	while (1) { // 不斷等待使用者輸入命令並執行之
		printf("myshell:%s $ ", path); // 顯示提示訊息
		fgets(cmd, SMAX-1, stdin);                     // 等待使用者輸入命令
		strtok(cmd, "\n");             // 切掉 \n
		if (strcmp(cmd, "exit")==0) break;
		sprintf(fullcmd, "cd %s;%s;pwd>%s", path, cmd, pathFile); // fullcmd = 切到 path; 使用者輸入的命令; 將路徑存入 pathFile 中。
		system(fullcmd);               // 執行 fullcmd 
		readText(pathFile, path, SMAX);// 讀 pathFile 檔取得路徑
		strtok(path, "\n");            // 切掉 \n
	}
}

int main(int argc, char *argv[]) {
	// 從命令行參數或者使用預設端口號設定端口
	int port = (argc >= 2) ? atoi(argv[1]) : PORT;
	net_t net;
	// 初始化網絡設定
	net_init(&net, TCP, SERVER, port, NULL);
	// 綁定端口
	net_bind(&net);
	// 監聽端口
	net_listen(&net);
	// 宣告兩個執行緒
	pthread_t thread1, thread2;    
	while(1) { // 主迴圈：等待客戶端連接，然後為其啟動服務函數
		// 接受客戶端連接
		int connfd = net_accept(&net); 
		assert(connfd >= 0);
		// 創建新的子進程處理該連接
		pthread_create(&thread2, NULL, myshell(connfd), NULL); 
		pthread_create(&thread1, NULL, serv(connfd), NULL);   
	}
}
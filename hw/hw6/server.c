#include "net.h"

int serv(int connfd) {
    char ipath[SMAX], path[SMAX], cmd[SMAX], fullcmd[SMAX], pathFile[SMAX];
    int sfd = dup(STDOUT_FILENO);
    getcwd(ipath, SMAX-1); // 取得初始路徑
    strcpy(path, ipath);   // path = ipath
    sprintf(pathFile, "%s/path.txt", ipath); // pathFile=<ipath>/path.txt
    while (1) { // 不斷等待使用者輸入命令並執行之
        dup2(sfd, STDOUT_FILENO);
        dup2(sfd, STDERR_FILENO);
        printf("myshell:%s $ ", path); // 顯示提示訊息
        fgets(cmd, SMAX-1, stdin);                     // 等待使用者輸入命令
        strtok(cmd, "\n");             // 切掉 \n
        if (strcmp(cmd, "exit")==0) break;
        sprintf(fullcmd, "cd %s;%s;pwd>%s", path, cmd, pathFile); // fullcmd = 切到 path; 使用者輸入的命令; 將路徑存入 pathFile 中。
        dup2(connfd, STDOUT_FILENO);             // 用 connfd 取代 stdout
        dup2(connfd, STDERR_FILENO);             // 用 connfd 取代 stderr
        system(fullcmd);               // 執行 fullcmd 
        readText(pathFile, path, SMAX);// 讀 pathFile 檔取得路徑
        strtok(path, "\n");            // 切掉 \n
    }

    close(connfd);
    exit(0);
}

int readText(char *file, char *text, int size) {
    FILE *f = fopen(file, "r");
    int n = fread(text, 1, size, f);
    fclose(f);
    return n;
}

int main(int argc, char *argv[]) {
    int port = (argc >= 2) ? atoi(argv[1]) : PORT;
    net_t net;
    net_init(&net, TCP, SERVER, port, NULL);
    net_bind(&net);
    net_listen(&net);    
    while(1) { // 主迴圈：等待 client 連進來，然後啟動 serv 為其服務
        int connfd = net_accept(&net); // 等待連線進來
        assert(connfd >= 0);
        if (fork()==0)
        {
            serv(connfd);
        }
    }
}
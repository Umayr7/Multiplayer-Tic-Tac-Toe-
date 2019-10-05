#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 256
#define DEFAULT_PORT "27016"

WSADATA wsaData;
int iResult;

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ConnectSocket = INVALID_SOCKET;

struct addrinfo *result = NULL;
struct addrinfo hints;


int iSendResult;
char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;
char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

struct addrinfo *ptr = NULL;

char sendbuf[256];

void Host();
void Join();
void Send(char *msg);
char* Receive1();
void Close();
int inspection();
void board();
void Shutdown();

int main(int argc, char *argv[])
{
	int player = 1;
	int i = 0;
	int j = 0;
	int choice = 0;
	char mark = 0;
	char server = '0';
	char *ptrRec;

	while ((server != 'h' && server != 'H' && server != 'c' && server != 'C'))
	{
		printf("Enter 'h' or 'H' if you want to be a host... Enter 'c' or 'C' if you want to be a client : \n");
		scanf_s(" %c", &server);

		if ((server != 'h' && server != 'H' && server != 'c' && server != 'C'))
		{
			printf("Invalid input!\n");
		}
	}

	if (server == 'h' || server == 'H')
	{
		player = 1;
		Host();

		printf("Host is Player 1 .. Client is Player 2!");

		do
		{
			board();


			printf("Player %d, enter a number:  ", player);

			do
			{
				j = 0;

				scanf_s("%d", &choice);


				if (player == 1)
				{
					mark = 'X';
				}
				else
				{
					mark = 'O';
				}

				if (choice == 1 && square[1] == '1')
				{
					square[1] = mark;
				}
				else if (choice == 2 && square[2] == '2')
				{
					square[2] = mark;
				}
				else if (choice == 3 && square[3] == '3')
				{
					square[3] = mark;
				}
				else if (choice == 4 && square[4] == '4')
				{
					square[4] = mark;
				}
				else if (choice == 5 && square[5] == '5')
				{
					square[5] = mark;
				}
				else if (choice == 6 && square[6] == '6')
				{
					square[6] = mark;
				}
				else if (choice == 7 && square[7] == '7')
				{
					square[7] = mark;
				}
				else if (choice == 8 && square[8] == '8')
				{
					square[8] = mark;
				}
				else if (choice == 9 && square[9] == '9')
				{
					square[9] = mark;
				}
				else
				{
					printf("Invalid move ");
					j = 1;
					getch();
				}
			} while (j == 1);
			board();
			Send(square);
			i = inspection();
			if (i == 1)
			{
				printf("==>Player 1 win!");
				getch();
				Close();

			}
			else if (i == 2)
			{
				printf("==>Player 2 win!");
				getch();
				Close();
			}
			else if(i == -1)
			{
				ptrRec = Receive1();
				for (int i = 0; i < 10; i++)
				{
					square[i] = *(ptrRec + i);
				}
				board();
				i = inspection();
				if (i == 1)
				{
					printf("==>Player 1 win!");
					getch();
					Close();
				}
				else if (i == 2)
				{
					printf("==>Player 2 win!");
					getch();
					Close();
				}
				else if (i==0)
				{
					printf("==>Game draw!");
					getch();
					Close();
				}
			}
			else if(i == 0)
			{
				printf("==>Game draw!");
				getch();
				Close();
			}
		} while (i == -1);

		Close();
	}
	else if (server == 'c' || server == 'C')
	{
		player = 2;
		Join();

		printf("Host is Player 1 .. Client is Player 2!");

		do
		{
			board();
			ptrRec = Receive1();
			for (int i = 0; i < 10; i++)
			{
				square[i] = *(ptrRec + i);
			}
			board();
			i = inspection();

			if (i == 1)
			{
				printf("==>Player 1 win!");
				getch();
				Close();

			}
			else if (i == 2)
			{
				printf("==>Player 2 win!");
				getch();
				Close();
			}
			else if (i == -1 )
			{


				printf("Player %d, enter a number:  ", player);

				do
				{
					j = 0;

					scanf_s("%d", &choice);


					if (player == 1)
					{
						mark = 'X';
					}
					else
					{
						mark = 'O';
					}

					if (choice == 1 && square[1] == '1')
					{
						square[1] = mark;
					}
					else if (choice == 2 && square[2] == '2')
					{
						square[2] = mark;
					}
					else if (choice == 3 && square[3] == '3')
					{
						square[3] = mark;
					}
					else if (choice == 4 && square[4] == '4')
					{
						square[4] = mark;
					}
					else if (choice == 5 && square[5] == '5')
					{
						square[5] = mark;
					}
					else if (choice == 6 && square[6] == '6')
					{
						square[6] = mark;
					}
					else if (choice == 7 && square[7] == '7')
					{
						square[7] = mark;
					}
					else if (choice == 8 && square[8] == '8')
					{
						square[8] = mark;
					}
					else if (choice == 9 && square[9] == '9')
					{
						square[9] = mark;
					}
					else
					{
						printf("Invalid move ");
						j = 1;
						getch();
					}
				} while (j == 1);
				board();
					Send(square);
					i = inspection();
					if (i == 1)
					{
						printf("==>Player 1 win!");
						getch();
						Close();
					}
					else if (i == 2)
					{
						printf("==>Player 2 win!");
						getch();
					}
					else if (i == 0)
					{
						printf("==>Game draw!");
						getch();
						Close();
					}
			}
			else
			{
				printf("==>Game draw!");
				getch();
				Close();
			}
			


		} while (i == -1);

		Close();
	}
	
	

	return 0;
}


int inspection()
{
	if (square[1] == square[2] && square[2] == square[3])
	{
		if (square[1] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if (square[4] == square[5] && square[5] == square[6])
	{
		if (square[4] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	else if (square[7] == square[8] && square[8] == square[9])
	{
		if (square[7] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	else if (square[1] == square[4] && square[4] == square[7])
	{
		if (square[1] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	else if (square[2] == square[5] && square[5] == square[8])
	{
		if (square[2] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	else if (square[3] == square[6] && square[6] == square[9])
	{
		if (square[3] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	else if (square[1] == square[5] && square[5] == square[9])
	{
		if (square[1] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	else if (square[3] == square[5] && square[5] == square[7])
	{
		if (square[3] == 'X')
		{
			return 1; //p1 win
		}
		else
		{
			return 2; //p2 win
		}
	}

	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
		square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
		!= '7' && square[8] != '8' && square[9] != '9')

		return 0; //draw
	else
		return  -1; //keep going
}


void board()
{
	system("cls");
	printf("\n\n\tMultiplayer Tic Tac Toe\n\n");

	printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

	printf("     |     |     \n\n");
}

void Host() {
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	char address[25];
	inet_ntop(AF_INET, result->ai_addr, address, sizeof(address));
	printf("%s", address);

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ConnectSocket = accept(ListenSocket, NULL, NULL);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket

}

void Join() {
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		//return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("10.20.155.103", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		//return 1;
	}
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			//return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		//return 1;
	}
}

void Send(char *msg)
{
	
	iResult = send(ConnectSocket, msg, 10, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}
}

char* Receive1()
{
	iResult = recv(ConnectSocket, recvbuf, 10, 0);
	if (iResult > 0) {
		printf("msg received: %s\n", recvbuf);
	}
	else {
		printf("recv failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	return &recvbuf[0];
}

void Close() {
	closesocket(ConnectSocket);
}

void Shutdown()
{
	// shutdown the connection since we're done
	closesocket(ListenSocket);
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);
	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

}

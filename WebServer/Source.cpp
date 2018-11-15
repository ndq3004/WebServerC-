// WebServer.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include "winsock2.h"
#pragma comment (lib, "ws2_32.lib")
#pragma warning (disable : 4996)

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8080);

	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	while (1)
	{
		SOCKET client = accept(listener, NULL, NULL);

		char buf[1024];
		int ret;

		// Nhan yeu cau tu trinh duyet
		ret = recv(client, buf, sizeof(buf), 0);
		buf[ret] = 0;
		
		printf("%s", buf);

		/*char cmd[16], path[1024];
		sscanf(buf, "%s %s", cmd, path);*/

		if (strncmp(buf + 4, "/xinchao", 8) == 0)
		{
			// Tra ket qua cho trinh duyet
			const char *header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
			send(client, header, strlen(header), 0);

			char sendbuf[256];
			char tmp[256];
			FILE *f = fopen("client.txt", "rb");
			//fgets(sendbuf, 255, (FILE *)f);
			while (1)
			{
				ret = fread(sendbuf, 1, sizeof(sendbuf), f);
				if (ret > 0)
					send(client, sendbuf, ret, 0);
				else
					break;
			}
			/*f = fopen("hello.js", "rb");
			while (1)
			{
				ret = fread(sendbuf, 1, sizeof(sendbuf), f);
				if (ret > 0)
					send(client, sendbuf, ret, 0);
				else
					break;
			}*/
			fclose(f);
				

			//const char *content = "<html><body><h1>Xin chao</h1></body></html>";
			//send(client, sendbuf, strlen(sendbuf), 0);
		}
		else if (strncmp(buf + 5, "/hello", 6) == 0)
		{
			//char buf2[256];
			//ret = recv(client, buf2, strlen(buf2), 0);
			// Tra ket qua cho trinh duyet
			const char *header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
			send(client, header, strlen(header), 0);

			char content[1024] = "<html><body><h1>Hello";
			strcat(content, buf);
			strcat(content, "< / h1>< / body>< / html>");
			send(client, content, strlen(content), 0);
		}
		//else if (strncmp(buf + 4, "/image", 6) == 0 || strncmp(buf + 4, "/favicon.ico", 12) == 0)
		//{
		//	// Tra ket qua cho trinh duyet
		//	const char *header = "HTTP/1.1 200 OK\nContent-Type: image/jpg\n\n";
		//	send(client, header, strlen(header), 0);

		//	FILE *f = fopen("C:\\test_server\\city.jpg", "rb");
		//	while (1)
		//	{
		//		ret = fread(buf, 1, sizeof(buf), f);
		//		if (ret > 0)
		//			send(client, buf, ret, 0);
		//		else
		//			break;
		//	}

		//	fclose(f);
		//}
		else
		{
			// Tra ket qua cho trinh duyet
			const char *header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
			send(client, header, strlen(header), 0);

			const char *content = "<html><body><h1>Yeu cau khong duoc ho tro</h1></body></html>";
			send(client, content, strlen(content), 0);
		}

		// Dong ket noi
		closesocket(client);
	}

	closesocket(listener);
	WSACleanup();

	return 0;
}


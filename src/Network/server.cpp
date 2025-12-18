#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include "server.h"
#include "../gameClasses/Player.h"
#include "../shader.h"

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")

using namespace std;

#pragma pack(push, 1)
struct PlayerData {
    float positionX;
    float positionY;
};
#pragma pack(pop)

// Main entry point into the server
void ServerLoop(std::vector<Player>& players, Shader& shader) {
	////////////////////////////////////////////////////////////
	// INITIALIZE WINSOCK
	////////////////////////////////////////////////////////////

	// Structure to store the WinSock version. This is filled in
	// on the call to WSAStartup()
	WSADATA data;

	// To start WinSock, the required version must be passed to
	// WSAStartup(). This server is going to use WinSock version
	// 2 so I create a word that will store 2 and 2 in hex i.e.
	// 0x0202

	// Start WinSock
	int wsOk = WSAStartup(MAKEWORD(2, 2), &data);
	if (wsOk != 0)
	{
		// Not ok! Get out quickly
		cout << "Can't start Winsock! " << wsOk;
		return;
	}

	////////////////////////////////////////////////////////////
	// SOCKET CREATION AND BINDING
	////////////////////////////////////////////////////////////

	// Create a socket, notice that it is a user datagram socket (UDP)
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

	// Create a server hint structure for the server
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY; // Us any IP address available on the machine
	serverHint.sin_family = AF_INET; // Address format is IPv4
	serverHint.sin_port = htons(54000); // Convert from little to big endian

	// Try and bind the socket to the IP and port
	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}

	////////////////////////////////////////////////////////////
	// MAIN LOOP SETUP AND ENTRY
	////////////////////////////////////////////////////////////

	sockaddr_in client; // Use to hold the client information (port / ip address)
	int clientLength = sizeof(client); // The size of the client information
	PlayerData p;
	PlayerData p_sender;

	// Enter a loop
	while (true)
	{
		ZeroMemory(&client, clientLength); // Clear the client structure
		// Wait for message
		int bytesIn = recvfrom(in, (char*)&p, sizeof(p), 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}

		// Display message and client info
		char clientIp[256]; // Create enough space to convert the address byte array
		ZeroMemory(clientIp, 256); // to string of characters

		// Convert from byte array to chars
		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

		//std::cout << "X=" << p.positionX << " Y=" << p.positionY << std::endl;

		// Testing coordinates for player two
		players[1].setPositionHard('x', p.positionX);
		players[1].setPositionHard('y', p.positionY);
        players[1].move(players[1].getPosition('x'), players[1].getPosition('y'), shader);
		// Display the message / who sent it
		//cout << "Message recv from " << clientIp << endl;


		// TODO: Sending back players[0] to the client
		p_sender.positionX = players[0].getPosition('x');
    	p_sender.positionY = players[0].getPosition('y');
		int sendOk = sendto(in, (char*)&p_sender, sizeof(p_sender), 0, (sockaddr*)&client, clientLength);
		if (sendOk == SOCKET_ERROR) {
	        cout << "That didn't work! " << WSAGetLastError() << endl;
		}
	}

	// Close socket
	closesocket(in);

	// Shutdown winsock
	WSACleanup();
}
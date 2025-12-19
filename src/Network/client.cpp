#include <iostream>
#include <WS2tcpip.h>
#include "client.h"
#include "../gameClasses/Player.h"
#include "../gameClasses/Weapon.h"
#include "../shader.h"

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")

// Saves us from typing std::cout << etc. etc. etc.
using namespace std;

#pragma pack(push, 1)
struct PlayerData {
    std::vector<Weapon> vec;
    float positionX;
    float positionY;
};
#pragma pack(pop)


void Client(std::vector<Player>& players, std::vector<Weapon>& weapons, Shader& shader) {
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
    // CONNECT TO THE SERVER
    ////////////////////////////////////////////////////////////

    // Create a hint structure for the server
    sockaddr_in server;
    int serverLength = sizeof(server);
    server.sin_family = AF_INET; // AF_INET = IPv4 addresses
    server.sin_port = htons(54000); // Little to big endian conversion
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // Convert from string to byte array

    // Socket creation, note that the socket type is datagram
    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    // Write out to that socket
    PlayerData p;
    p.positionX = players[0].getPosition('x');
    p.positionY = players[0].getPosition('y');
    p.vec = weapons;

    int sendOk = sendto(out, (char*)&p, sizeof(p), 0, (sockaddr*)&server, sizeof(server));
    if (sendOk == SOCKET_ERROR)
    {
        cout << "That didn't work! " << WSAGetLastError() << endl;
    }

    sockaddr_in from;
    int fromLen = sizeof(from);
    PlayerData p_receiver;
    int bytesIn = recvfrom(out, (char*)&p_receiver, sizeof(p_receiver), 0, (sockaddr*)&from, &fromLen);
    if (bytesIn == SOCKET_ERROR)
    {
        cout << "Error receiving from client " << WSAGetLastError() << endl;
    }
    players[1].setPositionHard('x', p_receiver.positionX);
    players[1].setPositionHard('y', p_receiver.positionY);
    players[1].move(players[1].getPosition('x'), players[1].getPosition('y'), shader);

    // Close the socket
    closesocket(out);

    // Close down Winsock
    WSACleanup();
}
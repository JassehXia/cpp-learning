#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

// Tell the linker to use the Winsock library (ws2_32.lib)
#pragma comment(lib, "ws2_32.lib")

// This function runs on a separate thread for every browser that connects
void handle_client(SOCKET client_socket) {
  // 1. Create a valid HTTP response string
  // This is the "Hello World" of web servers
  std::string response = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Content-Length: 13\r\n"
                         "\r\n"
                         "Hello World!";

  // 2. Send the response back to the browser
  send(client_socket, response.c_str(), (int)response.size(), 0);

  // 3. Close the connection so the browser knows we're done
  closesocket(client_socket);
}

int main() {
  // --- STEP 1: INITIALIZE WINSOCK ---
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "Failed to initialize Winsock.\n";
    return 1;
  }

  // --- STEP 2: CREATE THE LISTENING SOCKET ---
  // AF_INET = IPv4, SOCK_STREAM = TCP
  SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == INVALID_SOCKET) {
    std::cerr << "Socket creation failed.\n";
    WSACleanup();
    return 1;
  }

  // --- STEP 3: CONFIGURE THE SERVER ADDRESS ---
  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr)); // Zero out the struct
  server_addr.sin_family = AF_INET;             // IPv4
  server_addr.sin_addr.s_addr =
      INADDR_ANY; // Listen on any available network interface
  server_addr.sin_port = htons(8080); // Listen on Port 8080

  // --- STEP 4: BIND SOCKET TO THE ADDRESS ---
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      SOCKET_ERROR) {
    std::cerr << "Bind failed.\n";
    closesocket(server_fd);
    WSACleanup();
    return 1;
  }

  // --- STEP 5: START LISTENING ---
  // 10 is the maximum length of the queue for pending connections
  if (listen(server_fd, 10) == SOCKET_ERROR) {
    std::cerr << "Listen failed.\n";
    closesocket(server_fd);
    WSACleanup();
    return 1;
  }

  std::cout << "Server is running on http://localhost:8080 ...\n";

  // --- STEP 6: THE MAIN ACCEPT LOOP ---
  while (true) {
    // This pauses the program (blocks) until someone tries to connect
    SOCKET client_socket = accept(server_fd, NULL, NULL);

    if (client_socket == INVALID_SOCKET) {
      int err = WSAGetLastError();
      std::cerr << "Accept failed with error: " << err << "\n";
      continue;
    }

    std::cout << "New connection accepted!\n";

    // Spawn a new thread to handle this specific client
    try {
      std::thread(handle_client, client_socket).detach();
    } catch (const std::exception &e) {
      std::cerr << "Thread creation failed: " << e.what() << "\n";
      closesocket(client_socket);
    }
  }

  // --- STEP 7: CLEANUP ---
  closesocket(server_fd);
  WSACleanup();
  return 0;
}

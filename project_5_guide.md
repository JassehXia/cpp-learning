# Project 5: Capstone - Multithreaded HTTP Server

This is the ultimate test of your C++ skills. You will build a functional web server that can serve real HTML files to a browser like Chrome.

## Objective
Build a program that can:
1. **Listen** for incoming connections on a specific port (e.g., 8080).
2. **Parse** incoming HTTP requests (GET /index.html HTTP/1.1).
3. **Resolve** the requested file on your hard drive.
4. **Serve** the file content back to the browser with correct headers.
5. **Handle Concurrent Users** by spawning a new thread for every client connection.

## New Engineering Concepts
- **Sockets (Berkeley Sockets/Winsock)**: The low-level API for network communication.
- **TCP/IP Handshake**: Understanding how computers "greet" each other.
- **HTTP/1.1 Protocol**: Parsing headers like `Content-Type` and `Content-Length`.
- **Statelessness**: Why the server forgets who you are as soon as the request ends.

## Windows Specifics (Winsock)
On Windows, you must "start" the networking library before using sockets:
```cpp
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

// Inside main:
WSADATA wsaData;
if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    // Handle error
}
```

## Recommended Roadmap
1. **The Listener**: Create a socket, bind it to a port, and wait for a connection.
2. **The Parser**: Convert the raw bytes from the socket into a `HTTPRequest` struct.
3. **The File System**: Check if `index.html` exists and read it as binary.
4. **The Multithreader**: Integrate your Phase 4 knowledge to handle multiple browsers at once.

## Hint Vault

### 1. Winsock Setup
Before you can send a single byte, you must initialize the library. 
```cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// Skeleton to start
int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return 1;

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // ... setup address and bind ...

    WSACleanup();
    return 0;
}
```

### 2. The HTTP "Handshake"
Your server doesn't need to be fancy yet. A valid HTTP response looks like this:
```cpp
std::string response = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 13\r\n"
    "\r\n"
    "Hello World!";
send(client_socket, response.c_str(), response.size(), 0);
```
> [!IMPORTANT]
> Note the `\r\n` (carriage return + line feed). HTTP header lines *must* end with these, and the headers are separated from the body by a double `\r\n\r\n`.

### 3. Handling Multiple Clients
Don't let one slow browser hang your whole server. Use `std::thread` to offload the work.
```cpp
void handle_client(SOCKET client_socket) {
    // Read request -> Solve file -> Send Response
    closesocket(client_socket);
}

// In your main loop:
while (true) {
    SOCKET client = accept(server_fd, NULL, NULL);
    std::thread client_thread(handle_client, client);
    client_thread.detach(); // Let it run independently
}
```

### 4. Reading Files as Binary
To serve images or HTML accurately, read the file in binary mode to avoid weird character conversions:
```cpp
std::ifstream file("index.html", std::ios::binary);
std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
```

---
Ready to start the skeleton?

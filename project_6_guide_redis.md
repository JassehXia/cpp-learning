# Project 6: Mini-Redis (In-Memory Key-Value Store)

This project moves away from the messy HTTP protocol and focuses on raw performance and thread-safe data structures. You are building the backbone of a real system.

## Objective
Build a server that can:
1. **Listen** for raw TCP connections.
2. **Accept Commands** in a simple format (e.g., `SET key value` or `GET key`).
3. **Store Data** in a `std::unordered_map`.
4. **Handle Concurrency** so multiple users can read/write data at the same time without crashing.

## Engineering Concepts
- **Thread-Safety**: Using `std::mutex` to protect your data.
- **Protocol Design**: Splitting a string like `"SET name Jasseh"` into parts your code can understand.
- **TCP Sockets**: Using the "Telephone" analogy without the "Web Browser" complexity.

## Roadmap
1. **The Listener**: Set up a basic TCP server using Winsock (re-use your Phase 5 knowledge).
2. **The Command Parser**: Create a function that takes a string and detects if it's a `SET`, `GET`, or `DEL`.
3. **The Data Store**: Implement a global (or class-based) map to store the keys/values.
4. **The Lock**: Add a mutex so two threads don't try to write to the map at the exact same microsecond.

## The Simple Protocol
To keep it easy, we will use plain text:
- `SET <key> <value>` -> Server stores it and returns `+OK\r\n`
- `GET <key>` -> Server returns the value or `$-1\r\n` if not found.

Ready to start the skeleton?

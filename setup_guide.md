# C++ Environment Setup for Windows

To follow this project-based path, you'll need a robust compiler and editor.

## 1. Install VS Code
- Download and install [VS Code](https://code.visualstudio.com/).
- Install the **C/C++ Extension Pack** (Microsoft).

## 2. Install Compiler (MSYS2/MinGW)
1. Download [MSYS2](https://www.msys2.org/).
2. Run the installer and open the MSYS2 terminal.
3. Update packages: `pacman -Syu`
4. Install GCC/G++: `pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain`
5. **Add to PATH**:
   - Add `C:\msys64\ucrt64\bin` to your System Environment Variables (PATH).

## 3. Verify Installation
Open a **NEW** standard Command Prompt or VS Code Terminal and type:
```bash
g++ --version
```

## 4. Install Build Tools
- Download and install [CMake](https://cmake.org/download/).
- Add CMake to PATH during installation.

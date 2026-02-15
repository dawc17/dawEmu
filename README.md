# dawEmu

C++ Game Boy emulator project with an OpenGL frontend.

## Prerequisites

- CMake 3.24+
- A C++20 compiler (MSVC, clang, or gcc)
- Git
- Python 3 (required by GLAD code generation)
- Python package: `jinja2`

Install `jinja2`:

```powershell
python -m pip install --user jinja2
```

## Build (Windows PowerShell)

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

## Run

```powershell
.\build\Debug\dawEmu.exe
```

## Run tests

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

## Notes

- Dependencies are fetched automatically with CMake `FetchContent` (GLFW, GLAD, Catch2).
- First build may take longer due to dependency download and GLAD source generation.
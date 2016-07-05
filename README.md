# nCine
nCine is a multi-platform 2d game engine

## Information

### Features
- OpenGL 2 / OpenGL ES 2 renderer
- Custom containers with iterators and algorithms
- Thread pool
- Streaming of OGG Vorbis audio
- Android assets support
- Joystick support
- SDL 1.2 / GLFW 3 support
- Font rendering (AngelCode's BMFont format)
- Particle system

### Supported platforms
- Windows (MSVC, MinGW)
- Mac Os X (LLVM)
- Linux (GCC, LLVM)
- Android (GCC, LLVM)

### Development Tools
- CMake
- Qt Creator
- Doxygen with GraphViz
- Valgrind
- Cppcheck
- git (originally Mercurial)

### Libraries
- GLEW
- GLFW 3
- SDL 1.2
- SDL_image
- libwebp
- libpng
- OpenAL
- libogg, libvorbis, libvorbisfile

## Tool Notes

### Cppcheck
`cppcheck --quiet --enable=all --inconclusive --std=c++03 -I include -I src/include src 2> cppcheck.log`

### Artistic Style
`./astyle --style=allman --indent=force-tab --attach-namespaces --indent-modifiers --indent-switches --indent-preproc-block --indent-preproc-cond --pad-oper --pad-header --add-brackets --keep-one-line-blocks --keep-one-line-statements --suffix=none --recursive "src/*" "include/*" "tests/*"`

## Developing

### Checklist
- compiler warnings
  - GCC + address sanitizer
  - LLVM
  - MSVC
- static analysis with Cppcheck
- memory analysis with Valgrind
- deploy and test on all platforms
  - check both GLFW 3 and SDL 1.2 support

### Coding conventions
- Indent with tabs (4 spaces wide)
- Allman brackets
  - Brackets around one line conditional statements
- Padding space after parenthesis headers (`if`, `do`, `while`, `for`, `switch`)
- `inline` keyword always before `virtual` and `static`
- Access specifiers order: `public`, `protected`, `private`
  - One half indent for access specifiers (2 spaces)
- Declarations order: typedefs and enums, data members, constructors, destructors, methods
  - Friend defined in the private section of a class, after everything else
- One space padding around operators
- Use of the `explicit` keyword all the times it makes sense

#### Naming conventions
- Pascal case for classes, enumerations, typedefs and constants
- Camel case for variables, functions and parameters
- All upper case for enumerators in an enumeration
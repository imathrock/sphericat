# What is cmake?

Starting from the basics, We have a C file, to compile the source code to an executable binary, we do the following:
```make
    gcc -o file file.c
```
file is the binary, file.c is the source code. We can put flags to optimize and other stuff like prefetch n stuff

```make
    gcc -O3 -o file file.c
```

Now to compile multiple files, liek if one depends on another?
```make
    gcc -o main main.c random.c -lm
```
main is the binary, main.c and random.c are the 2 files we use. 
If we compile it with -c flag instead of a -o flag we will get object files and we can use the -o to connect them using the same gcc command but use .o instead of .c. The -lm basically links the math library, an example of the previously mentioned flag. 

Now If you have like 128 c files, writing the gcc command would be ridicoulous, the kernel has like 20000 files, nobody is writing the gcc command for that. We use a makefile instead.

## Makefiles
Makefiles are automating a lot of this repetitive stuff, so instead of writing the whole compile statement we just write a makefile. The following is an example:

```make
all: hellow

hellow: hellow.c
    gcc -o hellow hellow.c

clean:
    rm -f hellow
```

What this does is automates running 100s even 1000s of files, All i have to do is call make, and it will make the object files and what not for us. 

make clean will remove binaries, make hellow will make only the hellow and make will call everything. 

Now makefiles can get more complicated

```make
CC = gcc

CFLAGS = -Wall -Wextra -g

TARGET = hellow

SRCS = hellow.c

all: $(TARGET)

$(TARGET): $(SRCS)
    $(CC) $(CFLAGS) -O $(TARGET) $(SRCS)

clean: 
    rm -f $(OBJS) $(TARGET)
```

We can add lots of files in srcs, lots of outputs in target and it runs it all in 1 command, this is shortening the work required in writing the makefile because if we have a new file we can just add the relative address int the srcs variable.

Now these makefiles can also get really long, like the one for linux kernel is like 2100 lines long. So Cmake is essentially automating the creation of makefile. However the C does not stand for "Create", it stands for "cross platform". As you can deduce this means that it will be able to create makefiles for all kinds of platforms.

## Cmake
CMake uses a config file called CMakeLists.txt 

- You define your project in CMakeLists.txt
- Run CMake to create Makefile
- Run make to build the project 
- Add code fix things, and build using the make 
- if new C files are added go back to the first step

Traditionally makefiles are places in the same directory are the soruce code. Which meand you go into the source directory and run make. But for CMake the makefile is generated in a different directory so that It does not overwhelm the soruce directory. 

We would have the following project structure:
```bash
- Hello.c
- CMakeLists.txt
- build/
    - Makefile
    - CMakeCache.txt
    - cmake_install.cmake
    - CMakeFiles/
    - hello # the object file

```

The following is an example of a CMakeLists.txt file:
```CMake
    cmake_minimum_required(VERSION 3.10)

    project(hellow)

    add_executable(hellow hellow.c)
```
Create a build directory, enter it, run 
```bash
cmake ..
```
then we will see a makefile in the build directory, run it and we will get out executable that we can run. 

As you can deduce, if we have more files we can just add more filenames of our dependencies in the add executable statement. 

Now similar to linking the math library we can use the following to add the correct links:

```cmake
    target_link_libraries(main PRIVATE m)
```
This CMakeLists.txt can build for different systems. It is amazing. 
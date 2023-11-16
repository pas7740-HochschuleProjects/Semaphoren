# Semaphoren
Semaphoren Libary for C

# How to install
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

# How to use
    main.c:
      #include <Semaphoren/sem.h>
    CMakeLists.txt:
      find_library(Semaphoren libSemaphoren.so)
      target_link_libraries(${PROJECT_NAME} PRIVATE ${Semaphoren})

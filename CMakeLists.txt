cmake_minimum_required(VERSION 3.10)

# --- PROGETTO ROBOTIC_HOME ---
project(robotic_home)

# cartelle dei file sorgente, librerie e test
include_directories(src)
include_directories(include)
include_directories(test)

# utilizzo standard C++11
set(CMAKE_CXX_STANDARD 11)

# definizione eseguibili
add_executable(main src/main.cpp)
add_executable(testCompiler test/test_compiler.cpp)

# definizione librerie
add_library(clock include/Clock.h src/Clock.cpp) # libreria Clock
add_library(device include/Device.h src/Device.cpp) # libreria Device
add_library(deviceM include/DeviceM.h src/DeviceM.cpp) # libreria DeviceM
add_library(deviceCP include/DeviceCP.h src/DeviceCP.cpp) # libreria DeviceCP

# dipendenze tra librerie
target_link_libraries(device clock) # link libreria Clock a Device
target_link_libraries(deviceM device) # link librerie Clock e Device a DeviceM
target_link_libraries(deviceCP device) # link librerie Clock e Device a DeviceCP

# dipendenze tra eseguibili e librerie
target_link_libraries(main deviceM deviceCP)

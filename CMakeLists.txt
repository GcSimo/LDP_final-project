cmake_minimum_required(VERSION 3.10)

# ----- PROGETTO DOMOTIC_HOME by ~BankAccount() -----
project(domotic_home)

# cartelle dei file sorgente, librerie e test
include_directories(include)
include_directories(src)
include_directories(test)

# utilizzo standard C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")

# definizione eseguibili
add_executable(main src/main.cpp) # programma completo
add_executable(test_clock test/test_clock.cpp) # test classe clock
add_executable(test_compiler test/test_compiler.cpp) #  test del compilatore usato
add_executable(test_device test/test_device.cpp) # test classi device
add_executable(test_home test/test_home.cpp) # test classi device
add_executable(test_slicing test/test_slicing.cpp) #  test dello slicing
add_executable(test_static_ID test/test_static_ID.cpp) # test variabili statiche

# definizione librerie
add_library(clock include/Clock.h src/Clock.cpp) # libreria Clock
add_library(device include/Device.h src/Device.cpp) # libreria Device
add_library(deviceM include/DeviceM.h src/DeviceM.cpp) # libreria DeviceM
add_library(deviceCP include/DeviceCP.h src/DeviceCP.cpp) # libreria DeviceCP
add_library(home include/Home.h src/Home.cpp) # libreria Home
add_library(parser include/Parser.h src/Parser.cpp) # libreria Parser

# dipendenze tra librerie
target_link_libraries(device clock) # link libreria Clock a Device
target_link_libraries(deviceM device) # link libreria Device a DeviceM
target_link_libraries(deviceCP device) # link libreria Device a DeviceCP
target_link_libraries(home deviceM deviceCP) # link librerie DeviceM e DeviceCP a Home
target_link_libraries(parser home) # link libreria Home a Parser

# dipendenze tra eseguibili e librerie
target_link_libraries(main parser)
target_link_libraries(test_clock clock)
target_link_libraries(test_device deviceM deviceCP)
target_link_libraries(test_home parser)

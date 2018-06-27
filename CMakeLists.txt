cmake_minimum_required(VERSION 3.10)
project(CVDemo)

#set(CUDA_USE_STATIC_CUDA_RUNTIME OFF) #禁用CUDA
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

add_executable(CVDemo main.cpp)
target_link_libraries(CVDemo ${OpenCV_LIBS}) #加入opencv lib

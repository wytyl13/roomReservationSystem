project(roomReservationSystem)
#file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.c")扫描目录下的所有文件存入变量
include_directories(./include)#指定头文件，相当于g++中的-I
add_compile_options(-Wall -fexec-charset=GBK) #if your terminal used gbk, you should add -fexec-charset=GBK
aux_source_directory(./src SRC_DIR_VAR)#扫描src目录下的所有文件并保存到变量中
#target_sources(${target} PRIVATE ${SRC_DIR_VAR})
add_executable(roomReservationSystem ${SRC_DIR_VAR})#使用传入变量的方式加入要编译的文件
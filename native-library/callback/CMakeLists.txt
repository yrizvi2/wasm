cmake_minimum_required(VERSION 3.14) 

project(wasm_callback) 

 

set(CMAKE_C_STANDARD 99) 

 

# Adjust this to your absolute path if needed 

set(WAMR_ROOT /home/yrizvi/webassembly/wasm-micro-runtime) 

 

include_directories(${WAMR_ROOT}/core/iwasm/include) 

 

add_executable(iwasm main.c) 

 

target_link_libraries(iwasm 

${WAMR_ROOT}/product-mini/platforms/linux/build/libiwasm.a 

pthread 

m 

dl 

) 

# 每个示例 = 一个可执行程序 + 一个 CTest，目录名对应 docs/01 的学习阶段。

add_executable(01_complex 01_complex/complex.cpp)
add_test(NAME 01_complex COMMAND 01_complex)

add_executable(02_string 02_string/string.cpp)
add_test(NAME 02_string COMMAND 02_string)

add_executable(03_object_model 03_object_model/polymorphism.cpp)
add_test(NAME 03_object_model COMMAND 03_object_model)

add_executable(04_gp_traits 04_gp_traits/traits.cpp)
add_test(NAME 04_gp_traits COMMAND 04_gp_traits)

add_executable(05_memory 05_memory/new_delete.cpp)
add_test(NAME 05_memory COMMAND 05_memory)

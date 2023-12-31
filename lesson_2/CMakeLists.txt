cmake_minimum_required(VERSION 3.10)

project(02.cpp14)

add_executable(auto auto.cpp)
add_executable(decltype decltype.cpp)
add_executable(lambda lambda.cpp)
add_executable(tuple tuple.cpp)
set_target_properties(auto decltype lambda tuple PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
if (MSVC)
    target_compile_options(auto PRIVATE
        /W4
    )
    target_compile_options(decltype PRIVATE
        /W4
    )
    target_compile_options(lambda PRIVATE
        /W4
    )
    target_compile_options(tuple PRIVATE
        /W4
    )
else ()
    target_compile_options(auto PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(decltype PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lambda PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(tuple PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

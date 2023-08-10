#
# Compiler settings
#

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)

#add_compile_options(-Werror)
add_compile_options(
    -Wall
    -Wextra
    -pedantic
)

add_compile_options(
    -Wno-gnu-zero-variadic-macro-arguments
)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

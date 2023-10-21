add_library(core "")

target_sources(core
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/calscontext.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/calculate.hpp
)
target_include_directories(core
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(core
    PUBLIC Qt6::Quick
)
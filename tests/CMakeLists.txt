set(tests
    01-xy
)

foreach(test ${tests})
    add_executable(${test} ${test}.cpp main.cpp)
    target_link_libraries(${test} ve Catch2::Catch2)
    add_test(NAME ${test} COMMAND ${test})
endforeach()

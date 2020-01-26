include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    )

add_executable(
    gtests
    ../src/main.cpp
    ../src/heap/heap_test.cpp
    ../src/io_data/mock_io_data_test.cpp
    ../src/list/list_node_test.cpp
    ../src/list/list_test.cpp
    ../src/queue/queue_test.cpp
    )

add_dependencies(gtests googletest)

target_link_libraries(
    gtests
    googletest
    bleu
    pthread
    )

include(CTest)

add_test(bleu_test ${PROJECT_BINARY_DIR}/gtests)

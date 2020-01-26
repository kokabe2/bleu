include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    )

add_library(
    bleu
    heap/gnu/heap.c
    io_data/mock_io_data.cpp
    list/list_node.c
    list/list.c
    queue/queue.c
    )

add_executable(
    gtests
    main.cpp
    heap/heap_test.cpp
    io_data/mock_io_data_test.cpp
    list/list_node_test.cpp
    list/list_test.cpp
    queue/queue_test.cpp
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

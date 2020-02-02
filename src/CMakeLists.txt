include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    )

add_library(
    bleu
    heap/gcc/heap.c
    io_data/mock_io_data.cpp
    list/list_node.c
    list/list.c
    queue/queue.c
    rng/xorshift/null_xorshift.c
    rng/xorshift/xorshift.c
    rng/xorshift/xorshift32.c
    rng/xorshift/xorshift64.c
    rng/xorshift/xorshift96.c
    rng/xorshift/xorshift128.c
    )

add_executable(
    gtests
    main.cpp
    heap/heap_test.cpp
    io_data/mock_io_data_test.cpp
    list/list_node_test.cpp
    list/list_test.cpp
    queue/queue_test.cpp
    rng/xorshift/null_xorshift_test.cpp
    rng/xorshift/xorshift_test.cpp
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

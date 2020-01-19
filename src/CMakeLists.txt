include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    )

add_library(
    bleu
    heap/gnu/heap.c
    list/list_node.c
    )

add_executable(
    gtests
    main.cpp
    heap/heap_test.cpp
    list/list_node_test.cpp
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

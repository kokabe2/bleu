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

#define _GNU_SOURCE
#include <liburing.h>
#include <linux/io_uring.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>

int main(){
    struct io_uring ring;
    struct io_uring_params params;
    params.flags = IORING_SETUP_SQPOLL_DAEMON;
    int fd = open("/home/hejohns/.vimrc", O_RDONLY);
    char buf[(1<<3) + 1];
    if(io_uring_queue_init_params(1<<20, &ring, &params)){
        perror("io_uring_queue_init_params");
        return EXIT_FAILURE;
    }
#if 0
    for(int i = 0; i < 1<<23; i++){
        struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
        io_uring_prep_read(sqe, fd, buf, 1<<3, -1);
        io_uring_submit(&ring);
        struct io_uring_cqe *cqe;
        memset(buf, 0, (1<<3) + 1);
        printf("[%d]: %s\n", i, buf);
    }
    for(int i = 0; i < 1<<23; i++){
        io_uring_wait_cqe(&ring, &cqe);
        io_uring_cqe_seen(&ring, cqe);
    }
    //cqe->user_data;
#endif
    io_uring_queue_exit(&ring);
    return EXIT_SUCCESS;
}

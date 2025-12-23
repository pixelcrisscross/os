#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/myfifo"
#define BUFFER_SIZE 256

int main() {
    int fd;
    const char *message = "Hello from writer process!";

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("Writer: FIFO created\n");

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("Writer: FIFO opened for writing\n");

    size_t message_length = strlen(message);
    if (write(fd, message, message_length) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Writer: Message written to FIFO\n");

    close(fd);

    return 0;
}
#include <stdio.h>
#include <pthread.h>

#include <unistd.h>
#include <sys/types.h>

struct message_t {
    int pid;
    char msg[1024];
};

void* read_thread(void* data) {
    FILE *fifoFile;

    fifoFile = fopen(data, "w+b");

    while (1) {
        struct message_t msg;

        fread(&msg, sizeof(msg), 1, fifoFile);
        
        if (msg.pid != getpid()) {
            printf(">%s", msg.msg);
        }
        else {
            // Так как FIFO файл один и не разделен на отдельные FIFO для записи и чтения,
            // то процесс может забрать из очереди своё же сообщение.
            // Поэтому при получении своего сообщения оно переотправляется.
            fwrite(&msg, sizeof(msg), 1, fifoFile);
            fflush(fifoFile);
        }
    }

    pthread_exit(0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Task #2 requries name of fifo file\n");
        return 1;
    }

    char *fifoName = argv[1];

    pthread_t r_thread;
    pthread_create(&r_thread, NULL, read_thread, fifoName);

    FILE *fifoFile;

    fifoFile = fopen(fifoName, "wb");

    if (fifoFile == NULL) {
        fprintf(stderr, "Cannot open fifo file!");
        return 1;
    }

    while (1) {
        struct message_t msg;
        msg.pid = getpid();

        fgets(msg.msg, sizeof(msg.msg), stdin);

        if (msg.msg == NULL) {
            printf("Cannot read data from stdin!");
            continue;
        }
        
        char success = fwrite(&msg, sizeof(msg), 1, fifoFile);
        if (!success) {
            printf("Error occured while writing the message!");
        }

        fflush(fifoFile);
    }

    if (fclose(fifoFile) == EOF) {
        perror("Can't close the FIFO");
        return 1;
    }

    return 0;
}
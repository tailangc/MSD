#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <message>\n";
        exit(1);
    }

    int pipe_fd[2];
    char buffer[BUFFER_SIZE];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process
        close(pipe_fd[1]);  // Close the write end of the pipe in the parent

        std::cout << "Parent process\n";

        wait(nullptr);  // Wait for the child process to exit

        ssize_t read_bytes = read(pipe_fd[0], buffer, BUFFER_SIZE);

        if (read_bytes == -1) {
            perror("Read from pipe failed");
            exit(1);
        }

        std::cout << "Received message from child: " << std::string(buffer, read_bytes) << '\n';

        close(pipe_fd[0]);  // Close the read end of the pipe in the parent
    } else {  // Child process
        close(pipe_fd[0]);  // Close the read end of the pipe in the child

        std::cout << "Child process\n";

        const char *message = argv[1];
        size_t message_length = strlen(message);

        // Send the message length to the parent
        if (write(pipe_fd[1], &message_length, sizeof(size_t)) == -1) {
            perror("Write to pipe failed");
            exit(1);
        }

        // Send the message to the parent
        if (write(pipe_fd[1], message, message_length) == -1) {
            perror("Write to pipe failed");
            exit(1);
        }

        close(pipe_fd[1]);  // Close the write end of the pipe in the child
        exit(0);
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sstream>
#include <algorithm>
#include <unistd.h>

#include "shelpers.h"

int main() {
    std::string input;
    while (std::getline(std::cin, input)) {
        if (input == "exit") {
            break;
        }
        std::vector<std::string> tokens = tokenize(input);
        std::vector<Command> commands = getCommands(tokens);

        if (!commands.empty()) {
            Command cmd = commands[0];

            pid_t pid = fork();
            if (pid == 0) {
                if (cmd.inputFd != STDIN_FILENO) {
                    dup2(cmd.inputFd, STDIN_FILENO);
                    close(cmd.inputFd);
                }
                // 输出重定向
                if (cmd.outputFd != STDOUT_FILENO) {
                    dup2(cmd.outputFd, STDOUT_FILENO);
                    close(cmd.outputFd);
                }

                std::vector<char*> argv;
                for (auto& arg : cmd.argv) {
                    argv.push_back(const_cast<char*>(arg)); // 移除 const 属性以适配 execvp
                }
                argv.push_back(nullptr);

                execvp(cmd.execName.c_str(), argv.data());
                perror("execvp failure");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
                if (status != 0) {
                    std::cerr << "Command failed with status " << status << std::endl;
                }
            } else {
                perror("fork failure");
            }

        }
    }
}
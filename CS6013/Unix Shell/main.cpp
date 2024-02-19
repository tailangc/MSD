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
            for (size_t i = 0; i < commands.size(); i++) {
                Command cmd = commands[0];
                if (cmd.execName == "cd") {
                    if (cmd.argv.size() >= 2) {
//                        const char* homeDir = getenv("HOME");
                        if (chdir(cmd.argv[1])) {
                            perror("cd");
                        }
                    }else {
                        std::cerr << "cd: HOME environment variable not set." << std::endl;
                    }
                    continue; // 继续下一个命令，如果有的话
                }


                //open pipe
                int pipefd[2];
                if (i < commands.size()) {
                    if (pipe(pipefd) == -1) {
                        perror("pipe error");
                        continue;
                    }
                    cmd.outputFd = pipefd[1];
                    commands[i + 1].inputFd = pipefd[0];
                }


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

                    std::vector<char *> argv;
                    for (auto &arg: cmd.argv) {
                        argv.push_back(const_cast<char *>(arg)); // 移除 const 属性以适配 execvp
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

                    //close pipe
                    if(i < commands.size() - 1){
                        close(pipefd[1]);
                    }
                    if(i > 0){
                        close(commands[i-1].inputFd);
                    }
                } else {
                    perror("fork failure");
                }

            }
            //part5
            size_t eqPos = input.find('=');

                std::string varName = input.substr(0, eqPos);
                std::string varValue = input.substr(eqPos + 1);
                if (setenv(varName.c_str(), varValue.c_str(), 1) == -1) {
                    perror("setenv");
                }
        }
    }
}

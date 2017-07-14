#include <cstdio>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

void interpret(const char* code_ptr) {
    if (code_ptr == NULL) {
        return;
    }

    size_t buffer_size = 30000;
    char* buffer = NULL;
    int  buffer_ptr = 0;
    std::stack<const char*> brackets;

    buffer = new char[buffer_size];
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 0;
    }

    while (*code_ptr != '\0') {
        switch (*code_ptr) {
            case '>':
                ++buffer_ptr;
                break;
            case '<':
                --buffer_ptr;
                break;
            case '+':
                ++buffer[buffer_ptr];
                break;
            case '-':
                --buffer[buffer_ptr];
                break;
            case '.':
                printf("%c", buffer[buffer_ptr]);
                break;
            case ',':
                buffer[buffer_ptr] = getchar(); 
                break;
            case '[':
                if (buffer[buffer_ptr] == 0) {
                    int outdent = 0;
                    while (true) {
                        ++code_ptr;
                        if (*code_ptr == '[') {
                            ++outdent;
                        } else if (*code_ptr == ']') {
                            if (outdent == 0) {
                                break;
                            } else {
                                --outdent;
                            }
                        }
                    }
                } else {
                    brackets.push(code_ptr);
                }
                break;
            case ']':
                if (buffer[buffer_ptr] != 0) {
                    code_ptr = brackets.top();
                } else {
                    brackets.pop();
                }
                break;
            default:
                break;
        }
        ++code_ptr;
    }

    delete[] buffer;
}

int main(int argc, char** argv) {
    std::string code_str = "";
    if (argc <= 1) {
        printf("usage: bf [-c code | -f source]\n");
    } else if (argc == 2) { 
        code_str = argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1], "-c") == 0) {
            code_str = argv[2];
        } else if (strcmp(argv[1], "-f") == 0) {
            std::ifstream infile(argv[2]);
            std::stringstream ss;
            char c;
            while (infile.get(c)) {
                ss << c;
            }
            code_str = ss.str();
        } else {
            printf("usage: bf [-c code | -f source]\n");
        }
    }

    interpret(code_str.c_str());

    return 0;
}

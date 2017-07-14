#include <cstdio>
#include <stack>

int main(int argc, char** argv) {
    const char* code_ptr = NULL;
    size_t buffer_size = 10000;
    char* buffer = NULL;
    int  buffer_ptr = 0;
    std::stack<const char*> brackets;

    if (argc <= 1) {
        printf("Usage: bf code\n");
    } else if (argc == 2) {
        code_ptr = argv[1];
    }

    buffer = new char[buffer_size];
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 0;
    }

    while (*code_ptr != '\0') {
        switch (*code_ptr) {
            case '>':
                buffer_ptr = (buffer_ptr + 1) % buffer_size;
                break;
            case '<':
                --buffer_ptr;
                buffer_ptr = buffer_ptr < 0 ? buffer_size - 1 : buffer_ptr;
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

    return 0;
}

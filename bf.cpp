#include <cstdio>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

void interpret(const char* code_ptr, bool smbf_flag = false) {
    if (code_ptr == NULL) {
        return;
    }

    size_t buffer_size = 30000;
    char* buffer = NULL;
    int  buffer_ptr = 0;
    std::stack<const char*> brackets;

    buffer = new char[buffer_size];
    if (!smbf_flag) {
        for (size_t i = 0; i < buffer_size; ++i) {
            buffer[i] = 0;
        }
    } else {
        const char* cp = code_ptr;
        for (size_t i = 0; i < buffer_size; ++i) {
            if (*cp != '\0') {
                buffer[i] = *cp;
                ++cp;
            } else {
                buffer[i] = 0;
            }
            buffer_ptr = cp - code_ptr;
        }
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
    // parse params
    std::string code_str = "";
    bool parse_flag = true;
    bool smbf_flag = false;
    if (argc <= 2) {
        parse_flag = false;
    } else {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-f") == 0) {
                if ((code_str == "") && (i != argc - 1)) {
                    std::ifstream infile(argv[++i]);
                    if (infile.is_open()) {
                        std::stringstream ss;
                        char c;
                        while (infile.get(c)) {
                            ss << c;
                        }
                        code_str = ss.str();
                    } else {
                        printf("Invalid filename: %s\n", argv[i]);
                        parse_flag = false;
                        break;
                    }
                } else {
                    parse_flag = false;
                    break;
                }
            } else if (strcmp(argv[i], "-c") == 0) {
                if ((code_str == "") && (i != argc - 1)) {
                    code_str = argv[++i];
                } else {
                    parse_flag = false;
                    break;
                }
            } else if (strcmp(argv[i], "--smbf") == 0) {
                smbf_flag = true;
            } else {
                parse_flag = false;
                break;
            }
        }
    }
    if (!parse_flag) {
        printf("usage: bf [--smbf] -f source | -c code\n");
        return EXIT_FAILURE;
    }

    interpret(code_str.c_str(), smbf_flag);

    return EXIT_SUCCESS;
}

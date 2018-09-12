int tokenize(char delim, char * line, int line_len, char ** buf, int buf_len) {
    int argc = 0;

    int i = 0;
    char last = delim;
    while(i < line_len) {
        char c = line[i];
        if(c == delim) {
            line[i] = 0;
        } else if(last == delim) {
            if (argc < buf_len) {
                buf[argc] = &line[i];
                argc += 1;
            }
        }
        last = c;
        i += 1;
    }

    return argc;
}
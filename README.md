# Get_next_line

A C function that reads a line from a file descriptor. This project focuses on handling file I/O efficiently, when called in a loop, it will allow reading a file line by line until the end

## Usage

1. Clone the repository
```sh
git clone https://github.com/andrexandre/get_next_line.git ; cd get_next_line
```

2. Create a file `main.c`
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("main.c", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

3. Compile your program with the file `get_next_line.c`
```sh
cc -o main main.c get_next_line.c
```
> It's also possible to define the buffersize by adding `-D BUFFER_SIZE=42`

4. And finally, run your program
```sh
./main
```

For the bonus function
```sh
cc -o main main.c get_next_line_bonus.c
```
> The bonus implements handling multiple file descriptors simultaneously without losing the reading thread of each file descriptor

> [!NOTE]
> This project is part of the 42 School curriculum

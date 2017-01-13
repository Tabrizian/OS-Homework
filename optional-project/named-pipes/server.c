#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int
main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime (&rawtime);

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);
    char datetime[100];
    strcpy(datetime, asctime(timeinfo));
    write(fd, datetime, sizeof(datetime));
    close(fd);

    unlink(myfifo);

    return 0;
}

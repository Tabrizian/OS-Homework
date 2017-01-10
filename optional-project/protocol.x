struct date {
    char *format;
};

program DATETIME {
    version DATETIME_1 {
        int ADD(date) = 1;
    } = 1;
} = 0x2fffffff;

struct result {
    char res[100];
    int len;
};
program DATETIME {
    version DATETIME_1 {
        struct result GETDATE() = 1;
    } = 1;
} = 0x2fffffff;

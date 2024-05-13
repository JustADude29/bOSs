#include <kernel/io.h>

void iowait() { outportb(0x80, 0); }

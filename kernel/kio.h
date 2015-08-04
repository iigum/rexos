/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2015, Alexey Kramarenko
    All rights reserved.
*/

#ifndef KIO_H
#define KIO_H

#include "kipc.h"
#include "kprocess.h"
#include "../userspace/dlist.h"
#include "../userspace/io.h"
#include "dbg.h"
#include <stdbool.h>

typedef struct {
    DLIST list;
    MAGIC;
    IO* io;
    KPROCESS* owner;
    KPROCESS* granted;
    bool kill_flag;
}KIO;

//called from svc
void kio_create(IO** io, unsigned int size);
void kio_send(KIO* kio, IPC* ipc);
void kio_call(KIO* kio, IPC* ipc);
void kio_destroy(KIO* io);

#endif // KIO_H

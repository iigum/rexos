/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2014, Alexey Kramarenko
    All rights reserved.
*/

#include "libusb.h"
#include "../direct.h"
#include "../../sys/usb.h"

bool libusb_register_persistent_descriptor(HANDLE usbd, USBD_DESCRIPTOR_TYPE type, unsigned int index, unsigned int lang, const void* descriptor)
{
    char buf[USBD_DESCRIPTOR_REGISTER_STRUCT_SIZE_ALIGNED + sizeof(const void**)];
    USBD_DESCRIPTOR_REGISTER_STRUCT* udrs = (USBD_DESCRIPTOR_REGISTER_STRUCT*)buf;

    udrs->flags = USBD_FLAG_PERSISTENT_DESCRIPTOR;
    udrs->index = index;
    udrs->lang = lang;
    *(const void**)(buf + USBD_DESCRIPTOR_REGISTER_STRUCT_SIZE_ALIGNED) = descriptor;
    direct_enable_read(usbd, buf, USBD_DESCRIPTOR_REGISTER_STRUCT_SIZE_ALIGNED + sizeof(const void**));
    ack(usbd, USBD_REGISTER_DESCRIPTOR, type, USBD_DESCRIPTOR_REGISTER_STRUCT_SIZE_ALIGNED + sizeof(const void**), 0);
    return get_last_error() == ERROR_OK;
}

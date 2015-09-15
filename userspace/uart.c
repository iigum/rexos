/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2015, Alexey Kramarenko
    All rights reserved.
*/

#include "uart.h"
#include "sys_config.h"
#include "object.h"

void uart_encode_baudrate(BAUD* baudrate, IPC* ipc)
{
    ipc->param2 = baudrate->baud;
    ipc->param3 = (baudrate->data_bits << 16) | (baudrate->parity << 8) | baudrate->stop_bits;
}

void uart_decode_baudrate(IPC* ipc, BAUD* baudrate)
{
    baudrate->baud = ipc->param2;
    baudrate->data_bits = (ipc->param3 >> 16) & 0xff;
    baudrate->parity = (ipc->param3 >> 8) & 0xff;
    baudrate->stop_bits = (ipc->param3) & 0xff;
}

void uart_setup_printk(int num)
{
    ack(object_get(SYS_OBJ_UART), HAL_CMD(HAL_UART, IPC_UART_SETUP_PRINTK), num, 0, 0);
}

void uart_setup_stdout(int num)
{
    object_set(SYS_OBJ_STDOUT, get(object_get(SYS_OBJ_UART), HAL_CMD(HAL_UART, IPC_GET_TX_STREAM), num, 0, 0));
}

void uart_setup_stdin(int num)
{
    object_set(SYS_OBJ_STDIN, get(object_get(SYS_OBJ_UART), HAL_CMD(HAL_UART, IPC_GET_RX_STREAM), num, 0, 0));
}

void uart_open(int num, unsigned int mode)
{
    ack(object_get(SYS_OBJ_UART), HAL_CMD(HAL_UART, IPC_OPEN), num, mode, 0);
}

void uart_close(int num)
{
    ack(object_get(SYS_OBJ_UART), HAL_CMD(HAL_UART, IPC_CLOSE), num, 0, 0);
}

void uart_set_baudrate(int num, BAUD* baudrate)
{
    IPC ipc;
    uart_encode_baudrate(baudrate, &ipc);
    ipc.cmd = HAL_CMD(HAL_UART, IPC_UART_SET_BAUDRATE);
    ipc.param1 = num;
    ipc.process = object_get(SYS_OBJ_UART);
    call(&ipc);
}

void uart_flush(int num)
{
    ack(object_get(SYS_OBJ_UART), HAL_CMD(HAL_UART, IPC_FLUSH), num, 0, 0);
}
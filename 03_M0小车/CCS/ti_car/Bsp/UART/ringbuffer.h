// #ifndef RINGBUFFER_H
// #define RINGBUFFER_H

// #include "bsp_system.h"

// #define RINGBUFFER_SIZE (30)

// typedef struct {
//     uint32_t w;
//     uint32_t r;
//     uint8_t buffer[RINGBUFFER_SIZE];
//     uint32_t itemCount;
// }ringbuffer_t;

// void ringbuffer_init(ringbuffer_t *rb);
// uint8_t ringbuffer_is_full(ringbuffer_t *rb);
// uint8_t ringbuffer_is_empty(ringbuffer_t *rb);
// int8_t ringbuffer_write(ringbuffer_t *rb, uint8_t *data, uint32_t num);
// int8_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data, uint32_t num);
// int8_t ringbuffer_peek_one(ringbuffer_t *rb, uint8_t *out);
// bool rb_peek(char *c);
// bool rb_get(char *c) ;
// extern ringbuffer_t usart_rb;

// #endif

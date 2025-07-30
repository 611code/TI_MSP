// #include "ringbuffer.h"

// // ��ʼ�����λ�����
// void ringbuffer_init(ringbuffer_t *rb)
// {
//     // ���ö�ָ����дָ����ʼֵΪ0
//     rb->r = 0;
//     rb->w = 0;
//     // ���������ڴ�����
//     memset(rb->buffer, 0, sizeof(uint8_t) * RINGBUFFER_SIZE);
//     // ��ʼ����Ŀ����Ϊ0
//     rb->itemCount = 0;
// }

// // ���黷�λ������Ƿ�����
// uint8_t ringbuffer_is_full(ringbuffer_t *rb)
// {
//     // ������Ŀ�������ڻ�������С������1�������������򷵻�0��δ����
//     return (rb->itemCount == RINGBUFFER_SIZE);
// }

// // ���黷�λ������Ƿ�Ϊ��
// uint8_t ringbuffer_is_empty(ringbuffer_t *rb)
// {
//     // ������Ŀ����Ϊ0������1��Ϊ�գ������򷵻�0���ǿգ�
//     return (rb->itemCount == 0);
// }
// int8_t ringbuffer_peek_one(ringbuffer_t *rb, uint8_t *out) {
//     if (ringbuffer_is_empty(rb)) {
//         return -1;
//     }
//     // ???? r ???????
//     uint32_t idx = rb->r % RINGBUFFER_SIZE;
//     *out = rb->buffer[idx];
//     return 0;
// }
// /**
//  * @brief ?????????
//  * 
//  * @param c  ??????
//  * @return true   ??(?????,*c ???)
//  * @return false  ????
//  */
// bool rb_peek(char *c) {
//     uint8_t tmp;
//     // ringbuffer_peek_one ?? 0 ????
//     if (ringbuffer_peek_one(&usart_rb, &tmp) == 0) {
//         *c = (char)tmp;
//         return true;
//     }
//     return false;
// }

// /**
//  * @brief ????????
//  * 
//  * @param c  ??????
//  * @return true   ??(?????,*c ??????)
//  * @return false  ????
//  */
// bool rb_get(char *c) {
//     uint8_t tmp;
//     // ringbuffer_read ?? 0 ????????????
//     if (ringbuffer_read(&usart_rb, &tmp, 1) == 0) {
//         *c = (char)tmp;
//         return true;
//     }
//     return false;
// }
// // �����λ�����д������
// int8_t ringbuffer_write(ringbuffer_t *rb, uint8_t *data, uint32_t num)
// {
//     // ��������������������-1
//     if(ringbuffer_is_full(rb))
//         return -1;
        
//     // ������д�뻺����
//     while(num--)
//     {
//         rb->buffer[rb->w] = *data++;  // д�����ݲ��ƶ�дָ��
//         rb->w = (rb->w + 1) % RINGBUFFER_SIZE;  // дָ��ѭ������
//         rb->itemCount++;  // ������Ŀ����
//     }
    
//     return 0;  // д���ɹ�����0
// }

// // �ӻ��λ�������ȡ����
// int8_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data, uint32_t num)
// {
//     // ����������Ϊ�գ�����-1
//     if(ringbuffer_is_empty(rb))
//         return -1;
    
//     // �ӻ�������ȡ����
//     while(num--)
//     {
//         *data++ = rb->buffer[rb->r];  // ��ȡ���ݲ��ƶ���ָ��
//         rb->r = (rb->r + 1) % RINGBUFFER_SIZE;  // ��ָ��ѭ������
//         rb->itemCount--;  // ������Ŀ����
//     }
//     return 0;  // ��ȡ�ɹ�����0
// }

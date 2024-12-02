#ifndef PACKET_TRANSMISSION_H
#define PACKET_TRANSMISSION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// +----------+--------+---------+---------+
// | Header   | Length | Payload | CRC     |
// +----------+--------+---------+---------+

// 定义协议头部的固定值
#define HEADER 0xAABB

// 定义最大负载大小
#define MAX_PAYLOAD_SIZE 256

// 数据包结构体
typedef struct {
    uint16_t header;   // 协议头
    uint16_t length;   // 包长度
    uint16_t payload[MAX_PAYLOAD_SIZE]; // 负载数据
    uint16_t crc;      // 校验码
} Packet;

int pack_packet(uint8_t *buffer, const uint8_t *payload, size_t payload_len);
int unpack_packet(const uint8_t *buffer, size_t buffer_len, uint8_t *payload, size_t *payload_len);
int packet_test(void);

#endif

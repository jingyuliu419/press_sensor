#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "packet_transmission.h"
#include "adc.h"

// CRC计算函数（简单实现）
uint16_t calculate_crc(const uint8_t *data, size_t len) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

// 封包函数
int pack_packet(uint8_t *buffer, const uint8_t *payload, size_t payload_len) {
    if (payload_len > MAX_PAYLOAD_SIZE * sizeof(uint16_t)) {
        printf("Payload size exceeds maximum limit.\n");
        return 0;
    }

    Packet packet;
    packet.header = HEADER;
    packet.length = payload_len;
    memcpy(packet.payload, payload, payload_len);

    size_t crc_data_len = sizeof(packet.header) + sizeof(packet.length) + sizeof(packet.payload);
    packet.crc = calculate_crc((uint8_t *)&packet, crc_data_len);

    memcpy(buffer, &packet, sizeof(Packet));

#if 1
    printf("payload_len : %d\r\n", packet.length);
    hexdump(&packet, sizeof(packet), (uintptr_t)&packet);
#endif

    return 0;
}

int unpack_packet(const uint8_t *buffer, size_t buffer_len, uint8_t *payload, size_t *payload_len) {
    Packet packet;

    if (buffer_len != sizeof(Packet)) {
        printf("Invalid packet length.\n");
        return -1;
    }

    memcpy(&packet, buffer, sizeof(Packet));

    if (packet.header != HEADER) {
        printf("Invalid packet header.\n");
        return -1;
    }

    // 校验CRC
    size_t crc_data_len = sizeof(packet.header) + sizeof(packet.length) + sizeof(packet.payload);
    uint16_t calculated_crc = calculate_crc(buffer, crc_data_len);
    if (calculated_crc != packet.crc) {
        printf("CRC check failed.\n");
        return -1;
    }

    *payload_len = (size_t)packet.length;
    memcpy(payload, packet.payload, *payload_len);

    return 0;
}

// 测试代码
int packet_test(void) {
    uint8_t buffer[sizeof(Packet)];
    uint8_t payload[] = "Hello, transparent transmission!";
    size_t payload_len = strlen((char *)payload);
    int ret;

    // 封包
    ret = pack_packet(buffer, payload, payload_len);
    if (ret) {
        printf("Packet packed successfully.\r\n");
    }

    // 解包
    uint8_t unpacked_payload[sizeof(Packet)];
    size_t unpacked_payload_len;

    if (unpack_packet(buffer, sizeof(Packet), unpacked_payload, &unpacked_payload_len) == 0) {
        printf("Packet unpacked successfully.\r\n");
        printf("Payload: %.*s\n", (int)unpacked_payload_len, unpacked_payload);
    } else {
        printf("Packet unpacked fail.\r\n");
    }

    return 0;
}

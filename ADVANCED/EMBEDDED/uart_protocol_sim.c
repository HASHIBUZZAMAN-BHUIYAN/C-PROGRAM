/*
 * UART Serial Protocol Simulation
 *
 * MODELS:    A basic framed UART protocol:
 *              [START=0xAA] [LENGTH] [PAYLOAD...] [CHECKSUM]
 * SIMULATED: Two "devices" communicating via an in-memory byte buffer.
 * REAL HW:   Replace sim_uart_write/read with HAL_UART_Transmit/Receive
 *            (STM32) or Serial.write/read (Arduino).
 *
 * Compile: gcc uart_protocol_sim.c -o uart_protocol_sim.exe
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define START_BYTE  0xAA
#define MAX_PAYLOAD 64
#define UART_BUF    256

/* Simulated UART buffer (circular in a real MCU, simple array here) */
static uint8_t uart_buf[UART_BUF];
static int     uart_buf_len = 0;

/* ---- Checksum (XOR of all payload bytes) ---- */
uint8_t compute_checksum(const uint8_t *data, int len) {
    uint8_t cs = 0;
    for (int i = 0; i < len; i++) cs ^= data[i];
    return cs;
}

/* ---- Framing: write a packet into the simulated UART buffer ---- */
void uart_send_packet(const char *msg) {
    int len = (int)strlen(msg);
    if (len > MAX_PAYLOAD) len = MAX_PAYLOAD;

    uart_buf[uart_buf_len++] = START_BYTE;
    uart_buf[uart_buf_len++] = (uint8_t)len;
    for (int i = 0; i < len; i++) uart_buf[uart_buf_len++] = (uint8_t)msg[i];
    uart_buf[uart_buf_len++] = compute_checksum((uint8_t*)msg, len);

    printf("[TX] Frame: AA %02X ", len);
    for (int i = 0; i < len; i++) printf("%02X ", (uint8_t)msg[i]);
    printf("%02X\n", compute_checksum((uint8_t*)msg, len));
}

/* ---- Receive and validate a packet from the buffer ---- */
typedef struct { char payload[MAX_PAYLOAD+1]; int ok; } Packet;

Packet uart_recv_packet(int *offset) {
    Packet p = {0};
    if (*offset >= uart_buf_len) return p;

    if (uart_buf[*offset] != START_BYTE) { (*offset)++; return p; }
    (*offset)++;

    int len = uart_buf[(*offset)++];
    if (*offset + len + 1 > uart_buf_len) return p;

    uint8_t *payload = uart_buf + *offset;
    *offset += len;
    uint8_t rx_cs    = uart_buf[(*offset)++];
    uint8_t calc_cs  = compute_checksum(payload, len);

    memcpy(p.payload, payload, len);
    p.payload[len] = '\0';
    p.ok = (rx_cs == calc_cs);
    return p;
}

int main(void) {
    printf("=== UART Protocol Simulation ===\n");
    printf("Frame format: [0xAA][LEN][PAYLOAD...][CHECKSUM_XOR]\n\n");

    /* Send several packets */
    uart_send_packet("HELLO");
    uart_send_packet("SENSOR:T=23.5");
    uart_send_packet("CMD:MOTOR_ON");

    /* Inject a corrupted packet manually */
    printf("[TX] Injecting corrupted frame...\n");
    int inject_at = uart_buf_len;
    uart_send_packet("CORRUPT");
    uart_buf[inject_at + 3] ^= 0xFF;   /* flip bits in first payload byte */

    /* Receive all packets */
    printf("\n--- Receiving ---\n");
    int offset = 0;
    int pkt = 0;
    while (offset < uart_buf_len) {
        Packet p = uart_recv_packet(&offset);
        if (p.payload[0]) {
            pkt++;
            printf("[RX] Packet %d: \"%s\"  checksum=%s\n",
                   pkt, p.payload, p.ok ? "OK" : "FAILED (corrupted)");
        }
    }
    return 0;
}

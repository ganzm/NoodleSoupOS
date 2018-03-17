#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */


void serial_configure_baud_rate(uint16_t com, uint16_t divisor);

void serial_configure_line(uint16_t com);

int serial_is_transmit_fifo_empty(uint16_t com);

void serial_send(uint16_t com, char c);

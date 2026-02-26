#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "dmx_tx.pio.h"

#define DMX_PIN        2
#define DMX_CHANNELS   512
#define DMX_BAUD       250000

#define DMX_BREAK_US   100
#define DMX_MAB_US     12

PIO dmx_pio = pio0;
uint dmx_sm = 0;
uint dmx_offset;

uint8_t dmx_buffer[DMX_CHANNELS + 1];

void dmx_pio_init() {

    dmx_offset = pio_add_program(dmx_pio, &dmx_tx_program);

    pio_sm_config c = dmx_tx_program_get_default_config(dmx_offset);

    // Map output pin
    sm_config_set_out_pins(&c, DMX_PIN, 1);
    sm_config_set_sideset_pins(&c, DMX_PIN);

    // Shift out LSB first, autopull at 8 bits
    sm_config_set_out_shift(&c, true, true, 8);

    // 4 cycles per bit
    float div = (float)clock_get_hz(clk_sys) / (DMX_BAUD * 4);
    sm_config_set_clkdiv(&c, div);

    pio_gpio_init(dmx_pio, DMX_PIN);
    pio_sm_set_consecutive_pindirs(dmx_pio, dmx_sm, DMX_PIN, 1, true);

    pio_sm_init(dmx_pio, dmx_sm, dmx_offset, &c);
    pio_sm_set_enabled(dmx_pio, dmx_sm, true);

    dmx_buffer[0] = 0x00;  // Start code
}

void dmx_send_frame() {

    // Disable state machine so we can drive line manually
    pio_sm_set_enabled(dmx_pio, dmx_sm, false);

    gpio_set_function(DMX_PIN, GPIO_FUNC_SIO);
    gpio_set_dir(DMX_PIN, GPIO_OUT);

    // BREAK
    gpio_put(DMX_PIN, 0);
    sleep_us(DMX_BREAK_US);

    // MAB
    gpio_put(DMX_PIN, 1);
    sleep_us(DMX_MAB_US);

    // Return control to PIO
    gpio_set_function(DMX_PIN, GPIO_FUNC_PIO0);
    pio_sm_set_enabled(dmx_pio, dmx_sm, true);

    // Send 513 bytes
    for (int i = 0; i < DMX_CHANNELS + 1; i++) {
        pio_sm_put_blocking(dmx_pio, dmx_sm, dmx_buffer[i]);
    }
}

int main() {

    stdio_init_all();
    sleep_ms(1000);

    printf("PIO DMX Transmitter Starting...\n");

    dmx_pio_init();

    uint8_t level = 0;

    while (true) {

        // Simple ramp pattern
        for (int i = 1; i <= DMX_CHANNELS; i++) {
            dmx_buffer[i] = level;
        }

        dmx_send_frame();

        level++;
        sleep_ms(25);   // ~40 FPS
    }
}
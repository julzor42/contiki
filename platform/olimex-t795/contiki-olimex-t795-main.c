#include <contiki.h>
#include <clock.h>
#include <pic32.h>
#include <pic32_clock.h>
#include <dev/watchdog.h>
#include <platform-init.h>
#include <debug-uart.h>
#include <pic32_irq.h>
#include "dev/serial-line.h"
#include <leds.h>
#include <sensors.h>
#include "button-sensor.h"
#include "dev/common-clicks.h"
#include "dev/interrupts.h"

void (*interrupt_isr)(void) = NULL;

#define UART_DEBUG_BAUDRATE 115200

SENSORS(&button_sensor, &button_sensor2);

/*---------------------------------------------------------------------------*/
int
main(int argc, char **argv)
{
  int32_t r = 0;

  pic32_init();
  watchdog_init();
  clock_init();
  leds_init();
  platform_init();

  process_init();
  process_start(&etimer_process, NULL);
  ctimer_init();
  rtimer_init();

  process_start(&sensors_process, NULL);
  SENSORS_ACTIVATE(button_sensor);
  SENSORS_ACTIVATE(button_sensor2);

  dbg_setup_uart(UART_DEBUG_BAUDRATE);
#ifdef __USE_UART_PORT3__
  uart3_set_input(serial_line_input_byte);
#elif  __USE_UART_PORT2__
  uart2_set_input(serial_line_input_byte);
#endif
  serial_line_init();

  autostart_start(autostart_processes);
  watchdog_start();

  while(1) {
    do {
      watchdog_periodic();
      r = process_run();
    } while(r > 0);
    watchdog_stop();
    asm volatile("wait");
    watchdog_start();
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
ISR(_CHANGE_NOTICE_VECTOR)
{
  if(BUTTON1_CHECK_IRQ()) {
    /* Button1 was pressed */
    button1_isr();
  } else if(BUTTON2_CHECK_IRQ()) {
    /* Button2 was pressed */
    button2_isr();
#ifdef MOTION_CLICK
  } else if(MOTION_SENSOR_CHECK_IRQ()) {
    /* Motion was detected */
    motion_sensor_isr();
#elif PROXIMITY_CLICK
  } else if(PROXIMITY_SENSOR_CHECK_IRQ()) {
    /* Proximity was detected */
    proximity_sensor_isr();
#endif
  }
  else if(INTERRUPT_CHECK_IRQ() && interrupt_isr != NULL) {
    interrupt_isr();
  }
}

/*---------------------------------------------------------------------------*/

#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

#define DEBUG_HIGHER_LEVELS 0

#include <inttypes.h>

/* Include project config file if defined in the project Makefile */
#ifdef PROJECT_CONF_H
  #include "project-conf.h"
#endif /* PROJECT_CONF_H */

#define CCIF
#define CLIF

typedef uint16_t uip_stats_t;
typedef uint32_t clock_time_t;
typedef uint32_t rtimer_clock_t;

#define RTIMER_CLOCK_LT(a,b) ((int32_t)((a)-(b)) < 0)

#define CLOCK_CONF_SECOND                       1024

#define NETSTACK_CONF_WITH_IPV6                 1

/*
 * There are 2 red LEDs on the board, LED1 is mapped to the Contiki LEDS_RED
 * and LED2 is mapped to LEDS_GREEN
 */
#define LED1                                    LEDS_RED
#define LED2                                    LEDS_GREEN

#endif /* CONTIKI_CONF_H */

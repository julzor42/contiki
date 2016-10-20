# Using Contiki on Olimex T795

## Overview

This section explains how to build Contiki code for Olimex T795 and to flash the compiled application image on Olimex T795

## Revision History

| revision  | changes from previous revision |
|---------- |------------------------------- |
| 1.0.0     | Initial release                |

## Package Content

Some key paths where IMG have added source code to support Contiki on Olimex T795:

| Folder              				| Content                                              							                      |
| :----               				| :----                                                							                      |
| platform/olimex-t795			        | Porting of drivers for peripherals like Button, LED, etc. on Olimex T795			                              |
| examples/olimex-t795                          | Applications for Olimex T795 board                                                                                          |         

## Getting Started

The xc32 compiler version 1.42 from Microchip can be used for compilation of the source code. Download the xc32 compiler from
<a href="http://www.microchip.com/pagehandler/en_us/devtools/mplabxc/">Microchip's website</a> and add tool chain path in the
environment variables and compile an example, say "Hello World" which is included in Contiki as per below:

    $ export PATH=$PATH:/opt/microchip/xc32/v1.42/bin/

For debugging purposes, UART3 will be used by default, but USE_SERIAL_PADS can be selected for UART2.The application e.g. Hello World can be built for Olimex T795 and HEX file can be generated to flash on the board along with possible build options as per below:

    $ cd examples/hello-world
    $ make TARGET=olimex-t795 USE_SERIAL_PADS=1
    $ /opt/microchip/xc32/v1.42/bin/xc32-bin2hex hello-world.olimex-t795
 


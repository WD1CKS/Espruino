#!/bin/false
# This file is part of Espruino, a JavaScript interpreter for Microcontrollers
#
# Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# ----------------------------------------------------------------------------------------
# This file contains information for a specific board - the available pins, and where LEDs,
# Buttons, and other in-built peripherals are. It is used to build documentation as well
# as various source and header files for Espruino.
# ----------------------------------------------------------------------------------------

import pinutils;
info = {
 'name' : "TYT MD-380/390 Discovery",
 'link' :  [ "http://www.tyt888.com/?mod=product_show&id=78" ],
 #'default_console' : "EV_SERIAL2", # FIXME: This was S2 because of pin conflict. Not sure if it's really an issue?
 'default_console' : "EV_USBSERIAL",
 'variables' : 5450,
 'binary_name' : 'espruino_%v_tyt.bin',
 'bootloader' : 1,
 'build' : {
   'optimizeflags' : '-O3',
   'libraries' : [
     'LCD_FSMC',
     'GRAPHICS',
   ],
   'makefile' : [
     'DEFINES+=-DUSE_USB_OTG_FS=1 -DSTM32F40_41xxx -DUSB_NO_VBUS_SENSE',
     'STLIB=STM32F405xx',
     'PRECOMPILED_OBJS+=$(ROOT)/targetlibs/stm32f4/lib/startup_stm32f40xx.o'
   ]
  }
};
chip = {
  'part' : "STM32F405VGT6",
  'family' : "STM32F4",
  'package' : "LQFP100",
  'ram' : 127, # 0x0001 8000 long, from 0x2000 0000 to 0x2001 7FFF
  'flash' : 512, # 0x0008 0000 long, from 0x0800 0000 to 0x0807 FFFF
  'speed' : 100,
  'usart' : 3,
  'spi' : 3,
  'i2c' : 3,
  'adc' : 3,
  'dac' : 2,
  'saved_code' : {
    # code size 225248 = 0x36FE0 starts at 0x0800 c000 ends at 0x0804 3FE0
    # so we have some left room for Espruino firmware and no risk to clear it while saving
    'address' : 0x08060000, # flash_saved_code_start 0x0806 0000 to 0x807 5000
    # we have enough flash space in this single flash page to save all of the ram
    'page_size' :  131072, # size of pages : on STM32F411, last 2 pages are 128 Kbytes
    # we use the last flash page only, furthermore it persists after a firmware flash of the board
    'pages' : 1, # count of pages we're using to save RAM to Flash,
    'flash_available' : 512 - 48 # binary will have a hole in it, so we just want to test against full size
  },
  'place_text_section' : 0x0800c000, # note flash_available above
};

devices = {
  'OSC' : { 'pin_1' : 'H0',
            'pin_2' : 'H1' },
  'OSC_RTC' : { 'pin_1' : 'C14',
                'pin_2' : 'C15' },
  'LED1' : { 'pin' : 'E0' },
  'LED2' : { 'pin' : 'E1' },
  'BTN1' : { 'pin' : 'E11', 'inverted' : True, 'pinstate' : 'IN' },
  'BTN2' : { 'pin' : 'E12', 'inverted' : True, 'pinstate' : 'IN' },
  'USB' : { 'pin_dm' : 'A11',
            'pin_dp' : 'A12', },
  'LCD' : {
            'width' : 160, 'height' : 128, 'bpp' : 16, 'controller' : 'fsmc',
            'pin_d0' : 'D14',
            'pin_d1' : 'D15',
            'pin_d2' : 'D0',
            'pin_d3' : 'D1',
            'pin_d4' : 'E7',
            'pin_d5' : 'E8',
            'pin_d6' : 'E9',
            'pin_d7' : 'E10',
            'pin_rd' : 'D4',
            'pin_wr' : 'D5',
            'pin_cs' : 'D6',
            'pin_rs' : 'D12',
            'pin_bl' : 'C6',
            'pin_reset' : 'D13'
          },
};

# left-right, or top-bottom order
board = {
  'left' : [ 'GND', 'VDD', 'GND', 'C1','C3','A1','A3','A5','A7','C5','B1','GND','E7','E9','E11','E13','E15','B11','B13','B15','D9','D11','D13','D15','GND'],
  'left2' : [ 'GND', 'VDD', 'NRST', 'C0','C2','A0','A2','A4','A6','C4','B0','B2','E8','E10','E12','E14','B10','B12','B14','D8','D10','D12','D14','NC','GND'],
  'right2' : [ 'GND', '5V', '3V3', 'H0', 'C14','E6','E4','E2','E0','B8','BOOT0','B6','B4','D7','D5','D3','D1','C12','C10','A14','A10','A8','C8','C6','GND'],
  'right' : [ 'GND', '5V', '3V3', 'H1', 'C15','C13','E5','E3','E1','B9','VDD','B7','B5','B3','D6','D4','D2','D0','C11','A15','A13','A9','C9','C7','GND'],
};
board["_css"] = """
#board {
  width: 680px;
  height: 1020px;
  left: 200px;
  background-image: url(img/STM32F411DISCOVERY.jpg);
}
#boardcontainer {
  height: 1020px;
}
#left {
  top: 375px;
  right: 590px;
}
#left2 {
  top: 375px;
  left: 105px;
}

#right  {
  top: 375px;
  left: 550px;
}
#right2  {
  top: 375px;
  right: 145px;
}
""";

def get_pins():
  pins = pinutils.scan_pin_file([], 'stm32f40x.csv', 6, 9, 10)
  return pinutils.only_from_package(pinutils.fill_gaps_in_pin_list(pins), chip["package"])

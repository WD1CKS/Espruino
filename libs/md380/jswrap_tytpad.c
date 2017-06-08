#include "jswrap_tytpad.h"
#include "jsinteractive.h"
#include "button_debounce.h"

static uint32_t
keypad_read(void)
{
	uint32_t	gpios = 0;

	/* Input pins */
	jshPinSetState(JSH_PORTD_OFFSET + 0,JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTD_OFFSET + 1, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTD_OFFSET + 14, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTD_OFFSET + 15, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 7, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 8, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 9, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 10, JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 11, JSHPINSTATE_GPIO_IN);
	jshPinSetState(JSH_PORTE_OFFSET + 12, JSHPINSTATE_GPIO_IN);
	jshPinSetState(JSH_PORTA_OFFSET + 1, JSHPINSTATE_GPIO_IN);

	/* Output pins */
	jshPinSetState(JSH_PORTA_OFFSET + 6, JSHPINSTATE_GPIO_OUT);
	jshPinSetState(JSH_PORTD_OFFSET + 2, JSHPINSTATE_GPIO_OUT);
	jshPinSetState(JSH_PORTD_OFFSET + 3, JSHPINSTATE_GPIO_OUT);

	jshPinSetValue(JSH_PORTA_OFFSET + 6, 0);
	jshPinSetValue(JSH_PORTD_OFFSET + 2, 1);
	jshPinSetValue(JSH_PORTD_OFFSET + 3, 1);
	jshDelayMicroseconds(2);
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 0) ? 0 : (1<<3);	// 3
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 1) ? 0 : (1<<4);	// 4
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 14) ? 0 : (1<<1);	// 1
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 15) ? 0 : (1<<2);	// 2
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 7) ? 0 : (1<<5);	// 5
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 8) ? 0 : (1<<6);	// 6
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 9) ? 0 : (1<<0);	// 0
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 10) ? 0 : (1<<10);	// *

	jshPinSetValue(JSH_PORTA_OFFSET + 6, 1);
	jshPinSetValue(JSH_PORTD_OFFSET + 2, 0);
	jshDelayMicroseconds(2);
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 0) ? 0 : (1<<14);	// D
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 1) ? 0 : (1<<7);	// 7
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 14) ? 0 : (1<<12);	// G
	gpios |= jshPinGetValue(JSH_PORTD_OFFSET + 15) ? 0 : (1<<13);	// U
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 7) ? 0 : (1<<8);	// 8
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 8) ? 0 : (1<<9);	// 9
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 9) ? 0 : (1<<11);	// #
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 10) ? 0 : (1<<15);	// R

	jshPinSetValue(JSH_PORTD_OFFSET + 2, 1);
	jshPinSetValue(JSH_PORTD_OFFSET + 3, 0);
	jshDelayMicroseconds(2);
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 9) ? 0 : (1<<16);	// T
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 10) ? 0 : (1<<17);	// B
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 11) ? 0 : (1<<18);	// P
	gpios |= jshPinGetValue(JSH_PORTE_OFFSET + 12) ? 0 : (1<<19);	// p
	gpios |= jshPinGetValue(JSH_PORTA_OFFSET + 1) ? 0 : (1<<20);	// X

	return gpios;
}

/*JSON{
  "type" : "class",
  "class" : "TYTKeyPad"
}
This class implements the keypad (and side buttons) of the radio.
*/

/*JSON{
  "type" : "init",
  "generate" : "jswrap_tytkeypad_init"
}*/

static Debouncer TYTPad_Debounce;

void jswrap_tytkeypad_init(void)
{
	ButtonDebounceInit(&TYTPad_Debounce, 0x00000000);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "TYTKeyPad",
  "name" : "getRaw",
  "generate" : "jswrap_tytkeypad_getraw",
  "return" : ["int32","Current raw key state"]
}
<code>Bit 0:  '0'
Bit 1:  '1'
Bit 2:  '2'
Bit 3:  '3'
Bit 4:  '4'
Bit 5:  '5'
Bit 6:  '6'
Bit 7:  '7'
Bit 8:  '8'
Bit 9:  '9'
Bit 10: '*'
Bit 11: '#'
Bit 12: 'G' (Green button)
Bit 13: 'U' (Up arrow)
Bit 14: 'D' (Down arrow)
Bit 15: 'R' (Red button)
Bit 16: 'T' (Top side button)
Bit 17: 'B' (Bottom side button)
Bit 18: 'P' (Side PTT button)
Bit 19: 'p' (External PTT button)
Bit 20: 'X' (Power switch - only available when pin A7 is set)</code>
*/

int32_t jswrap_tytkeypad_getraw(void)
{
	return (int32_t)keypad_read();
}

/*JSON{
  "type" : "staticmethod",
  "class" : "TYTKeyPad",
  "name" : "getPressed",
  "generate" : "jswrap_tytkeypad_getpressed",
  "return" : ["int32","Current debounced pressed keys"]
}
See getRaw() for bit definitions.
*/

int32_t jswrap_tytkeypad_getpressed(void)
{
	return (int32_t)ButtonCurrent(&TYTPad_Debounce, 0x001fffff);
}

/*JSON{
  "type" : "event",
  "class" : "TYTKeyPad",
  "name" : "keyPress",
  "params" : [ [ "key", "JsVar", "The key that was pressed as a single character string"] ]
}*/

/*JSON{
  "type" : "event",
  "class" : "TYTKeyPad",
  "name" : "keyRelease",
  "params" : [ [ "key", "JsVar", "The key that was released as a single character string"] ]
}*/

/*JSON{
  "type" : "staticmethod",
  "class" : "TYTKeyPad",
  "name" : "poll",
  "generate" : "jswrap_tytkeypad_poll"
}
This function should be called periodically.  A key will be pressed once it has been poll()ed eight times.
*/

const char *lookup="0123456789*#GUDRTBPpX";

void jswrap_tytkeypad_poll(void)
{
	uint32_t keys;
	JsVar *kv;
	char str[2];
	int key;
	JsVar *obj;

	obj = jsvObjectGetChild(execInfo.root, "TYTKeyPad", 0);
	str[1] = 0;

	if (obj == NULL)
		return;

	keys = keypad_read();
	ButtonProcess(&TYTPad_Debounce, keys);
	keys = ButtonPressed(&TYTPad_Debounce, 0x001fffff);
	while(keys) {
		key = ffs((int)keys);
		keys &= ~(1<<(key - 1));
		str[0] = lookup[key-1];
		kv = jsvNewFromString(str);
		jsiQueueObjectCallbacks(obj, JS_EVENT_PREFIX"keyPress", &kv, 1);
		jsvUnLock(kv);
	}

	keys = ButtonReleased(&TYTPad_Debounce, 0x001fffff);
	while(keys) {
		key = ffs((int)keys);
		keys &= ~(1<<(key - 1));
		str[0] = lookup[key-1];
		kv = jsvNewFromString(str);
		jsiQueueObjectCallbacks(obj, JS_EVENT_PREFIX"keyRelease", &kv, 1);
		jsvUnLock(kv);
	}
}

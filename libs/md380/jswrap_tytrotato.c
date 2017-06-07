#include "jswrap_tytrotato.h"
#include "jsinteractive.h"

/*JSON{
  "type" : "property",
  "name" : "TYTRotato",
  "generate" : "jswrap_tytrotato",
  "return" : ["int32", "Current Rotato position" ]
}*/

static const int8_t lookup[] = {11, 12, 10, 9, 14, 13, 15, 16, 6, 5, 7, 8, 3, 4, 2, 1};

int32_t jswrap_tytrotato(void)
{
	jshPinSetState(JSH_PORTB_OFFSET + 10,JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTB_OFFSET + 11,JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 14,JSHPINSTATE_GPIO_IN_PULLUP);
	jshPinSetState(JSH_PORTE_OFFSET + 15,JSHPINSTATE_GPIO_IN_PULLUP);

	return lookup[(jshPinGetValue(JSH_PORTB_OFFSET + 10) << 3) |
	    (jshPinGetValue(JSH_PORTE_OFFSET + 14) << 2) |
	    (jshPinGetValue(JSH_PORTE_OFFSET + 15) << 1) |
	    jshPinGetValue(JSH_PORTB_OFFSET + 11)];
}

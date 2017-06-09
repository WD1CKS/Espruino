#include "jsinteractive.h"
#include "jsvar.h"
#include "jswrap_modules.h"

/*JSON{
  "type" : "init",
  "generate" : "jswrap_md380_modules"
}*/

/*
 * Currently, only supports 64k, though extra 64k chunks could be added.
 */

extern char _md380_lib_js_start[];
extern uint32_t _md380_lib_js_size;

void jswrap_md380_modules(void)
{
	if (_md380_lib_js_size > 0 && _md380_lib_js_size <= 65535) {
		JsVar *src = jsvNewWithFlags(JSV_NATIVE_STRING);
		if (!src) {
			jsiConsolePrintf("Unable to create Native String\n");
			return;
		}
		JsVar *mod = jsvNewFromString("md380");
		if (!mod) {
			jsiConsolePrintf("Unable to create Module name\n");
			jsvUnLock(src);
			return;
		}
		src->varData.nativeStr.ptr = _md380_lib_js_start;
		src->varData.nativeStr.len = _md380_lib_js_size;
		jswrap_modules_addCached(mod, src);
		//jsvUnLock(src);
		//jsvUnLock(mod);
	}
	else
		jsiConsolePrintf("Size %d out of range\n", _md380_lib_js_size);
}

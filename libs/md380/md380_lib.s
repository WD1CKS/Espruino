.section .rodata
.global _md380_lib_js_start
.type _md380_lib_js_start, %object
.balign 1

_md380_lib_js_start:
.incbin "md380_lib.js"

.global _md380_lib_js_size
.type _md380_lib_js_size, %object
.balign 1

_md380_lib_js_size:
.int _md380_lib_js_size - _md380_lib_js_start

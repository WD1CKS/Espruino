#include "jsvar.h"

JsVar *jswrap_spiffs_config_constructor(void);
int32_t jswrap_spiffs_config_phys_size(JsVar *parent);
int32_t jswrap_spiffs_config_phys_addr(JsVar *parent);
int32_t jswrap_spiffs_config_phys_erase_sz(JsVar *parent);
int32_t jswrap_spiffs_config_log_block_size(JsVar *parent);
int32_t jswrap_spiffs_config_log_page_size(JsVar *parent);
int32_t jswrap_spiffs_config_fh_ix_offset(JsVar *parent);

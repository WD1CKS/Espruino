#include "jswrap_spiffs.h"
#include "spiffs.h"

/*JSON{
 "type" : "class",
 "class" : "SIFFS"
}
This is the SPIFFS object - it allows you to access a SPIFFS file system
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "Config"
}
The SPIFFS_Config object representing the configuration of this SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "BlockCount"
}
Number of blocks in the SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "FDCount"
}
Count of available file descriptors
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "LastError"
}
Last error that occured in SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "FreeBlocks"
}
Number of free blocks in the SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "Allocated"
}
current number of busy pages
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "Deleted"
}
current number of deleted pages
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "Cleaning"
}
flag indicating that garbage collector is cleaning
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "MaxEraseCount"
}
max erase count amongst all blocks
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "GCRuns",
  "#if" : "SPIFFS_GC_STATS"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "CacheSize",
  "#if" : "SPIFFS_CACHE"
}
cache size
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "CacheHits",
  "#if" : "SPIFFS_CACHE && SPIFFS_CACHE_STATS"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "CacheMisses",
  "#if" : "SPIFFS_CACHE && SPIFFS_CACHE_STATS"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS",
  "name" : "Mounted"
}
mounted flag
*/



/*JSON{
 "type" : "class",
 "class" : "SIFFS_Config"
}
This is the SPIFFS config object - it allows you to create a SPIFFS object
*/

/*JSON{
  "type" : "constructor",
  "class" : "SPIFFS_Config",
  "name" : "SPIFFS_Config",
  "generate" : "jswrap_spiffs_config_constructor",
  "return" : ["JsVar", "SPIFFS_Config object"],
  "return_object" : "SPIFFS_Config"
}
*/

static s32_t my_read(u32_t addr, u32_t size, u8_t *dst)
{
	return SPIFFS_OK;
}

static s32_t my_write(u32_t addr, u32_t size, u8_t *src)
{
	return SPIFFS_OK;
}

static s32_t my_erase(u32_t addr, u32_t size)
{
	return SPIFFS_OK;
}

JsVar *jswrap_spiffs_config_constructor(void)
{
	JsVar *ret = jsvNewFlatStringOfLength(sizeof(spiffs_config));
	spiffs_config *sc;

	ret = jsvNewFlatStringOfLength(sizeof(spiffs_config));
	if (!ret) {
		// Error;
		return ret;
	}
	sc = (void *)jsvGetFlatStringPointer(ret);
	sc->hal_read_f = my_read;
	sc->hal_write_f = my_write;
	sc->hal_erase_f = my_erase;
#if SPIFFS_SINGLETON == 0
	/* TODO: Pass these as args... */
	sc->phys_size = 0;
	sc->phys_addr = 0;
	sc->phys_erase_block = 0;
	sc->log_block_size = 0;
	sc->log_page_size = 0;
#endif
#if SPIFFS_FILEHDL_OFFSET
	sc->fh_ix_offset = 0;
#endif
	return ret;
}

/*JSON{
  "type" : "property",
  "class" : "SIFFS_Config",
  "name" : "PhysicalSize",
  "generate_full" : "jswrap_spiffs_config_phys_size(parent)",
  "return" : ["int32", "Physical size"]
}
physical size of the spi flash
*/
int32_t jswrap_spiffs_config_phys_size(JsVar *parent)
{
#if SPIFFS_SINGLETON
	return SPIFFS_CFG_PHYS_SZ(parent);
#else
	spiffs_config *sc;

	sc = (void *)jsvGetFlatStringPointer(parent);
	if (!sc) {
		return -1;
	}
	return sc->phys_size;
#endif
}

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Config",
  "name" : "PhysicalOffset",
  "generate_full" : "jswrap_spiffs_config_phys_addr(parent)",
  "return" : ["int32", "Physical address"]
}
physical offset in spi flash used for spiffs, must be on block boundary
*/
int32_t jswrap_spiffs_config_phys_addr(JsVar *parent)
{
#if SPIFFS_SINGLETON
	return SPIFFS_CFG_PHYS_ADDR(parent);
#else
	spiffs_config *sc;

	sc = (void *)jsvGetFlatStringPointer(parent);
	if (!sc) {
		return -1;
	}
	return sc->phys_addr;
#endif
}

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Config",
  "name" : "PhysicalEraseSize",
  "generate_full" : "jswrap_spiffs_config_phys_erase_sz(parent)",
  "return" : ["int32", "Physical size when erasing"]
}
physical size when erasing a block
*/
int32_t jswrap_spiffs_config_phys_erase_sz(JsVar *parent)
{
#if SPIFFS_SINGLETON
	return SPIFFS_CFG_PHYS_ERASE_SZ(parent);
#else
	spiffs_config *sc;

	sc = (void *)jsvGetFlatStringPointer(parent);
	if (!sc) {
		return -1;
	}
	return sc->phys_erase_sz;
#endif
}

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Config",
  "name" : "LogicalBlockSize",
  "generate_full" : "jswrap_spiffs_config_log_block_size(parent)",
  "return" : ["int32", "Logical block size"]
}
logical size of a block, must be on physical block size boundary and must never be less than a physical block
*/
int32_t jswrap_spiffs_config_log_block_size(JsVar *parent)
{
#if SPIFFS_SINGLETON
	return SPIFFS_CFG_LOG_BLOCK_SZ(parent);
#else
	spiffs_config *sc;

	sc = (void *)jsvGetFlatStringPointer(parent);
	if (!sc) {
		return -1;
	}
	return sc->log_block_sz;
#endif
}

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Config",
  "name" : "LogicalPageSize",
  "generate_full" : "jswrap_spiffs_config_log_page_size(parent)",
  "return" : ["int32", "Logical block size"]
}
logical size of a page, must be at least log_block_size / 8
*/
int32_t jswrap_spiffs_config_log_page_size(JsVar *parent)
{
#if SPIFFS_SINGLETON
	return SPIFFS_CFG_LOG_PAGE_SZ(parent);
#else
	spiffs_config *sc;

	sc = (void *)jsvGetFlatStringPointer(parent);
	if (!sc) {
		return -1;
	}
	return sc->log_page_size;
#endif
}

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Config",
  "name" : "FHOffset",
  "generate_full" : "jswrap_spiffs_config_fh_ix_offset(parent)",
  "return" : ["int32", "Logical block size"]
}
an integer offset added to each file handle
*/
int32_t jswrap_spiffs_config_fh_ix_offset(JsVar *parent)
{
#if SPIFFS_FILEHDL_OFFSET
	spiffs_config *sc;

	sc = (void *)jsvGetFlatStringPointer(parent);
	if (!sc) {
		return -1;
	}
	return sc->fh_ix_offset;
#else
	return 0;
#endif
}

/*JSON{
  "type" : "staticmethod",
  "class" : "SPIFFS_Config",
  "name" : "ProbeFS"
}
*/



/*JSON{
 "type" : "class",
 "class" : "SIFFS_Stat"
}
Stat return for SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Stat",
  "name" : "ObjectID"
}
Object ID
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Stat",
  "name" : "Size"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Stat",
  "name" : "Type"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Stat",
  "name" : "PageIndex"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_Stat",
  "name" : "Name"
}
*/

/*JSON{
 "type" : "class",
 "class" : "SIFFS_DirEnt"
}
Directory entry for SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_DirEnt",
  "name" : "ObjectID"
}
Object ID
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_DirEnt",
  "name" : "Size"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_DirEnt",
  "name" : "Type"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_DirEnt",
  "name" : "PageIndex"
}
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_DirEnt",
  "name" : "Name"
}
*/

/*JSON{
 "type" : "class",
 "class" : "SIFFS_DIR"
}
Directory for SPIFFS
*/

/*JSON{
  "type" : "property",
  "class" : "SPIFFS_DIR",
  "name" : "Entry"
}
*/

/*JSON{
 "type" : "class",
 "class" : "SIFFS_IX_MAP",
 "#if" : "SPIFFS_IX_MAP"
}
First-level index map
*/

/*JSON{
 "type" : "class",
 "class" : "SIFFS_File"
}
SPIFFS File object 
*/

/*JSON{
  "type" : "staticproperty",
  "class" : "SPIFFS",
  "name" : "Config",
  "instanceof" : "SPIFFS_Config",
  "#if" : "SPIFFS_SINGLETON"
}
This contains the static config of the singleton SPIFFS instance
*/

/*JSON{
  "type" : "constructor",
  "class" : "SPIFFS",
  "name" : "Config",
  "#if" : "!SPIFFS_SINGLETON"
}
Represents a spiffs_config instance for a SPIFFS
*/

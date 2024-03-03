/*
 * logger.h
 *
 *  Created on: 29.01.2021
 *      Author: pvvx
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_
#include "app_config.h"

#if USE_FLASH_MEMO

#define MEMO_SEC_ID		0x55AAC0DE // sector head

#define FLASH1M_ADDR_START_MEMO	0x80000
#define FLASH1M_ADDR_END_MEMO	0x100000 // 128 sectors

#define FLASH_ADDR_START_MEMO	0x40000
#define FLASH_ADDR_END_MEMO		0x74000 // 52 sectors

typedef struct _memo_blk_t {
	uint32_t time;  // time (UTC)
	int16_t temp;	// x0.01 C
	uint16_t humi;  // x0.01 %
	uint16_t vbat;  // mV
}memo_blk_t, * pmemo_blk_t;

typedef struct _memo_inf_t {
	uint32_t faddr; // current flash addr
	uint32_t cnt_cur_sec;
	uint32_t sectors;
	uint32_t start_addr;
	uint32_t end_addr;
}memo_inf_t;

typedef struct _memo_rd_t {
	memo_inf_t saved;
	uint32_t cnt;
	uint32_t cur;
}memo_rd_t;

typedef struct _memo_head_t {
	uint32_t id;  // = 0x55AAC0DE (MEMO_SEC_ID)
	uint16_t flg;  // = 0xffff - new sector, = 0 close sector
}memo_head_t;

#define MEMO1M_SEC_COUNT	((FLASH1M_ADDR_END_MEMO - FLASH1M_ADDR_START_MEMO) / FLASH_SECTOR_SIZE) // 52 or 128 sectors
#define MEMO1M_SEC_RECS		((FLASH_SECTOR_SIZE-sizeof(memo_head_t))/sizeof(memo_blk_t)) // 1 sector = 409 records
#define MEMO1M_REC_COUNT	(MEMO1M_SEC_RECS*(MEMO1M_SEC_COUNT-1))// max 51*409 = 20859 records or 127*409 = 51943 records

#define MEMO_SEC_COUNT		((FLASH_ADDR_END_MEMO - FLASH_ADDR_START_MEMO) / FLASH_SECTOR_SIZE) // 52 or 128 sectors
#define MEMO_SEC_RECS		((FLASH_SECTOR_SIZE-sizeof(memo_head_t))/sizeof(memo_blk_t)) // 1 sector = 409 records
#define MEMO_REC_COUNT		(MEMO_SEC_RECS*(MEMO_SEC_COUNT-1))// max 51*409 = 20859 records or 127*409 = 51943 records


extern memo_rd_t rd_memo;
extern memo_inf_t memo;

void memo_init(void);
void clear_memo(void);
unsigned get_memo(uint32_t bnum, pmemo_blk_t p);
void write_memo(void);

#endif // USE_FLASH_MEMO
#endif /* _LOGGER_H_ */

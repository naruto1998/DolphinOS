#include "bitmap.h"

#define PAGE_SIZE 4096
#define USED_MEMORY_SIZE 5242880 //5x1024x1024, 5MB memory, unit: bytes
#define MEM_BITMAP_BASE 0xd0000  //bitmap memory address

typedef struct _pool {
	BitMap pool_bitmap;	 
	uint32_t phy_addr_start;	 
	uint32_t pool_size;		 
}Pool;

/* 用于虚拟地址管理 */
typedef struct _virtual_addr {
/* 虚拟地址用到的位图结构，用于记录哪些虚拟地址被占用了。以页为单位。*/
   BitMap vaddr_bitmap;  //uint32_t BitMap.bm_total_len;
						 //uint8_t* BitMap.bits;
/* 管理的虚拟地址 */
   uint32_t vaddr_start;
}Virtual_Addr_BitMap;

/* 内存池标记,用于判断用哪个内存池 */
enum pool_flags {
   PF_KERNEL = 1,    // 内核内存池
   PF_USER = 2	     // 用户内存池
};

void init_memory();
static void* vaddr_get(enum pool_flags pf, uint32_t pg_cnt);
static void* palloc(Pool* m_pool);



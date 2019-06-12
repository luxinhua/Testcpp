
#define SDMMC_ReadBlocks(uStartBlk, uNumOfBlks, uDstAddr)	\
	(((void(*)(unsigned int, unsigned int, unsigned int *))(*((unsigned int *)0x02020030)))(uStartBlk, uNumOfBlks, uDstAddr))
#define CORE_START_BLK		49				// �����ǰѴ������ص������
#define CORE_BLKCNT			200				// 100K
#define CORE_DST_ADDR		0x43e00000		// 0x40000000 + 0x3e00000

void reload_core_sd_boot(void)
{
	SDMMC_ReadBlocks(CORE_START_BLK, CORE_BLKCNT, (unsigned int *)CORE_DST_ADDR);
}


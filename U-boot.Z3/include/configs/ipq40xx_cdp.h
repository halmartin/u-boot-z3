/*
 *
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _IPQ40XX_CDP_H
#define _IPQ40XX_CDP_H

#include <linux/sizes.h>

#if !defined(DO_DEPS_ONLY) || defined(DO_SOC_DEPS_ONLY)
/*
 * Beat the system! tools/scripts/make-asm-offsets uses
 * the following hard-coded define for both u-boot's
 * ASM offsets and platform specific ASM offsets :(
 */
#include <generated/generic-asm-offsets.h>
#if !defined(DO_SOC_DEPS_ONLY)
#include <generated/asm-offsets.h>
#endif
#endif /* !DO_DEPS_ONLY */

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_SYS_CACHELINE_SIZE	64
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SYS_HZ			1000

#undef CONFIG_IPQ40XX_USB
#ifdef CONFIG_IPQ40XX_USB
#define CONFIG_USB_XHCI
#define CONFIG_CMD_USB
#define CONFIG_DOS_PARTITION
#define CONFIG_USB_STORAGE
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT		2
#endif

#define CONFIG_CONS_INDEX		1

#define CONFIG_ENV_OVERWRITE
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600,\
								115200}
#define V_PROMPT			"(IPQ40xx) # "
#define CONFIG_SYS_CBSIZE		(256 * 2) /* Console I/O Buffer Size */
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
						sizeof(CONFIG_SYS_PROMPT) + 16)

#define CONFIG_SYS_SDRAM_BASE		0x80000000
#define CONFIG_SYS_SDRAM_SIZE		0x0FF00000
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_TEXT_BASE + 0x100000 - GENERATED_GBL_DATA_SIZE)
#define CONFIG_MAX_RAM_BANK_SIZE	CONFIG_SYS_SDRAM_SIZE
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + (64 << 20))
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_OF_LIBFDT		1
#define CONFIG_OF_BOARD_SETUP		1

#undef CONFIG_IPQ40XX_PCI
#ifdef CONFIG_IPQ40XX_PCI
#define CONFIG_PCI
#define CONFIG_CMD_PCI
#define CONFIG_PCI_SCAN_SHOW
#endif

#ifndef __ASSEMBLY__
#include <compiler.h>
extern loff_t board_env_offset;
extern loff_t board_env_range;
extern loff_t board_env_size;

/*
 * XXX XXX Please do not instantiate this structure. XXX XXX
 * This is just a convenience to avoid
 *      - adding #defines for every new reservation
 *      - updating the multiple associated defines like smem base,
 *        kernel start etc...
 *      - re-calculation of the defines if the order changes or
 *        some reservations are deleted
 * For new reservations just adding a member to the structure should
 * suffice.
 * Ensure that the size of this structure matches with the definition
 * of the following IPQ40xx compile time definitions
 *      PHYS_OFFSET     (linux-sources/arch/arm/mach-msm/Kconfig)
 *      zreladdr        (linux-sources/arch/arm/mach-msm/Makefile.boot)
 *      CONFIG_SYS_INIT_SP_ADDR defined above should point to the bottom.
 *      MSM_SHARED_RAM_PHYS (linux-sources/arch/arm/mach-msm/board-ipq40xx.c)
 *
 */
#if !defined(DO_DEPS_ONLY) || defined(DO_SOC_DEPS_ONLY)
typedef struct {
	uint8_t uboot[1024 * 1024 - GENERATED_GBL_DATA_SIZE];	/* ~1MB */
	uint8_t init_stack[GENERATED_GBL_DATA_SIZE];
	uint8_t sbl[1024 * 1024];				/* 1 MB */
	uint8_t cnss_debug[6 * 1024 * 1024];			/* 6 MB */
	uint8_t tz_apps[3 * 1024 * 1024];			/* 3 MB */
	uint8_t smem[512 * 1024];				/* 512 KB */
	uint8_t tz[1536 * 1024];				/* 1.5 MB */
} __attribute__ ((__packed__)) qca_mem_reserve_t;

#define QCA_MEM_RESERVE_SIZE(x)		sizeof(((qca_mem_reserve_t *)0)->x)
#define QCA_MEM_RESERVE_BASE(x)		\
	(CONFIG_SYS_TEXT_BASE + \
	 ((uint32_t)&(((qca_mem_reserve_t *)0)->x)))
#endif

#define QCA_KERNEL_START_ADDR	\
	(CONFIG_SYS_SDRAM_BASE + GENERATED_QCA_RESERVE_SIZE)

#define QCA_DRAM_KERNEL_SIZE	\
	(CONFIG_SYS_SDRAM_SIZE - GENERATED_QCA_RESERVE_SIZE)

#define QCA_BOOT_PARAMS_ADDR	(QCA_KERNEL_START_ADDR + 0x100)
#endif

#define IPQ_ROOT_FS_PART_NAME		"rootfs"

/* Environment */
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_ENV_IS_NOWHERE
#undef CONFIG_CMD_SAVEENV
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_ENV_OFFSET		board_env_offset
#define CONFIG_ENV_RANGE		board_env_size
#define CONFIG_ENV_SIZE			CONFIG_ENV_SIZE_MAX
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE_MAX + (512 << 10))
#define CONFIG_SYS_BOOTM_LEN		SZ_32M

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE + 0x1300000
#define CONFIG_SYS_MEMTEST_END		CONFIG_SYS_MEMTEST_START + 0x100
#define CONFIG_CMD_SOURCE		1
#define CONFIG_INITRD_TAG		1
#define CONFIG_SYS_DEVICE_NULLDEV

/* L1 cache line size is 64 bytes, L2 cache line size is 128 bytes
 * Cache flush and invalidation based on L1 cache, so the cache line
 * size is configured to 64 */
#define CONFIG_SYS_CACHELINE_SIZE	64

/* CMDS */

/*
 * NAND Flash Configs
 */

/* CONFIG_QPIC_NAND: QPIC NAND in BAM mode
 * CONFIG_IPQ_NAND: QPIC NAND in FIFO/block mode.
 * BAM is enabled by default.
 */
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_SYS_MAX_FLASH_BANKS 1
/*
 * Expose SPI driver as a pseudo NAND driver to make use
 * of U-Boot's MTD framework.
 */
#define CONFIG_SYS_MAX_NAND_DEVICE	(CONFIG_IPQ_MAX_NAND_DEVICE + \
					CONFIG_IPQ_MAX_SPI_DEVICE)

/*
 * SPI Flash Configs
 */

#undef CONFIG_QCA_SPI
#ifdef CONFIG_QCA_SPI
#define CONFIG_SPI_FLASH
#define CONFIG_CMD_SF
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_SPI_FLASH_MACRONIX
#define CONFIG_SPI_FLASH_GIGA
#define CONFIG_SPI_NOR_GENERIC
#define CONFIG_IPQ40XX_SPI

#define CONFIG_SF_DEFAULT_BUS 0
#define CONFIG_SF_DEFAULT_CS 0
#define CONFIG_SF_SPI_NAND_CS 1
#define CONFIG_SF_DEFAULT_MODE SPI_MODE_0
#define CONFIG_IPQ40XX_XIP	1

#define CONFIG_QUP_SPI_USE_DMA 1

#define CONFIG_SPI_NAND_GIGA 1
#define CONFIG_SPI_NAND_ATO
#define CONFIG_SPI_NAND_MACRONIX
#define CONFIG_SPI_NAND_WINBOND
#endif

/*
 * ESS Configs
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_SYS_RX_ETH_BUFFER	16
#define CONFIG_MII
#define CONFIG_CMD_MII
#define CONFIG_IPADDR	192.168.1.11
#define CONFIG_IPQ_NO_MACS	2
#endif
/*
 * CRASH DUMP ENABLE
 */

#undef CONFIG_QCA_APPSBL_DLOAD

#ifdef CONFIG_QCA_APPSBL_DLOAD
#define CONFIG_CMD_TFTPPUT
/* We will be uploading very big files */
#undef CONFIG_NET_RETRY_COUNT
#define CONFIG_NET_RETRY_COUNT 500
#endif

/*
 * Expose SPI driver as a pseudo NAND driver to make use
 * of U-Boot's MTD framework.
 */
#define CONFIG_SYS_MAX_NAND_DEVICE	(CONFIG_IPQ_MAX_NAND_DEVICE + \
					 CONFIG_IPQ_MAX_SPI_DEVICE)

#undef CONFIG_QCA_MMC

#ifdef CONFIG_QCA_MMC
#define CONFIG_CMD_MMC
#define CONFIG_MMC
#define CONFIG_EFI_PARTITION
#define CONFIG_GENERIC_MMC
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV  0
#endif


#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS

#define CONFIG_RBTREE		/* for ubi */
#define CONFIG_LZO
#define CONFIG_BOOTCOMMAND	"run meraki_boot"

#define CONFIG_REMAKE_ELF

#define CONFIG_EXTRA_ENV_SETTINGS	               \
   "initrd_high=0xffffffff\0" \
   "fdt_high=0xffffffff\0" \
   "itb_config=config@1\0" \
   "loadaddr=0x84000000\0" \
   "fuseaddr=0x88000000\0" \
   "imgaddr=0x84000028\0" \
   "bootargs=\0" \
   "part=part.safe\0" \
   "set_bootargs=setenv bootargs loader=u-boot maxcpus=1\0" \
   "set_ubi=setenv mtdids nand0=nand0; setenv mtdparts mtdparts=nand0:0x7000000@0xc00000(ubi); ubi part ubi\0" \
   "boot_part=ubi read $loadaddr $part; bootm $loadaddr#$itb_config\0" \
   "boot_signedpart=ubi read $loadaddr $part; validate $loadaddr && bootm $imgaddr#$itb_config\0" \
   "bootkernel1=setenv part part.safe; run boot_part\0" \
   "bootkernel2=setenv part part.old; run boot_part\0" \
   "meraki_boot=run set_bootargs; run set_ubi; boot_meraki_qca; run bootkernel1; run bootkernel2\0" \
   "uboot_loadaddr=0x87300000\0" \
   "chainload_uboot=if ubi check uboot.dev; then ubi read $uboot_loadaddr uboot.dev; go $uboot_loadaddr; fi\0" \
   "check_boot_diag_img=if ubi check boot_diagnostic; then ubi remove boot_diagnostic; ubi read $loadaddr diagnostic1; validate $loadaddr && bootm $imgaddr; fi\0" \
   "scrloadaddr=0x81000000\0" \
   "scrname=boot.scr\0" \
   "check_load_boot_scr=if ubifsls $scrname; then ubifsload $scrloadaddr $scrname; bootcustom $scrloadaddr; fi\0" \
   "check_boot_part_dev=if ubi check part.dev; then setenv part part.dev; run boot_part; fi\0" \
   "check_dev_unlock=ubi read $loadaddr dev.crt; validate $loadaddr\0"


#endif /* _IPQCDP_H */

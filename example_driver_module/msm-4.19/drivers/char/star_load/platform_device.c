#include <linux/device.h>  // for driver member from  platform_driver 
#include <linux/init.h>    // late_initcall 
#include <linux/module.h>  // module_init
#include <linux/platform_device.h>    // platform_driver_register
#include <linux/mod_devicetable.h>    // for of_device_id
#include <linux/of.h>      // parse_dt of function 
#include <linux/ioport.h>  // platform_device 

#include "star_core.h"
// =========================================================
// 1. platform_device resource .
/*
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	unsigned long desc;
	struct resource *parent, *sibling, *child;
}; */
struct resource	* starload_resource[] = {
	[0] = {
	.start = 99,
	.end   = 100, 
	.name  = STAR_LAOD_NAME,
	/* flags 
	#define IORESOURCE_BITS		0x000000ff  Bus-specific bits 
	
	#define IORESOURCE_TYPE_BITS	0x00001f00	 Resource type 
	#define IORESOURCE_IO		0x00000100	 PCI/ISA I/O ports 
	#define IORESOURCE_MEM		0x00000200
	#define IORESOURCE_REG		0x00000300	 Register offsets
	#define IORESOURCE_IRQ		0x00000400
	#define IORESOURCE_DMA		0x00000800
	#define IORESOURCE_BUS		0x00001000
	
	#define IORESOURCE_PREFETCH	0x00002000	 No side effects 
	#define IORESOURCE_READONLY	0x00004000
	#define IORESOURCE_CACHEABLE	0x00008000
	#define IORESOURCE_RANGELENGTH	0x00010000
	#define IORESOURCE_SHADOWABLE	0x00020000
	
	#define IORESOURCE_SIZEALIGN	0x00040000	 size indicates alignment 
	#define IORESOURCE_STARTALIGN	0x00080000	 start field is alignment 
	
	#define IORESOURCE_MEM_64	0x00100000
	#define IORESOURCE_WINDOW	0x00200000	 forwarded by bridge 
	#define IORESOURCE_MUXED	0x00400000	 Resource is software muxed 
	
	#define IORESOURCE_EXT_TYPE_BITS 0x01000000	 Resource extended types 
	#define IORESOURCE_SYSRAM	0x01000000	 System RAM (modifier) 
	
	#define IORESOURCE_EXCLUSIVE	0x08000000	 Userland may not map this resource 
	
	#define IORESOURCE_DISABLED	0x10000000
	#define IORESOURCE_UNSET	0x20000000	 No address assigned yet 
	#define IORESOURCE_AUTO		0x40000000
	#define IORESOURCE_BUSY		0x80000000	 Driver has marked this resource busy 
	*/
	.flags = IORESOURCE_MEM,
	},
	{},
}; 


// 2. 定义platform_device 
/* 
struct platform_device {
	const char	*name;
	int		id;
	bool		id_auto;
	struct device	dev;
	u32		num_resources;
	struct resource	*resource;

	const struct platform_device_id	*id_entry;
	char *driver_override; // Driver name to force a match 

	// MFD cell pointer 
	struct mfd_cell *mfd_cell;

	// arch specific additions 
	struct pdev_archdata	archdata;
};*/ 

struct platform_device star_device = {
	.name = STAR_LAOD_NAME,
	.id = -1,
	.num_resources = ARRAY_SIZE(starload_resource),
	.resource = starload_resource,
	.dev = {
		
	},
};
// =========================================================
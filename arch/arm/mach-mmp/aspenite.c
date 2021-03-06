/*
 *  linux/arch/arm/mach-mmp/aspenite.c
 *
 *  Support for the Marvell PXA168-based Aspenite and Zylonite2
 *  Development Platform.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  publishhed by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/smc91x.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/addr-map.h>
#include <mach/mfp-pxa168.h>
#include <mach/pxa168.h>
#include <mach/gpio.h>

#include "common.h"

static unsigned long common_pin_config[] __initdata = {
	/* Data Flash Interface */
	GPIO0_DFI_D15,
	GPIO1_DFI_D14,
	GPIO2_DFI_D13,
	GPIO3_DFI_D12,
	GPIO4_DFI_D11,
	GPIO5_DFI_D10,
	GPIO6_DFI_D9,
	GPIO7_DFI_D8,
	GPIO8_DFI_D7,
	GPIO9_DFI_D6,
	GPIO10_DFI_D5,
	GPIO11_DFI_D4,
	GPIO12_DFI_D3,
	GPIO13_DFI_D2,
	GPIO14_DFI_D1,
	GPIO15_DFI_D0,

	/* Static Memory Controller */
	GPIO18_SMC_nCS0,
	GPIO34_SMC_nCS1,
	GPIO23_SMC_nLUA,
	GPIO25_SMC_nLLA,
	GPIO28_SMC_RDY,
	GPIO29_SMC_SCLK,
	GPIO35_SMC_BE1,
	GPIO36_SMC_BE2,
	GPIO27_GPIO,	/* Ethernet IRQ */

	/* UART1 */
	GPIO107_UART1_RXD,
	GPIO108_UART1_TXD,
};

static struct smc91x_platdata smc91x_info = {
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
};

static struct resource smc91x_resources[] = {
	[0] = {
		.start	= SMC_CS1_PHYS_BASE + 0x300,
		.end	= SMC_CS1_PHYS_BASE + 0xfffff,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= gpio_to_irq(27),
		.end	= gpio_to_irq(27),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	}
};

static struct platform_device smc91x_device = {
	.name		= "smc91x",
	.id		= 0,
	.dev		= {
		.platform_data = &smc91x_info,
	},
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
};

static void __init common_init(void)
{
	mfp_config(ARRAY_AND_SIZE(common_pin_config));

	/* on-chip devices */
	pxa168_add_uart(1);

	/* off-chip devices */
	platform_device_register(&smc91x_device);
}

MACHINE_START(ASPENITE, "PXA168-based Aspenite Development Platform")
	.phys_io        = APB_PHYS_BASE,
	.boot_params    = 0x00000100,
	.io_pg_offst    = (APB_VIRT_BASE >> 18) & 0xfffc,
	.map_io		= pxa_map_io,
	.init_irq       = pxa168_init_irq,
	.timer          = &pxa168_timer,
	.init_machine   = common_init,
MACHINE_END

MACHINE_START(ZYLONITE2, "PXA168-based Zylonite2 Development Platform")
	.phys_io        = APB_PHYS_BASE,
	.boot_params    = 0x00000100,
	.io_pg_offst    = (APB_VIRT_BASE >> 18) & 0xfffc,
	.map_io		= pxa_map_io,
	.init_irq       = pxa168_init_irq,
	.timer          = &pxa168_timer,
	.init_machine   = common_init,
MACHINE_END

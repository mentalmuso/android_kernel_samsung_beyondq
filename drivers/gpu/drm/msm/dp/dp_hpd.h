/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _DP_HPD_H_
#define _DP_HPD_H_

#include <linux/usb/usbpd.h>
#include <linux/types.h>
#include <linux/device.h>
#include "dp_parser.h"

/**
 * enum dp_hpd_type - dp hpd type
 * @DP_HPD_USBPD:   USB type-c based HPD
 * @DP_HPD_GPIO:    GPIO based HPD
 * @DP_HPD_BUILTIN: Controller built-in HPD
 */

enum dp_hpd_type {
	DP_HPD_USBPD,
	DP_HPD_GPIO,
	DP_HPD_BUILTIN,
};

/**
 * struct dp_hpd_cb - callback functions provided by the client
 *
 * @configure: called when dp connection is ready.
 * @disconnect: notify the cable disconnect event.
 * @attention: notify any attention message event.
 */
struct dp_hpd_cb {
#ifndef CONFIG_SEC_DISPLAYPORT
	int (*configure)(struct device *dev);
	int (*disconnect)(struct device *dev);
	int (*attention)(struct device *dev);
#else
	int (*configure)(void);
	int (*disconnect)(void);
	int (*attention)(void);
#endif
};

/**
 * struct dp_hpd - DisplayPort HPD status
 *
 * @type: type of HPD
 * @orientation: plug orientation configuration, USBPD type only.
 * @hpd_high: Hot Plug Detect signal is high.
 * @hpd_irq: Change in the status since last message
 * @alt_mode_cfg_done: bool to specify alt mode status
 * @switch_needed: bool to specify if switch is needed
 * @multi_func: multi-function preferred, USBPD type only
 * @isr: event interrupt, BUILTIN type only
 * @simulate_connect: simulate disconnect or connect for debug mode
 * @simulate_attention: simulate attention messages for debug mode
 */
struct dp_hpd {
	enum dp_hpd_type type;
	enum plug_orientation orientation;
	bool hpd_high;
	bool hpd_irq;
	bool alt_mode_cfg_done;
	bool multi_func;

	void (*isr)(struct dp_hpd *dp_hpd, int event);
	int (*simulate_connect)(struct dp_hpd *dp_hpd, bool hpd);
	int (*simulate_attention)(struct dp_hpd *dp_hpd, int vdo);
};

/**
 * dp_hpd_get() - configure and get the DisplayPlot HPD module data
 *
 * @dev: device instance of the caller
 * @parser: DP parser
 * @cb: callback function for HPD response
 * return: pointer to allocated hpd module data
 *
 * This function sets up the hpd module
 */
struct dp_hpd *dp_hpd_get(struct device *dev,
	struct dp_parser *parser, struct dp_hpd_cb *cb);

/**
 * dp_hpd_put()
 *
 * Cleans up dp_hpd instance
 *
 * @dp_hpd: instance of dp_hpd
 */
void dp_hpd_put(struct dp_hpd *dp_hpd);

#endif /* _DP_HPD_H_ */

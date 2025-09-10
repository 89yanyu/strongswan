/*
 * Copyright (C) 2023 strongSwan Project
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup latunnel latunnel
 * @ingroup cplugins
 *
 * @defgroup latunnel_plugin latunnel_plugin
 * @{ @ingroup latunnel
 */

#ifndef LATUNNEL_PLUGIN_H_
#define LATUNNEL_PLUGIN_H_

#include <plugins/plugin.h>

typedef struct latunnel_plugin_t latunnel_plugin_t;

/**
 * Plugin that logs CHILD_SA events with specific tunnel information.
 */
struct latunnel_plugin_t {

	/**
	 * implements plugin interface
	 */
	plugin_t plugin;
};

/**
 * Create a latunnel_plugin instance.
 */
plugin_t *latunnel_plugin_create();

#endif /** LATUNNEL_PLUGIN_H_ @}*/

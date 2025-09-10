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
 * @defgroup latunnel_listener latunnel_listener
 * @{ @ingroup latunnel
 */

#ifndef LATUNNEL_LISTENER_H_
#define LATUNNEL_LISTENER_H_

#include <bus/bus.h>

typedef struct latunnel_listener_t latunnel_listener_t;

/**
 * Listener which logs CHILD_SA up/down/rekey events with specific information.
 */
struct latunnel_listener_t {

	/**
	 * Implements listener_t.
	 */
	listener_t listener;

	/**
	 * Destroy a latunnel_listener_t.
	 */
	void (*destroy)(latunnel_listener_t *this);
};

/**
 * Create a latunnel_listener instance.
 */
latunnel_listener_t *latunnel_listener_create();

#endif /** LATUNNEL_LISTENER_H_ @}*/
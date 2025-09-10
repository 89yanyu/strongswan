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

#include <stdio.h>
#include <unistd.h>

#include "latunnel_listener.h"

#include <daemon.h>
#include <config/child_cfg.h>

typedef struct private_latunnel_listener_t private_latunnel_listener_t;

/**
 * Private data of a latunnel_listener_t object.
 */
struct private_latunnel_listener_t {

	/**
	 * Public latunnel_listener_t interface.
	 */
	latunnel_listener_t public;
};

/**
 * Log CHILD_SA information
 */
static void log_child_sa_info(private_latunnel_listener_t *this, 
							  ike_sa_t *ike_sa, child_sa_t *child_sa, 
							  char *event_type, char *sa_type)
{
	host_t *host;
	uint32_t if_id_in, if_id_out;
	enumerator_t *enumerator;
	bool first = TRUE;
	char my_sourceip[64] = "none";
	char peer_sourceip[64] = "none";

	/* 获取 IF_ID */
	if_id_in = child_sa->get_if_id(child_sa, TRUE);
	if_id_out = child_sa->get_if_id(child_sa, FALSE);

	/* 获取本地虚拟IP (PLUTO_MY_SOURCEIP) */
	enumerator = ike_sa->create_virtual_ip_enumerator(ike_sa, TRUE);
	while (enumerator->enumerate(enumerator, &host))
	{
		if (first)
		{
			/* 使用第一个虚拟IP作为PLUTO_MY_SOURCEIP */
			snprintf(my_sourceip, sizeof(my_sourceip), "%H", host);
			first = FALSE;
			break;
		}
	}
	enumerator->destroy(enumerator);

	/* 获取对端虚拟IP (PLUTO_PEER_SOURCEIP) */
	first = TRUE;
	enumerator = ike_sa->create_virtual_ip_enumerator(ike_sa, FALSE);
	while (enumerator->enumerate(enumerator, &host))
	{
		if (first)
		{
			/* 使用第一个虚拟IP作为PLUTO_PEER_SOURCEIP */
			snprintf(peer_sourceip, sizeof(peer_sourceip), "%H", host);
			first = FALSE;
			break;
		}
	}
	enumerator->destroy(enumerator);

	/* 打印日志 */
	DBG1(DBG_CHD, "latunnel_listener: CHILD_SA %s event (%s)", event_type, sa_type);
	DBG1(DBG_CHD, "  PLUTO_IF_ID_IN=%u", if_id_in);
	DBG1(DBG_CHD, "  PLUTO_IF_ID_OUT=%u", if_id_out);
	DBG1(DBG_CHD, "  PLUTO_MY_SOURCEIP=%s", my_sourceip);
	DBG1(DBG_CHD, "  PLUTO_PEER_SOURCEIP=%s", peer_sourceip);
	DBG1(DBG_CHD, "  PLUTO_UNIQUEID=%u", ike_sa->get_unique_id(ike_sa));
}

METHOD(listener_t, child_updown, bool,
	private_latunnel_listener_t *this, ike_sa_t *ike_sa, child_sa_t *child_sa,
	bool up)
{
	log_child_sa_info(this, ike_sa, child_sa, up ? "UP" : "DOWN", "current");
	return TRUE;
}

METHOD(listener_t, child_rekey, bool,
	private_latunnel_listener_t *this, ike_sa_t *ike_sa,
	child_sa_t *old, child_sa_t *new)
{
	// 对于rekey事件，需要打印新老两个CHILD_SA的信息
	log_child_sa_info(this, ike_sa, old, "REKEY", "old");
	log_child_sa_info(this, ike_sa, new, "REKEY", "new");
	return TRUE;
}

METHOD(latunnel_listener_t, destroy, void,
	private_latunnel_listener_t *this)
{
	free(this);
}

/**
 * See header
 */
latunnel_listener_t *latunnel_listener_create()
{
	private_latunnel_listener_t *this;

	INIT(this,
		.public = {
			.listener = {
				.child_updown = _child_updown,
				.child_rekey = _child_rekey,
			},
			.destroy = _destroy,
		},
	);

	return &this->public;
}
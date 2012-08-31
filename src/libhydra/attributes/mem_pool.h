/*
 * Copyright (C) 2010 Tobias Brunner
 * Hochschule fuer Technik Rapperswil
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
 * @defgroup mem_pool mem_pool
 * @{ @ingroup attributes
 */

#ifndef MEM_POOL_H
#define MEM_POOL_H

typedef struct mem_pool_t mem_pool_t;

#include <utils/host.h>
#include <utils/identification.h>

/**
 * An in-memory IP address pool.
 */
struct mem_pool_t {

	/**
	 * Get the name of this pool.
	 *
	 * @return			the name of this pool
	 */
	const char* (*get_name)(mem_pool_t *this);

	/**
	 * Get the base (first) address of this pool.
	 *
	 * @return			base address, internal host
	 */
	host_t* (*get_base)(mem_pool_t *this);

	/**
	 * Get the size (i.e. number of addresses) of this pool.
	 *
	 * @return			the size of this pool
	 */
	u_int (*get_size)(mem_pool_t *this);

	/**
	 * Get the number of online leases.
	 *
	 * @return			the number of offline leases
	 */
	u_int (*get_online)(mem_pool_t *this);

	/**
	 * Get the number of offline leases.
	 *
	 * @return			the number of online leases
	 */
	u_int (*get_offline)(mem_pool_t *this);

	/**
	 * Acquire an address for the given id from this pool.
	 *
	 * @param id		the id to acquire an address for
	 * @param requested	acquire this address, if possible
	 * @return			the acquired address
	 */
	host_t* (*acquire_address)(mem_pool_t *this, identification_t *id,
							   host_t *requested);

	/**
	 * Release a previously acquired address.
	 *
	 * @param address	the address to release
	 * @param id		the id the address was assigned to
	 * @return			TRUE, if the lease was found
	 */
	bool (*release_address)(mem_pool_t *this, host_t *address,
							identification_t *id);

	/**
	 * Create an enumerator over the leases of this pool.
	 *
	 * Enumerator enumerates over
	 * identification_t *id, host_t *address, bool online
	 *
	 * @return			enumerator
	 */
	enumerator_t* (*create_lease_enumerator)(mem_pool_t *this);

	/**
	 * Destroy a mem_pool_t instance.
	 */
	void (*destroy)(mem_pool_t *this);
};

/**
 * Create an in-memory IP address pool.
 *
 * An empty pool just returns the requested address.
 *
 * @param name		name of this pool
 * @param base		base address of this pool, NULL to create an empty pool
 * @param bits		net mask
 */
mem_pool_t *mem_pool_create(char *name, host_t *base, int bits);

#endif /** MEM_POOL_H_ @} */


/*****************************************************************************\
 * src/common/io_hdr.h - IO connection header functions
 * $Id$
 *****************************************************************************
 *  Copyright (C) 2002 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Mark A. Grondona <mgrondona@llnl.gov>.
 *  UCRL-CODE-2002-040.
 *  
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.llnl.gov/linux/slurm/>.
 *  
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *  
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
\*****************************************************************************/

#ifndef _HAVE_IO_HDR_H
#define _HAVE_IO_HDR_H


#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if HAVE_STDINT_H
#  include <stdint.h>
#endif
#if HAVE_INTTYPES_H
#  include <inttypes.h>
#endif

#include "src/common/macros.h"   /* Containes SLURM_CRED_SIGLEN */
#include "src/common/pack.h"
#include "src/common/cbuf.h"

#define SLURM_IO_STDIN 0
#define SLURM_IO_STDOUT 1
#define SLURM_IO_STDERR 2
#define SLURM_IO_ALLTASKS ((uint16_t)-1)

struct slurm_io_init_msg {
	uint16_t      version;
	unsigned char cred_signature[SLURM_CRED_SIGLEN]; 
	uint32_t      nodeid;
};


typedef struct slurm_io_header {
	uint16_t      type;
	uint16_t      gtaskid;
	uint16_t      ltaskid;
	uint32_t      length;
} io_hdr_t;

/*
 * Return the packed size of an IO header in bytes;
 */
int io_hdr_packed_size();

void io_hdr_pack(io_hdr_t *hdr, Buf buffer);

int io_hdr_unpack(io_hdr_t *hdr, Buf buffer);

/*
 * Validate io init msg
 *
 * Returns 0 on success, -1 if any of the following is not true
 */
int io_init_msg_validate(struct slurm_io_init_msg *msg, const char *sig);

int io_init_msg_write_to_fd(int fd, struct slurm_io_init_msg *msg);

int io_init_msg_read_from_fd(int fd, struct slurm_io_init_msg *msg);

#endif /* !_HAVE_IO_HDR_H */

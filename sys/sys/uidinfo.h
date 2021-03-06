/*	$NetBSD: uidinfo.h,v 1.4 2019/03/01 03:03:19 christos Exp $	*/

/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _SYS_UIDINFO_H_
#define _SYS_UIDINFO_H_

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/mutex.h>

/*
 * Structure associated with user caching.
 */
struct uidinfo {
	SLIST_ENTRY(uidinfo) ui_hash;
	uid_t	ui_uid;
	u_long	ui_proccnt;	/* Number of processes */
	u_long	ui_lwpcnt;	/* Number of lwps */
	u_long	ui_lockcnt;	/* Number of locks */
	u_long	ui_semcnt;	/* Number of semaphores */
	u_long	ui_sbsize;	/* Socket buffer size */
};

int	chgproccnt(uid_t, int);
int	chglwpcnt(uid_t, int);
int	chgsemcnt(uid_t, int);
int	chgsbsize(struct uidinfo *, u_long *, u_long, rlim_t);
struct uidinfo *uid_find(uid_t);
void	uid_init(void);

#endif /* _SYS_UIDINFO_H_ */

/* $NetBSD: meson_clk_gate.c,v 1.2 2019/02/25 19:30:17 jmcneill Exp $ */

/*-
 * Copyright (c) 2017-2019 Jared McNeill <jmcneill@invisible.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: meson_clk_gate.c,v 1.2 2019/02/25 19:30:17 jmcneill Exp $");

#include <sys/param.h>
#include <sys/bus.h>

#include <dev/clk/clk_backend.h>

#include <arm/amlogic/meson_clk.h>

int
meson_clk_gate_enable(struct meson_clk_softc *sc, struct meson_clk_clk *clk,
    int enable)
{
	struct meson_clk_gate *gate = &clk->u.gate;
	uint32_t val;
	int set;

	KASSERT(clk->type == MESON_CLK_GATE);

	set = (gate->flags & MESON_CLK_GATE_SET_TO_DISABLE) ? !enable : enable;

	CLK_LOCK(sc);

	val = CLK_READ(sc, gate->reg);
	if (set)
		val |= gate->mask;
	else
		val &= ~gate->mask;
	CLK_WRITE(sc, gate->reg, val);

	CLK_UNLOCK(sc);

	return 0;
}

const char *
meson_clk_gate_get_parent(struct meson_clk_softc *sc, struct meson_clk_clk *clk)
{
	struct meson_clk_gate *gate = &clk->u.gate;

	KASSERT(clk->type == MESON_CLK_GATE);

	return gate->parent;
}

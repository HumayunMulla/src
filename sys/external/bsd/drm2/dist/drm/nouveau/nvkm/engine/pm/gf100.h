/*	$NetBSD: gf100.h,v 1.2 2018/08/27 04:58:32 riastradh Exp $	*/

#ifndef __NVKM_PM_NVC0_H__
#define __NVKM_PM_NVC0_H__
#include "priv.h"

struct gf100_pm_func {
	const struct nvkm_specdom *doms_hub;
	const struct nvkm_specdom *doms_gpc;
	const struct nvkm_specdom *doms_part;
};

int gf100_pm_new_(const struct gf100_pm_func *, struct nvkm_device *,
		  int index, struct nvkm_pm **);

extern const struct nvkm_funcdom gf100_perfctr_func;
extern const struct nvkm_specdom gf100_pm_gpc[];

extern const struct nvkm_specsrc gf100_pbfb_sources[];
extern const struct nvkm_specsrc gf100_pmfb_sources[];
#endif

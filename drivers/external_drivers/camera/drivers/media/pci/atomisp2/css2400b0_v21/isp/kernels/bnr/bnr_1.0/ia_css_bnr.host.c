/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include "ia_css_types.h"
#include "sh_css_defs.h"
#include "ia_css_debug.h"
#include "sh_css_frac.h"

#include "ia_css_bnr.host.h"

void
ia_css_bnr_encode(
	struct sh_css_isp_bnr_params *to,
	const struct ia_css_nr_config *from,
	unsigned size)
{
	(void)size;
	/* BNR (Bayer Noise Reduction) */
	to->threshold_low =
	    uDIGIT_FITTING(from->direction, 16, SH_CSS_BAYER_BITS);
	to->threshold_width_log2 = uFRACTION_BITS_FITTING(8);
	to->threshold_width =
	    1 << to->threshold_width_log2;
	to->gain_all =
	    uDIGIT_FITTING(from->bnr_gain, 16, SH_CSS_BNR_GAIN_SHIFT);
	to->gain_dir =
	    uDIGIT_FITTING(from->bnr_gain, 16, SH_CSS_BNR_GAIN_SHIFT);
	to->clip = uDIGIT_FITTING((unsigned)16384, 16, SH_CSS_BAYER_BITS);
}

void
ia_css_bnr_dump(
	const struct sh_css_isp_bnr_params *bnr,
	unsigned level)
{
	if (!bnr) return;
	ia_css_debug_dtrace(level, "Bayer Noise Reduction:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"bnr_gain_all", bnr->gain_all);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"bnr_gain_dir", bnr->gain_dir);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"bnr_threshold_low",
			bnr->threshold_low);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"bnr_threshold_width_log2",
			bnr->threshold_width_log2);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"bnr_threshold_width",
			bnr->threshold_width);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			"bnr_clip", bnr->clip);
}

/* -*- c++ -*- */
/*
 * Copyright 2012-2021 Clayton Smith.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSD_DSD_BLOCK_FF_H
#define INCLUDED_DSD_DSD_BLOCK_FF_H

#include <gnuradio/sync_decimator.h>
#include <dsd/api.h>

namespace gr {
namespace dsd {

enum dsd_frame_mode {
  dsd_FRAME_AUTO_DETECT,
  dsd_FRAME_P25_PHASE_1,
  dsd_FRAME_DSTAR,
  dsd_FRAME_NXDN48_IDAS,
  dsd_FRAME_NXDN96,
  dsd_FRAME_PROVOICE,
  dsd_FRAME_DMR_MOTOTRBO,
  dsd_FRAME_X2_TDMA
};

enum dsd_modulation_optimizations {
  dsd_MOD_AUTO_SELECT,
  dsd_MOD_C4FM,
  dsd_MOD_GFSK,
  dsd_MOD_QPSK
};

/*!
 * \brief <+description of block+>
 * \ingroup dsd
 *
 */
class DSD_API dsd_block_ff : virtual public gr::sync_decimator
{
public:
    typedef std::shared_ptr<dsd_block_ff> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of dsd::dsd_block_ff.
     *
     * To avoid accidental use of raw pointers, dsd::dsd_block_ff's
     * constructor is in a private implementation
     * class. dsd::dsd_block_ff::make is the public interface for
     * creating new instances.
     */
    static sptr make(dsd_frame_mode frame,
                     dsd_modulation_optimizations mod,
                     int uvquality,
                     bool errorbars,
                     int verbosity);
};

} // namespace dsd
} // namespace gr

#endif /* INCLUDED_DSD_DSD_BLOCK_FF_H */

/* -*- c++ -*- */
/*
 * Copyright 2012-2016 Clayton Smith
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_DSD_DSD_BLOCK_FF_H
#define INCLUDED_DSD_DSD_BLOCK_FF_H

#include <dsd/api.h>
#include <gnuradio/sync_decimator.h>

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
      typedef boost::shared_ptr<dsd_block_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dsd::dsd_block_ff.
       *
       * To avoid accidental use of raw pointers, dsd::dsd_block_ff's
       * constructor is in a private implementation
       * class. dsd::dsd_block_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make(dsd_frame_mode frame, dsd_modulation_optimizations mod, int uvquality, bool errorbars, int verbosity);
    };

  } // namespace dsd
} // namespace gr

#endif /* INCLUDED_DSD_DSD_BLOCK_FF_H */

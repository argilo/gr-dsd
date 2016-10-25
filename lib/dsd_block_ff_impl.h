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

#ifndef INCLUDED_DSD_DSD_BLOCK_FF_IMPL_H
#define INCLUDED_DSD_DSD_BLOCK_FF_IMPL_H

#include <dsd/dsd_block_ff.h>

extern "C"
{
  #include <dsd.h>
}

namespace gr {
  namespace dsd {

    typedef struct
    {
      dsd_opts opts;
      dsd_state state;
    } dsd_params;

    class dsd_block_ff_impl : public dsd_block_ff
    {
     private:
      dsd_params params;

     public:
      dsd_block_ff_impl(dsd_frame_mode frame, dsd_modulation_optimizations mod, int uvquality, bool errorbars, int verbosity);
      ~dsd_block_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace dsd
} // namespace gr

#endif /* INCLUDED_DSD_DSD_BLOCK_FF_IMPL_H */

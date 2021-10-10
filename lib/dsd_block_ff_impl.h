/* -*- c++ -*- */
/*
 * Copyright 2012-2021 Clayton Smith.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
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
    dsd_block_ff_impl(dsd_frame_mode frame,
                      dsd_modulation_optimizations mod,
                      int uvquality,
                      bool errorbars,
                      int verbosity);
    ~dsd_block_ff_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dsd
} // namespace gr

#endif /* INCLUDED_DSD_DSD_BLOCK_FF_IMPL_H */

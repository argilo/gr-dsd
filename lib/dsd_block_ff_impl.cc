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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "dsd_block_ff_impl.h"

namespace gr {
  namespace dsd {

    void* run_dsd (void *arg)
    {
      dsd_params *params = (dsd_params *) arg;
      liveScanner (&params->opts, &params->state);
      return NULL;
    }

    dsd_block_ff::sptr
    dsd_block_ff::make(dsd_frame_mode frame, dsd_modulation_optimizations mod, int uvquality, bool errorbars, int verbosity)
    {
      return gnuradio::get_initial_sptr
        (new dsd_block_ff_impl(frame, mod, uvquality, errorbars, verbosity));
    }

    /*
     * The private constructor
     */
    dsd_block_ff_impl::dsd_block_ff_impl(dsd_frame_mode frame, dsd_modulation_optimizations mod, int uvquality, bool errorbars, int verbosity)
      : gr::sync_decimator("dsd_block_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)), 6)
    {
      initOpts (&params.opts);
      initState (&params.state);

      params.opts.split = 1;
      params.opts.playoffset = 0;
      params.opts.delay = 0;
      params.opts.audio_in_type = 0;
      params.opts.audio_out_type = 0;

      if (frame == dsd_FRAME_AUTO_DETECT)
      {
        params.opts.frame_dstar = 1;
        params.opts.frame_x2tdma = 1;
        params.opts.frame_p25p1 = 1;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 1;
        params.opts.frame_dmr = 1;
        params.opts.frame_provoice = 0;
      }
      else if (frame == dsd_FRAME_DSTAR)
      {
        params.opts.frame_dstar = 1;
        params.opts.frame_x2tdma = 0;
        params.opts.frame_p25p1 = 0;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 0;
        params.opts.frame_dmr = 0;
        params.opts.frame_provoice = 0;
        printf ("Decoding only D-STAR frames.\n");
      }
      else if (frame == dsd_FRAME_X2_TDMA)
      {
        params.opts.frame_dstar = 0;
        params.opts.frame_x2tdma = 1;
        params.opts.frame_p25p1 = 0;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 0;
        params.opts.frame_dmr = 0;
        params.opts.frame_provoice = 0;
        printf ("Decoding only X2-TDMA frames.\n");
      }
      else if (frame == dsd_FRAME_PROVOICE)
      {
        params.opts.frame_dstar = 0;
        params.opts.frame_x2tdma = 0;
        params.opts.frame_p25p1 = 0;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 0;
        params.opts.frame_dmr = 0;
        params.opts.frame_provoice = 1;
        params.state.samplesPerSymbol = 5;
        params.state.symbolCenter = 2;
        params.opts.mod_c4fm = 0;
        params.opts.mod_qpsk = 0;
        params.opts.mod_gfsk = 1;
        params.state.rf_mod = 2;
        printf ("Setting symbol rate to 9600 / second\n");
        printf ("Enabling only GFSK modulation optimizations.\n");
        printf ("Decoding only ProVoice frames.\n");
      }
      else if (frame == dsd_FRAME_P25_PHASE_1)
      {
        params.opts.frame_dstar = 0;
        params.opts.frame_x2tdma = 0;
        params.opts.frame_p25p1 = 1;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 0;
        params.opts.frame_dmr = 0;
        params.opts.frame_provoice = 0;
        printf ("Decoding only P25 Phase 1 frames.\n");
      }
      else if (frame == dsd_FRAME_NXDN48_IDAS)
      {
        params.opts.frame_dstar = 0;
        params.opts.frame_x2tdma = 0;
        params.opts.frame_p25p1 = 0;
        params.opts.frame_nxdn48 = 1;
        params.opts.frame_nxdn96 = 0;
        params.opts.frame_dmr = 0;
        params.opts.frame_provoice = 0;
        params.state.samplesPerSymbol = 20;
        params.state.symbolCenter = 10;
        params.opts.mod_c4fm = 0;
        params.opts.mod_qpsk = 0;
        params.opts.mod_gfsk = 1;
        params.state.rf_mod = 2;
        printf ("Setting symbol rate to 2400 / second\n");
        printf ("Enabling only GFSK modulation optimizations.\n");
        printf ("Decoding only NXDN 4800 baud frames.\n");
      }
      else if (frame == dsd_FRAME_NXDN96)
      {
        params.opts.frame_dstar = 0;
        params.opts.frame_x2tdma = 0;
        params.opts.frame_p25p1 = 0;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 1;
        params.opts.frame_dmr = 0;
        params.opts.frame_provoice = 0;
        params.opts.mod_c4fm = 0;
        params.opts.mod_qpsk = 0;
        params.opts.mod_gfsk = 1;
        params.state.rf_mod = 2;
        printf ("Enabling only GFSK modulation optimizations.\n");
        printf ("Decoding only NXDN 9600 baud frames.\n");
      }
      else if (frame == dsd_FRAME_DMR_MOTOTRBO)
      {
        params.opts.frame_dstar = 0;
        params.opts.frame_x2tdma = 0;
        params.opts.frame_p25p1 = 0;
        params.opts.frame_nxdn48 = 0;
        params.opts.frame_nxdn96 = 0;
        params.opts.frame_dmr = 1;
        params.opts.frame_provoice = 0;
        printf ("Decoding only DMR/MOTOTRBO frames.\n");
      }

      params.opts.uvquality = uvquality;

      params.opts.verbose = verbosity;
      params.opts.errorbars = errorbars;

      if (mod == dsd_MOD_AUTO_SELECT)
      {
        params.opts.mod_c4fm = 1;
        params.opts.mod_qpsk = 1;
        params.opts.mod_gfsk = 1;
        params.state.rf_mod = 0;
      }
      else if (mod == dsd_MOD_C4FM)
      {
        params.opts.mod_c4fm = 1;
        params.opts.mod_qpsk = 0;
        params.opts.mod_gfsk = 0;
        params.state.rf_mod = 0;
        printf ("Enabling only C4FM modulation optimizations.\n");
      }
      else if (mod == dsd_MOD_GFSK)
      {
        params.opts.mod_c4fm = 0;
        params.opts.mod_qpsk = 0;
        params.opts.mod_gfsk = 1;
        params.state.rf_mod = 2;
        printf ("Enabling only GFSK modulation optimizations.\n");
      }
      else if (mod == dsd_MOD_QPSK)
      {
        params.opts.mod_c4fm = 0;
        params.opts.mod_qpsk = 1;
        params.opts.mod_gfsk = 0;
        params.state.rf_mod = 1;
        printf ("Enabling only QPSK modulation optimizations.\n");
      }

      // Initialize the mutexes
      if(pthread_mutex_init(&params.state.input_mutex, NULL))
      {
        printf("Unable to initialize input mutex\n");
      }
      if(pthread_mutex_init(&params.state.output_mutex, NULL))
      {
        printf("Unable to initialize output mutex\n");
      }

      // Initialize the conditions
      if(pthread_cond_init(&params.state.input_ready, NULL))
      {
        printf("Unable to initialize input condition\n");
      }
      if(pthread_cond_init(&params.state.output_ready, NULL))
      {
        printf("Unable to initialize output condition\n");
      }

      // Lock output mutex
      if (pthread_mutex_lock(&params.state.output_mutex))
      {
        printf("Unable to lock mutex\n");
      }

      params.state.input_length = 0;

      params.state.output_buffer = (short *) malloc(2 * 80000); // TODO: Make this variable size.
      params.state.output_offset = 0;
      if (params.state.output_buffer == NULL)
      {
        printf("Unable to allocate output buffer.\n");
      }

      // Spawn DSD in its own thread
      pthread_t dsd_thread;
      if(pthread_create(&dsd_thread, NULL, &run_dsd, &params))
      {
        printf("Unable to spawn thread\n");
      }
    }

    /*
     * Our virtual destructor.
     */
    dsd_block_ff_impl::~dsd_block_ff_impl()
    {
      // Unlock output mutex
      if (pthread_mutex_unlock(&params.state.output_mutex))
      {
        printf("Unable to unlock mutex\n");
      }
      free(params.state.output_buffer);
    }

    int
    dsd_block_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      int i;
      int send_to_dsd = 0;
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      for (i = 0; i < noutput_items * 6; i++) {
        if (in[i] != 0) {
          send_to_dsd = 1;
          break;
        }
      }
      if (!send_to_dsd) {
        // All samples are zero, so skip DSD processing.
        for (i = 0; i < noutput_items; i++) {
          out[i] = 0;
        }
        return noutput_items;
      }

      params.state.output_samples = out;
      params.state.output_num_samples = 0;
      params.state.output_length = noutput_items;
      params.state.output_finished = 0;

      if (pthread_mutex_lock(&params.state.input_mutex))
      {
        printf("Unable to lock mutex\n");
      }

      params.state.input_samples = in;
      params.state.input_length = noutput_items * 6;
      params.state.input_offset = 0;

      if (pthread_cond_signal(&params.state.input_ready))
      {
        printf("Unable to signal\n");
      }

      if (pthread_mutex_unlock(&params.state.input_mutex))
      {
        printf("Unable to unlock mutex\n");
      }

      while (params.state.output_finished == 0)
      {
        if (pthread_cond_wait(&params.state.output_ready, &params.state.output_mutex))
        {
          printf("general_work -> Error waiting for condition\n");
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dsd */
} /* namespace gr */

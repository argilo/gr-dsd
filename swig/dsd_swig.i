/* -*- c++ -*- */

#define DSD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dsd_swig_doc.i"

%{
#include "dsd/dsd_block_ff.h"
%}


%include "dsd/dsd_block_ff.h"
GR_SWIG_BLOCK_MAGIC2(dsd, dsd_block_ff);

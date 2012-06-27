/* -*- c++ -*- */

#define DSD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dsd_swig_doc.i"


%{
#include "dsd_block_ff.h"
%}

GR_SWIG_BLOCK_MAGIC(dsd,block_ff);
%include "dsd_block_ff.h"

# Copyright 2012 Clayton Smith
#
# This file is part of gr-dsd
#
# gr-dsd is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# gr-dsd is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with gr-dsd; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -idirafter /usr/local/include/gnuradio")
add_library(dsd dmr_data.c dmr_voice.c dsd_audio.c dsd_dibit.c dsd_file.c dsd_frame.c dsd_frame_sync.c dsd_main.c dsd_mbe.c dsd_serial.c dsd_symbol.c dsd_upsample.c dstar.c nxdn96.c nxdn_data.c nxdn_voice.c p25_lcw.c p25p1_hdu.c p25p1_ldu1.c p25p1_ldu2.c p25p1_tdulc.c provoice.c x2tdma_data.c x2tdma_voice.c)
target_link_libraries(dsd mbe)
add_definitions(-fPIC)

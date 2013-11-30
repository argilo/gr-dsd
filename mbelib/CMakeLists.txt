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
add_library(mbe ambe3600x2250.c ecc.c imbe7100x4400.c imbe7200x4400.c mbelib.c)
add_definitions(-fPIC)

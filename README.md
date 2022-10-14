gr-dsd
======

Author: Clayton Smith  
Email: <argilo@gmail.com>

The goal of this project is to package Digital Speech Decoder (DSD) as
a GNU Radio block, so that it can be easily used with software radio
peripherals such as the Ettus Research USRP or RTL2832U-based USB TV
tuners.

Dependencies:

  * GNU Radio 3.7, 3.8, 3.9, or 3.10
  * libsndfile (libsndfile1-dev package in Ubuntu)
  * BOOST C++ source libraries (libboost-all-dev in Ubuntu)
  * libcppunit-dev
  * libitpp-dev
  * liblog4cpp5-dev
  * swig

Build instructions:

    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    sudo ldconfig

If your GNU Radio is installed in `/usr` (rather than `/usr/local`), then
replace the first line above with:

    cmake -DCMAKE_INSTALL_PREFIX=/usr ..

After running the above commands, "DSD Block" should appear under the
"DSD" category in GNU Radio Companion, and "block_ff" will be available
in the "dsd" Python package.

The block expects 48000 samples per second input, and outputs sound at
8000 samples per second.  The input should be FM-demodulated (for
example, with GNU Radio's Quadrature Demod block) and should be between
-1 and 1 while receiving digital signals.  (A quadrature demod gain of
1.6 works well for me for EDACS Provoice.)  The input signal should
also be free of DC bias, so make sure you are tuned accurately, or
filter out DC.

To save CPU cycles, the block detects when the input is zero and avoids
sending it through DSD.  Thus it helps to put a squelch block before
gr-dsd, especially if you're using many copies of gr-dsd in parallel.

The underlying DSD and mbelib were taken from:

* https://github.com/szechyjs/dsd
* https://github.com/szechyjs/mbelib

No modifications to mbelib were required, but DSD has been modified to
bypass the sound card.  The GNU Radio block itself was adapted from the
gr-howto-write-a-block sample included with GNU Radio.

Contributions are welcome!

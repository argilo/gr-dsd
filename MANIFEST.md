title: gr-dsd
brief: A GNU Radio wrapper for Digital Speech Decoder (DSD)
tags:
  - DSD
  - P25
  - DMR
  - D-STAR
author:
  - Clayton Smith <argilo@gmail.com>
copyright_owner:
  - Clayton Smith <argilo@gmail.com>
dependencies:
  - gnuradio (>= 3.7.0)
  - libsndfile
  - libitpp
license: GPLv3
repo: https://github.com/argilo/gr-dsd.git
gr_supported_version: v3.7, v3.8, v3.9
stable_release: HEAD
---
The goal of this project is to package Digital Speech Decoder (DSD) as
a GNU Radio block, so that it can be easily used with software radio
peripherals such as the Ettus Research USRP or RTL2832U-based USB TV
tuners.

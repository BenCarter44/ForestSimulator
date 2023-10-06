#!/bin/bash

# For Ubuntu 18.04 systems

sudo apt remove cmake -y
pip install cmake --upgrade
sudo ln /usr/local/bin/cmake /usr/bin/cmake

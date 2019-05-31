#!/bin/bash
sudo qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk

#! -curses -machine ubuntu,accel=kvm

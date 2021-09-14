#!/bin/bash

##########################################
#
# This script is designed to run by Systemd SCANOSS API service.
# It rotates scanoss log file and starts SCANOSS API.
# Install it in /usr/bin
#
################################################################
smtp-tls "SCANOSS API" "SCANOSS API Starting"
BIND_IP="0.0.0.0"
TSTAMP=$(date '+%Y%m%d-%H%M%S')

# Rotate log
cp /var/log/scanossws.log /var/log/scanossws.log.$TSTAMP
echo > /var/log/scanossws.log

cp /var/log/scanossws-error.log /var/log/scanossws-error.log.$TSTAMP
echo > /var/log/scanossws-error.log
# Start scanossws
# Valgrind flags
 VGFLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 --keep-debuginfo=yes"
 VALGRIND_CMD="valgrind ${VGFLAGS} /usr/bin/scanossws -d -b ${BIND_IP}"
 ${VALGRIND_CMD} >> /var/log/scanossws-error.log 2>&1
#/usr/bin/scanossws -d -b ${BIND_IP}

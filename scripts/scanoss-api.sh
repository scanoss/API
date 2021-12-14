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
cp /var/log/scanoss-api.log /var/log/scanoss-api.log.$TSTAMP
echo > /var/log/scanoss-api.log
#start API
/usr/bin/scanossws -d -b ${BIND_IP}

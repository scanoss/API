#!/bin/bash

DEV_HOST=${1:-dev}
echo "*** PUSHING API TO ${DEV_HOST} ***"
BIND_IP=${2:-"127.0.0.1"}
VERSION=$(grep SCANOSS_API_VERSION src/utils/constants.h | awk '{print $NF}' | sed 's/"//g')
TSTAMP=$(date +%s)


# Copy new file
echo "#1 - Copy new binary"
ssh $DEV_HOST "service scanoss-api stop"
echo "#1.1 - Service stopped"
scp scanossws $DEV_HOST:/usr/bin/scanossws-$VERSION
if [ $? != 0 ]; then
  echo "There was an error when copying new scanossws binary"
  exit 1
fi

# Copy api docs
echo "#2 - Copy API Doc"
ssh $DEV_HOST "mkdir -p /var/lib/scanoss/ui/static"
scp scanoss-openapi.yaml $DEV_HOST:/var/lib/scanoss/ui/static/scanoss-api.yaml

if [ $? != 0 ]; then
  echo "There was an error when copying new scanossws binary"
  exit 1
fi
# Update symlink
echo "#3 - Update symlink"

ssh $DEV_HOST "ln -sf /usr/bin/scanossws-$VERSION /usr/bin/scanossws"
if [ $? != 0 ]; then
  echo "There was an error when updating scanossws symlink"
  exit 1
fi

# Start scanossws
echo "#5 -  Start scanossws"
# Valgrind flags
ssh $DEV_HOST "service scanoss-api start"

if [ $? != 0 ]; then
  echo "There was an error when starting scanossws service"
  exit 1
fi

echo "#6 - Verify that the service is started"
ssh $DEV_HOST "service scanoss-api status"

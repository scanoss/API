#!/bin/bash

SCANOSS_VERSION=$(grep SCANOSS_API_VERSION src/utils/constants.h | awk -F'"' '{print $2}')

# Generate openapi-info.yaml from template

cat src/openapi-info.yaml.tpl | sed "s/%VERSION%/$SCANOSS_VERSION/" > src/openapi-info.yaml

openapi-spec-gen ./src > scanoss-openapi.yaml
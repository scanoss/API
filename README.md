# SCANOSS API

The API is designed to work in conjunction with the SCANOSS Engine to provide an API for Open Source scanning. It is built on top of [WAYUU Web Server](https://github.com/scanoss/wayuu)

# API Usage 

The API defines the `/api/scan/direct` endpoint that can be used to scan SCANOSS WFP files. One easy way to operate with this API endpoint is via one of the availables clients:
- https://github.com/scanoss/scanoss.py
- https://github.com/scanoss/scanoss-cli

# OpenApi docs
You can test this API using the openapi documentation available in: https://docs.osskb.org/

# Building from Source

Make sure to have net-tools installed.

This project depens on Wayuu shared library. When cloning make sure that you run `make install-wayuu` to install the lastest release of Wayuu.

SCANOSS doesn't need any external libraries other than standard Linux GNU extensions as well as OpenSSL and libcrypto. You can build SCANOSS API easily with GCC and Make. 

- `make`: Builds the `scanoss-api` binary.
- `make test`: Executes the unit tests. 

# Installation

Run `make install` and the `scanoss-api` binary will be copied to `/usr/bin` by default.

If you are using Linux you can do a simple systemd script to run the API on startup. Otherwise you can run the binary. 

## Command options

* -d: Logs in debug level.
* -t: Logs in trace level.
* -f: HTTP mode (SSL disable).
* -b[IP]: define bind IP address (default is `127.0.0.1`).
* -p[PORT]: define TCP port number (default is `4443`).
* -r[DIR]: Use root as the root folder for WAYUU (default is `/etc/wayuu`).
* -c[FILE]: use a config json file. Check at test/api-config.json to see an example.
* -l[FILE]: Specify log file path.

# Running tests

ScanOSS API uses the very simple [**snow**](https://github.com/mortie/snow) for unit tests. 

To run all tests: `make test`

If you want to run all tests for a component, for instance, `project`, you can do it like this: `ARGS=project make test`. Or specifically running the binary executable `./test-scanoss-api project`.


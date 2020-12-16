# SCANOSS API

The API is designed to work in conjunction with the SCANOSS Engine to provide an API for Open Source scanning. It is built on top of [WAYUU Web Server](https://github.com/scanoss/wayuu)

# API Usage 

The API defines the `/api/scan/direct` endpoint that can be used to scan SCANOSS WFP files. One easy way to operate with this API endpoint is via [`scanner.py`](https://github.com/scanoss/scanner.py).

# Building from Source

This project includes Wayuu as a git submodule. When cloning make sure that you initialise the submodule running `git submodule init && git submodule update`. This only needs to be done once. Alternatively, clone the project with the`--recurse-submodules` flag (`git clone --recurse-submodules ...`). Keep Wayuu up to date by regularly running `git submodule update`.

SCANOSS doesn't need any external libraries other than standard Linux GNU extensions as well as OpenSSL and libcrypto. You can build SCANOSS API easily with GCC and Make. 

- `make`: Builds the `scanoss-api` binary.
- `make test`: Executes the unit tests. 

# Installation

Run `make install` and the `scanoss-api` binary will be copied to `/usr/bin` by default. 

If you are using Linux you can do a simple systemd script to run the API on startup. Otherwise you can run the binary. 

## Default Values
- Default port is 4443
- Default API Root folder is `/var/lib/scanoss`
- Default bind IP Address is `127.0.0.1`

# Running tests

ScanOSS API uses the very simple [**snow**](https://github.com/mortie/snow) for unit tests. 

To run all tests: `make test`

If you want to run all tests for a component, for instance, `project`, you can do it like this: `ARGS=project make test`. Or specifically running the binary executable `./test-scanoss-api project`.


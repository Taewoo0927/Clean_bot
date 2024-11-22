# Use an official Ubuntu LTS base image
FROM ubuntu:22.04

# Set DEBIAN_FRONTEND to noninteractive to suppress prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages and dependencies
RUN apt-get update && apt-get install -y \
    wget bzip2 make unzip cppcheck \
    libncurses5 libusb-1.0-0-dev \
    mspdebug \
    gcc-msp430 msp430-libc binutils-msp430

# Set the working directory
WORKDIR /workspace

# Set the default command
CMD ["/bin/bash"]
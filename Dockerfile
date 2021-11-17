FROM ubuntu:20.04
RUN apt-get update &&\
    apt-get install --yes --no-install-recommends \
        cmake \
        gdb \
        g++ \
        make &&\
    apt-get autoremove --yes &&\
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
RUN useradd clion
USER clion

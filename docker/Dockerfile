FROM ubuntu:20.04
ARG user=clion
ARG group=clion
ARG PROJECT_ROOT
ENV PROJECT_ROOT=${PROJECT_ROOT}

# Install development tools.
RUN apt-get update &&\
    apt-get install --yes --no-install-recommends \
        ca-certificates \
        cmake \
        curl \
        gdb \
        g++ \
        make &&\
    apt-get autoremove --yes && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Create the container user.
RUN addgroup ${group} && \
    adduser --ingroup ${group} --home /home/${user} --shell /bin/bash --disabled-password ${user}

# Install fixuid for matching the default user's UID and GID to the host user
# at runtime. This is necessary in a development environment where the
# container needs to write to the local project directory. THIS SHOULD NOT BE
# USED IN A PRODUCTION ENVIRONMENT. See <https://github.com/boxboat/fixuid>.
RUN curl -SsL https://github.com/boxboat/fixuid/releases/download/v0.5.1/fixuid-0.5.1-linux-amd64.tar.gz | tar -C /usr/local/bin -xzf - && \
    chmod 4755 /usr/local/bin/fixuid && \
    mkdir -p /etc/fixuid && \
    printf "user: ${user}\ngroup: ${group}\n" > /etc/fixuid/config.yml
USER ${user}
ENTRYPOINT ["fixuid"]

WORKDIR ${PROJECT_ROOT}
CMD ["bash"]

# Prepare the container environment for use as a CLion Docker Toolchain.
set -o errexit

# CLion appears to override the default ENTRYPOINT that runs `fixuid`, so run
# it here instead. See <https://github.com/boxboat/fixuid>.
eval "$(fixuid)"

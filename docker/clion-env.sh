# Prepare the container environment for use as a CLion Docker toolchain. See
# <https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html>.
set -o errexit

# CLion appears to override the default ENTRYPOINT that runs `fixuid`, so run
# it here instead. See <https://github.com/boxboat/fixuid>. The `eval` call
# set $HOME via an `export`.
eval "$(fixuid)"

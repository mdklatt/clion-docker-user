=================
clion-docker-user
=================

This is a basic project to explore user permissions when using a CLion
`Docker toolchain`_. This is motivated by cases where the Docker container
must be run as a specific user during development (`CPP-27415`_). CLion must
run Docker toolchains using the UID and GID of the host user so that
`mounted file permissions` are correct within the container.

The `sample Dockerfile`_ in the JetBrains documentation has a solution for
matching the host user to a specific user inside the Docker container. This
works best in situations where the Docker image can built locally by the same
user who will be running CLion.

If the developer is using a Docker base image that has a predefined user, the
Docker user UID and GID need to matched to the host user at runtime. One
solution for this is `fixuid`_. When the container is started, the UID and GID
of the container user will be modified to match the host user.

The `fixuid`_ documentation suggests using the image ``ENTRYPOINT`` to run
``fixuid``, but it can also be run as part of a container start-up script,
*i.e.* the CLion Docker toolchain environment script.



Running the test application
============================

Running with CLion
------------------

First, build the Docker image using Docker Compose:

.. code:: console

  $ docker compose -f docker/docker-compose.yml build develop

Then, configure the ``clion-docker-user`` image as a `Docker toolchain` and
specify ``docker/clion-env.sh`` as the toolchain environment script.

The test application can be build and run from the IDE.


Running manually
----------------

First, run the Docker image using Docker Compose (the image will be built if it
does not already exist):

.. code:: console

  $ export UID=$(id -u)
  $ export GID=$(id -g)
  $ docker compose -f docker/docker-compose.yml run --rm develop

Then, build and run the application inside the running container.

.. code:: console

  user@container $ cmake -S . -B .build
  user@container $ cmake --build .build
  user@container $ .build/clion_docker_user


Expected output
---------------

When the application is built and executed, it will display information
about the container user. Whether using CLion or running manually, the
output should be the same:

.. code:: console

  fixuid: TRUE
  HOME: /home/clion
  whoami: clion
  UID: <host UID>
  GID: <host GID>

The UID and GID should match the host user values. For macOS, this is typically
``501`` and ``20`` respectively.


.. _Docker toolchain: https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html
.. _CPP-27415: https://youtrack.jetbrains.com/issue/CPP-27415
.. _mounted file permissions: https://dille.name/blog/2018/07/16/handling-file-permissions-when-writing-to-volumes-from-docker-containers
.. _sample Dockerfile: https://www.jetbrains.com/help/clion/clion-toolchains-in-docker.html#sample-dockerfile
.. _fixuid: https://github.com/boxboat/fixuid
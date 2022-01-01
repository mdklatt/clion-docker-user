#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <filesystem>

using std::cout;
using std::endl;
using std::filesystem::exists;
using std::exception;
using std::getenv;
using std::runtime_error;
using std::string;


/**
 * Display info for the Docker container user.
 *
 * @return process exit status
 */
int main()
try {
    // The UID and GID should match the host user, typically 501:20 on macOS.
    // These should have been defined in the Docker `run` command.
    cout << "UID: " << geteuid() << endl;
    cout << "GID: " << getegid() << endl;

    // Determine if `fixuid` ran, either as the image ENTRYPOINT or as part of
    // the CLion toolchain environment script.
    const auto fixuid{exists("/var/run/fixuid.ran")};
    cout << "fixuid: " << (fixuid ? "TRUE" : "FALSE") << endl;

    // This should be 'clion' as the result of running `fixuid'.
    const auto user{cuserid(nullptr)};
    cout << "user: " << (user ? user : "") << endl;

    // This should be '/home/clion' as the result of running `fixuid'.
    const auto home{getenv("HOME")};
    cout << "HOME: " << (home ? home : "") << endl;

    // HOME UID and GID should match the host user.
    struct stat statbuf{};
    if (stat(home, &statbuf) != 0) {
        throw runtime_error(strerror(errno));
    }
    cout << "HOME UID: " << statbuf.st_uid << endl;
    cout << "HOME GID: " << statbuf.st_gid << endl;

    return EXIT_SUCCESS;
}
catch (const exception& ex) {
    cout << "ERROR: " << ex.what() << endl;
    return EXIT_FAILURE;
}

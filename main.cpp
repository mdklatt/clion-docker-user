#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
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
using std::to_string;

extern string whoami();


/**
 * Display info for the Docker continer user.
 *
 * @return process exit status
 */
int main()
try {
    // Determine if `fixuid` ran, either as the image ENTRYPOINT or as part of
    // the CLion toolchain environment script.
    const auto fixuid{exists("/var/run/fixuid.ran")};
    cout << "fixuid: " << (fixuid ? "TRUE" : "FALSE") << endl;

    // This should be set to /home/clion when `fixuid` is run.
    const auto home{getenv("HOME")};
    cout << "HOME: " << (home ? home : "") << endl;

    // Verify that 'clion' is the current user.
    const auto user{whoami()};
    cout << "whoami: " << user;

    // The UID should match the host user, typically 501 on macOS.
    const auto uid{getuid()};
    cout << "UID: " << uid << endl;
    auto *const pwd{getpwuid(uid)};
    if (not pwd) {
        throw runtime_error("no password file entry for " + to_string(uid));
    }

    // The GID should match the host user, typically 20 ('staff') on macOS.
    cout << "GID: " << pwd->pw_gid << endl;

    return EXIT_SUCCESS;
}
catch (const exception& ex) {
    cout << "ERROR: " << ex.what() << endl;
    return EXIT_FAILURE;
}

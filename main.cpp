#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::exception;
using std::getenv;
using std::runtime_error;
using std::string;
using std::to_string;

extern string whoami();


/**
 * Display process user info.
 *
 * @return process exit status
 */
int main()
try {
    const auto home{getenv("HOME")};
    cout << "$HOME: " << (home ? home : "") << endl;
    const auto user{whoami()};
    cout << "whoami: " << user;
    const auto uid{getuid()};
    cout << "UID: " << uid << endl;
    auto *const pwd{getpwuid(uid)};
    if (not pwd) {
        throw runtime_error("no password file entry for " + to_string(uid));
    }
    cout << "GID: " << pwd->pw_gid << endl;
    return EXIT_SUCCESS;
}
catch (const exception& ex) {
    cout << "ERROR: " << ex.what() << endl;
    return EXIT_FAILURE;
}

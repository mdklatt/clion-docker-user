#include <pwd.h>
#include <unistd.h>
#include <iostream>


/**
 * Display process user info.
 *
 * @return process exit status
 */
int main() {
    const auto uid(geteuid());
    std::cout << "UID: " << uid << std::endl;
    auto *const pwd(getpwuid(uid));
    if (not pwd) {
        std::cout << "Unknown user";
    }
    else {
        // Expecting "clion" for the Docker container.
        std::cout << "User is " << pwd->pw_name << " (" << uid << ")";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

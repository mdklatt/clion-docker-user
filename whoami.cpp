#include <array>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <stdexcept>

using std::array;
using std::runtime_error;
using std::string;
using std::unique_ptr;


/**
 * Execute the `whoami` command.
 *
 * @return: user name
 */
string whoami() {
    array<char, 32> buffer{};  // max length per `man useradd`
    string output;
    const auto pipe{popen("whoami 2>&1", "r")};
    if (!pipe) {
        throw runtime_error("popen failed");
    }
    while (fgets(buffer.data(), buffer.size(), pipe)) {
        output += buffer.data();
    }
    if (pclose(pipe) != EXIT_SUCCESS) {
       throw runtime_error("command failed: " + output);
    }
    return output;
}

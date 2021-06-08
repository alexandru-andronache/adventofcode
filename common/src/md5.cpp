#ifdef USE_OPENSSL
#include "md5.h"
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

namespace md5 {

    std::string calculateMD5(std::string hash) {
        unsigned char result[MD5_DIGEST_LENGTH];
        MD5((unsigned char *) hash.c_str(), hash.size(), result);

        std::ostringstream sout;
        sout << std::hex << std::setfill('0');
        for (long long c: result) {
            sout << std::setw(2) << (long long) c;
        }

        return sout.str();
    }

}
#endif
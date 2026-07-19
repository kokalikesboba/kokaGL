#ifndef HASH_HPP
#define HASH_HPP

#include <vector>
#include <cstddef>

namespace Hash {

inline unsigned int djb2(const unsigned char* data, size_t len)
{
    unsigned int h = 5381;
    for (size_t i = 0; i < len; ++i)
        h = h * 31 + data[i];
    return h;
}

inline unsigned int djb2(const std::vector<unsigned char>& data)
{
    return djb2(data.data(), data.size());
}

}

#endif
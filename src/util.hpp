#pragma once

/**
 * Align the number of bytes up to the next closest word (4 bytes)
 */
inline int word_align(int bytes) {
    return 4*(bytes/4) + (bytes % 4 != 0 ? 1 : 0);
}

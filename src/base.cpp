#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include "config.h"
#include "base.h"

void LOG(string message, unsigned char ll) {
    if (LOG_LEVEL & ll) {
        cerr << message << endl;
    }
}

void displayBI(t_bint* a, t_size size) {
    cerr << "0x" << hex;
    for (; a[size - 1] == 0; size--) {
    }
    if (size == 0) {
        cerr << "0";
        return;
    }
    else {
        cerr << (unsigned long long)a[size - 1];
        size--;
        for (; size > 0; size--) {
            cerr << setfill('0') << setw(BLOCK_SIZE / 4)
                 << (unsigned long long)a[size - 1];
        }
    }
}

void scanBI(t_bint* a, const char* aStr, t_size sizeA) {
    t_size size = strlen(aStr);
    t_size i;
    const t_size ULONG_STR_SIZE = ULONG_SIZE * 2;
    t_size loopEnd = size - BLOCKS_NUMBER * BLOCK_SIZE;
    loopEnd = loopEnd > 0 ? loopEnd : 0 + size % ULONG_STR_SIZE;
    char* currentNumber = new char[ULONG_STR_SIZE + 1];
    memset(currentNumber, 0, ULONG_STR_SIZE + 1);
    char* tmp; // Do not delete[]! Needed for strtoul
    for (i = size - ULONG_STR_SIZE; i >= loopEnd; i -= ULONG_STR_SIZE,
         (ULONG*)a++) {
        memcpy(currentNumber, &aStr[i], ULONG_STR_SIZE);
        *(ULONG*)a = strtoul(currentNumber, &tmp, 16);
    }
    memset(currentNumber, 0, ULONG_STR_SIZE + 1);
    memcpy(currentNumber, &aStr[0], size % ULONG_STR_SIZE);
    *(ULONG*)a = strtoul(currentNumber, &tmp, 16);
    delete[] currentNumber;
}

unsigned char cmp(t_bint* a, t_bint b, t_size size) {
    if (a[0] > b) {
        return CMP_GREATER;
    }
    for (t_size i = 1; i < size; i++) {
        if (a[i]) {
            return CMP_GREATER;
        }
    }
    if (a[0] == b) {
        return CMP_EQUAL;
    }
    else if (a[0] < b) {
        return CMP_LOWER;
    }
    else {
        return CMP_GREATER;
    }
}

unsigned char cmp(t_bint* a, t_bint* b, t_size size1, t_size size2) {
    if (!size2) {
        size2 = size1;
    }
    t_size i;
    if (size1 > size2) {
        for (i = size1 - 1; i >= size2; i--) {
            if (a[i]) {
                return CMP_GREATER;
            }
        }
    }
    else if (size2 > size1) {
        for (i = size2 - 1; i >= size1; i--) {
            if (b[i]) {
                return CMP_LOWER;
            }
        }
    }
    else {
        i = size1 - 1;
    }
    for (; i >= 0; i--) {
        if (a[i] > b[i]) {
            return CMP_GREATER;
        }
        else if (a[i] < b[i]) {
            return CMP_LOWER;
        }
    }
    return CMP_EQUAL;
}

void mov(t_bint* a, t_bint* b, t_size size) {
    memcpy(a,b,size * sizeof(t_size));
}

t_size msw(t_bint* a, t_size size) {
    while (--size >= 0) {
        if (a[size] > 0) {
            return size;
        }
    }

    return -1;
}

t_size msb(t_bint* a, t_size size) {
    t_size result = msw(a,size);
    t_size i;
    if (result == -1) {
        return -1;
    }
    t_bint tmp = a[result];
    result *= BLOCK_SIZE;
    for (i = 0; i < BLOCK_SIZE; i++) {
        tmp >>= 1;
        if (!tmp) {
            return result + i;
        }
    }
    return -2;
}

bool isNull(t_bint* a, t_size size) {
    if (size < 1) {
        return true;
    }
    if (a == NULL) {
        return true;
    }
    while (size-- > 0) {
        if (a[size]) {
            return false;
        }
    }
    return true;
}

void setNull(t_bint* a, t_size size) {
    memset(a,0,size * sizeof(t_bint));
}
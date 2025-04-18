#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t(*cb_t)(uint64_t, uint64_t);

uint64_t kernel1(uint64_t, uint64_t);
uint64_t kernel2(uint64_t, uint64_t);
uint64_t kernel3(uint64_t, uint64_t);
uint64_t kernel4(uint64_t, uint64_t);

void transform(uint8_t* buf, size_t len, cb_t cb);

int main()
{
    FILE* in = fopen("input.bin", "rb");
	assert(in);

    fseek(in, 0, SEEK_END);
    long in_len = ftell(in);
    fseek(in, 0, 0);

    uint8_t* dst_buf = malloc(in_len);
	assert(dst_buf);
    fread(dst_buf, 1, in_len, in);
    fclose(in);

    unsigned coef = in_len >> 0x1f;
    long cond = (in_len + (coef & 3) & 3) - (coef & 3);

	cb_t cb;
    if (cond == 0)
        cb = &kernel1;
    else if (cond == 1)
        cb = &kernel2;
    else if (cond == 2)
        cb = &kernel3;
    else
        cb = &kernel4;

    transform(dst_buf, in_len, cb);

    FILE* out = fopen("output.bin", "wb");
    assert(out);

    fwrite(dst_buf, 1, in_len, out);
    fclose(out);
    free(dst_buf);
}

uint64_t kernel1(uint64_t v1, uint64_t v2)
{
	return v1 ^ v2 * 0x17 + 4U;
}

uint64_t kernel2(uint64_t v1, uint64_t v2)
{
	return v1 ^ v2 * 0x1d + v1 - 4;
}

uint64_t kernel3(uint64_t v1, uint64_t v2)
{
	return v1 - (v2 * v1 + 0xe);
}

uint64_t kernel4(uint64_t v1, uint64_t v2)
{
	return v1 + v2 * 0x22 + v1 * 7;
}

extern char table[256];

void
transform(uint8_t* buf, size_t len, cb_t cb)
{
    char accum = 0;
    for (size_t i = 0; i < len; ++i)
    {
        buf[i] = table[buf[i]];
        accum = accum ^ buf[i];
    }

    for (size_t i = 0; i < len; ++i)
    {
        char val = (buf[i] >> 3 | buf[i] << 5) + (char)i * '\r';
        buf[i] = val ^ cb(val - accum, i);
    }
}


char table[256] = {
    0x71, 0x30, 0xBA, 0x99, 0xE5, 0x39, 0x0F, 0x33, 0x2A, 0x15, 0x92, 0xD3, 0x77, 0xB6, 0xEB, 0xDF,
    0x9C, 0x83, 0x27, 0xB7, 0x76, 0x5C, 0x35, 0x0C, 0x84, 0x4C, 0x9B, 0x2C, 0x29, 0x6D, 0x66, 0x80,
    0x43, 0xA8, 0x4A, 0x38, 0x1D, 0xFB, 0x44, 0x5D, 0x12, 0x75, 0x98, 0xB0, 0x06, 0x5A, 0x42, 0x91,
    0xF6, 0xA1, 0xCC, 0x74, 0xAC, 0x9D, 0x8B, 0x5F, 0x3C, 0xED, 0x0A, 0x46, 0xE9, 0xA6, 0xF0, 0x78,
    0x61, 0x51, 0xEF, 0xA4, 0x94, 0x3E, 0x1B, 0x01, 0xF3, 0x37, 0xE4, 0xE1, 0xE2, 0xF9, 0xE6, 0x70,
    0x25, 0x3B, 0xA9, 0x6A, 0x6C, 0x09, 0xCF, 0x28, 0x19, 0x89, 0xD7, 0xC1, 0x8C, 0x40, 0x73, 0xC5,
    0x69, 0xF1, 0x79, 0x1E, 0x11, 0xAA, 0xC0, 0x64, 0x6E, 0x20, 0x4E, 0x10, 0xD6, 0xB3, 0x24, 0xAD,
    0xD1, 0xF8, 0x81, 0x54, 0x1F, 0xB4, 0x36, 0x9F, 0x3D, 0x8F, 0xD9, 0x00, 0xDA, 0xC3, 0xDC, 0xAE,
    0xD5, 0x2F, 0xEE, 0xC4, 0xC9, 0x02, 0x14, 0x85, 0x34, 0x3F, 0x13, 0x05, 0x90, 0xF4, 0xC7, 0xE3,
    0x58, 0x04, 0xFC, 0x7B, 0x07, 0xEC, 0xF2, 0xA3, 0xFF, 0xFE, 0xD4, 0x57, 0x7F, 0x21, 0xD2, 0x18,
    0x4B, 0x50, 0x17, 0x8D, 0x62, 0xCE, 0x97, 0x08, 0xE7, 0x59, 0x5B, 0x82, 0x68, 0x3A, 0x1C, 0xF5,
    0x7D, 0x0D, 0xAB, 0xBC, 0x7E, 0x86, 0x45, 0xDB, 0x67, 0xA2, 0x93, 0x4F, 0x2B, 0xFD, 0xCB, 0x65,
    0xB1, 0x7C, 0x0E, 0x47, 0x72, 0xD0, 0x4D, 0x32, 0x96, 0xBE, 0x9A, 0x53, 0xB2, 0xC6, 0x16, 0x41,
    0x2D, 0xCD, 0x6B, 0xAF, 0xCA, 0xFA, 0xEA, 0xA0, 0x95, 0x2E, 0x5E, 0xB8, 0xDE, 0xB5, 0x1A, 0xA7,
    0x26, 0xE0, 0xF7, 0x8E, 0x31, 0xB9, 0xC8, 0xD8, 0x63, 0x87, 0x56, 0x48, 0xC2, 0x55, 0xBB, 0x49,
    0x03, 0x88, 0xA5, 0x9E, 0xBD, 0x52, 0x0B, 0x6F, 0x8A, 0x60, 0xDD, 0x22, 0x7A, 0x23, 0xBF, 0xE8,
};

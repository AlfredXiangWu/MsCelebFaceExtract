#ifndef BASE64_H_
#define BASE64_H_

#include <stdint.h>
#include <stdlib.h>

void build_decoding_table();
int get_decode_output(const char* data, size_t input_length, size_t *output_length);
int base64_decode(const char *data, unsigned char* decoded_data, size_t input_length, size_t *output_length);
void base64_cleanup();

#endif // BASE64_H_
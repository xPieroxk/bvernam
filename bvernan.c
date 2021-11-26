#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

data_files *load_data_files(char *key_file, char *input_file, char *output_file) {
    data_files *pointer = malloc(sizeof(data_files));
    FILE *key = fopen(key_file, "rb");
    FILE *input = fopen(input_file, "rb");
    if (key == NULL || input == NULL)
        perror("Error ");
    FILE *output = fopen(output_file, "wb");
    pointer->key_file = key;
    pointer->input_file = input;
    pointer->output_file = output;
    return pointer;
}

source_byte *load_source_byte(data_files *d) {
    source_byte *pointer = malloc(sizeof(source_byte));
    fseek(d->key_file, 0L, SEEK_END);
    long k_size = ftell(d->key_file);
    fseek(d->key_file, 0, SEEK_SET);
    // empty input file or key file implies that there is nothing to encrypt
    if (fread(&pointer->byte, sizeof(unsigned char), 1, d->input_file) != 1 || k_size == 0)
        return NULL;
    pointer->byte_index = 0;
    pointer->block_index = 0;
    pointer->block_size = k_size;
    pointer->encrypted_byte = 0;
    return pointer;
}

source_byte *update_source_byte(data_files *d, source_byte *s) {
    // update indexes
    s->byte_index++;
    s->block_index = s->byte_index / s->block_size;
    long key_index = (s->byte_index + s->block_index) % s->block_size;
    // update pointer of key file
    if (key_index == 0)
        fseek(d->key_file, 0, SEEK_SET);
    else if (s->byte_index % s->block_size == 0)
        fseek(d->key_file, key_index, SEEK_SET);
    // reads a byte from the input file
    if (fread(&s->byte, sizeof(unsigned char), 1, d->input_file) < 1)
        return NULL;
    return s;
}


source_byte *encode(data_files *d, source_byte *s) {
    unsigned key_byte;
    if (fread(&key_byte, sizeof(unsigned char), 1, d->key_file) != 1)
        return NULL;
    s->encrypted_byte = key_byte ^ s->byte;
    return s;
}


int upload_encrypted_byte(data_files *d, source_byte *s) {
    return fwrite(&s->encrypted_byte, sizeof(unsigned char), 1, d->output_file) == 1 ?
           1 : -1;
}


void free_bvernan(data_files *d, source_byte *s) {
    free(s);
    fclose(d->key_file);
    fclose(d->input_file);
    fclose(d->output_file);
    free(d);
}


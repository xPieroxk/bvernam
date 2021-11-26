#ifndef PIEROHIERRO110944_BVERNAN_H
#define PIEROHIERRO110944_BVERNAN_H

/**
 * This struct is used to keep information about the byte to encrypt.
 */
typedef struct {
    long byte_index;
    long block_index;
    long block_size;
    unsigned char byte;
    unsigned char encrypted_byte;
} source_byte;

/**
 * This struct is used to keep track about the key,input and output files.
 */
typedef struct {
    FILE *key_file;
    FILE *input_file;
    FILE *output_file;
} data_files;

/**
 * Initializes and returns a pointer to data_files.
 *
 * @param key_file key file path
 * @param input_file input file path
 * @param output_file output file path
 * @return a pointer to data_files
 */
data_files *load_data_files(char *key_file, char *input_file, char *output_file);

/**
 * Initializes and returns a pointer to source_byte.
 *
 * @param  d a data_files from which to take information to initialize the block size
 * @return a pointer to source_byte or NULL if there is nothing to encrypt
 */
source_byte *load_source_byte(data_files *d);

/**
 * Updates source_byte fields.
 *
 * @param d a data_files from which to take information to update source_byte
 * @param s the source_byte to update
 * @return a pointer to the same source_byte but updated or NULL if nothing has been updated
 */
source_byte *update_source_byte(data_files *d, source_byte *s);

/**
 * Apply bvernan encryption.
 *
 * @param d a data_files from which to take information to update source_byte
 * @param s a source_byte containing the byte to encrypt
 * @return the same souce_byte but now containing the encrypted byte
 *         or null if the encryption could not be performed
 */
source_byte *encode(data_files *d, source_byte *s);

/**
 * Writes the encrypted byte to the output file.
 *
 * @param d a data_files from which to take information to upload the encrypted byte
 * @param s a source_byte containing the encrypted byte to be uploaded
 * @return 1 if the byte has been loaded, -1 otherwise
 */
int upload_encrypted_byte(data_files *d, source_byte *s);

/**
 * Deallocates a source_byte and a data_file and closes its associated files.
 *
 * @param d a data_files to deallocate and close the associated files
 * @param s a source_byte to deallocate
 */
void free_bvernan(data_files *d, source_byte *s);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Error: Incorrect number of parameters!\n");
        exit(EXIT_FAILURE);
    }

    data_files *data = load_data_files(argv[1], argv[2], argv[3]);
    source_byte *source_b = load_source_byte(data);
    if (source_b == NULL)
        return 0;
    do {
        if (encode(data, source_b) == NULL || upload_encrypted_byte(data, source_b) == -1) {
            free_bvernan(data, source_b);
            fprintf(stderr, "Error: Something went wrong during the encryption...\n");
            exit(EXIT_FAILURE);
        }
    } while (update_source_byte(data, source_b) != NULL);
    free_bvernan(data, source_b);
    return 0;
}

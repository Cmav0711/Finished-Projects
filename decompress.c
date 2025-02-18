#include "decompress.h"

void decompress_dna(const unsigned char *compressed_data, int compressed_length, char *decompressed_dna) {
    int i = 1;                         // Start at 1 to skip the length byte
    int index = 0;                     // Index for decompressed DNA string
    int dna_length = compressed_data[0]; // Original length of the DNA string

    for (; i < compressed_length; ++i) {
        unsigned char current_byte = compressed_data[i];

        // Extract 2 bits at a time, starting from the most significant bits
        for (int shift = 6; shift >= 0; shift -= 2) {
            if (index >= dna_length) { // Stop if we have reached the original DNA length
                decompressed_dna[index] = '\0'; // Null-terminate the decompressed string
                return;
            }

            unsigned char encoded_value = (current_byte >> shift) & 0x03; // Extract 2 bits
            char dna_char;

            // Decode the 2-bit value into the corresponding DNA character
            switch (encoded_value) {
                case 0: dna_char = 'A'; break;
                case 1: dna_char = 'T'; break;
                case 2: dna_char = 'C'; break;
                case 3: dna_char = 'G'; break;
                default: return; // Invalid data
            }

            decompressed_dna[index++] = dna_char;
        }
    }

    decompressed_dna[index] = '\0'; // Null-terminate the decompressed string
}

#include "compress.h"

void compress_dna(const char *dna, unsigned char *compressed_data, int *compressed_length) {
    int i = 0;         // Index for DNA characters
    int index = 1;     // Index for compressed data array, start at 1 to leave space for length
    unsigned char current_byte = 0;
    int shift = 6;     // Start at the most significant bits for the first pair

    // Store the length of the DNA string as the first element
    compressed_data[0] = (unsigned char) strlen(dna);

    while (dna[i] != '\0') {
        unsigned char encoded_value;

        // Encode DNA character to 2-bit value
        switch (dna[i]) {
            case 'A': encoded_value = 0; break; // 00
            case 'T': encoded_value = 1; break; // 01
            case 'C': encoded_value = 2; break; // 10
            case 'G': encoded_value = 3; break; // 11
            default: return; // Invalid character
        }

        // Place the encoded value in the current byte
        current_byte |= (encoded_value << shift);
        shift -= 2;

        // If we've filled the byte, move to the next
        if (shift < 0) {
            compressed_data[index++] = current_byte;
            current_byte = 0; // Reset for the next byte
            shift = 6;        // Reset shift for a new byte
        }

        i++;
    }

    // If there is remaining data in current_byte, add it to compressed_data
    if (shift != 6) {
        compressed_data[index++] = current_byte;
    }

    *compressed_length = index; // Set the total length of the compressed data
}

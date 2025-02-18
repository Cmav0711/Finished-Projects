#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "decompress.h"

// Define maximum sizes for compressed and decompressed data
#define MAX_COMPRESSED_LENGTH 1024
#define MAX_DNA_LENGTH 2048

int main(int argc, char *argv[]) {
    // Check if the user has provided the correct number of command-line arguments
    if (argc < 3) {
        printf("Usage: %s -c/-d DNA_STRING/COMPRESSED_DATA\n", argv[0]);
        return 1;
    }

    // Check if the user wants to compress the DNA string
    if (strcmp(argv[1], "-c") == 0) {
        char *dna_string = argv[2]; // Get the DNA string from the command-line arguments
        unsigned char compressed_data[MAX_COMPRESSED_LENGTH]; // Array to hold compressed data
        int compressed_length; // Variable to store the length of the compressed data

        // Call the compression function to compress the DNA string
        compress_dna(dna_string, compressed_data, &compressed_length);

        // Print the compressed data to the console
        for (int i = 0; i < compressed_length; ++i) {
            printf("%u ", compressed_data[i]); // Print each byte of compressed data as an unsigned integer
        }
        printf("\n");

    } 
    // Check if the user wants to decompress the data
    else if (strcmp(argv[1], "-d") == 0) {
        unsigned char compressed_data[MAX_COMPRESSED_LENGTH]; // Array to hold compressed input data
        int compressed_length = argc - 2; // Calculate the number of compressed data elements provided

        // Convert command-line arguments to unsigned char values and store in compressed_data array
        for (int i = 0; i < compressed_length; ++i) {
            compressed_data[i] = (unsigned char)atoi(argv[i + 2]);
        }

        char decompressed_dna[MAX_DNA_LENGTH]; // Array to hold the decompressed DNA string

        // Call the decompression function to decompress the data
        decompress_dna(compressed_data, compressed_length, decompressed_dna);
        
        // Print the decompressed DNA string
        printf("%s\n", decompressed_dna);

    } 
    // If the user provided an invalid option
    else {
        printf("Invalid option. Use -c for compression or -d for decompression.\n");
        return 1;
    }

    return 0; // Indicate successful program termination
}
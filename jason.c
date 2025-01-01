#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neurolib.h"

#define MAX_INPUT 256 // Maximum size for user input

void extract_value(const char *json, const char *key, char *value, size_t value_size) {
    const char *key_pos = strstr(json, key);
    if (key_pos == NULL) {
        value[0] = '\0';
        return;
    }

    const char *colon = strchr(key_pos, ':');
    if (colon == NULL) {
        value[0] = '\0';
        return;
    }

    while (*colon != ':') colon++;
    colon++;

    while (*colon == ' ' || *colon == '\t' || *colon == '\n' || *colon == '\r') colon++;

    if (*colon == '"') {
        colon++;
        size_t i = 0;
        while (i < value_size - 1 && *colon != '"') {
            if (*colon == '\\') {
                colon++;
                if (*colon == '"') {
                    value[i++] = '"';
                } else if (*colon == '\\') {
                    value[i++] = '\\';
                } else if (*colon == 'n') {
                    value[i++] = '\n';
                } else if (*colon == 't') {
                    value[i++] = '\t';
                } else if (*colon == 'r') {
                    value[i++] = '\r';
                } else {
                    value[i++] = *colon;
                }
                colon++;
            } else {
                value[i++] = *colon++;
            }
        }
        value[i] = '\0';
    } else {
        size_t i = 0;
        while (i < value_size - 1 && *colon != ',' && *colon != '}' && *colon != '\0') {
            if (*colon == ' ' || *colon == '\t' || *colon == '\n' || *colon == '\r') {
                colon++;
                continue;
            }
            value[i++] = *colon++;
        }
        value[i] = '\0';
    }
}

void print_with_newlines(const char *value) {
    while (*value) {
        if (*value == '\\' && *(value + 1) == 'n') {
            printf("\n");
            value += 2;
        } else {
            putchar(*value);
            value++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s [--extract <filename> | --bot]\n", argv[0]);
        return 1;
    }

    char *key = argv[1];

    if (strcmp(key, "--extract") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s --extract <filename>\n", argv[0]);
            return 1;
        }

        char *filename = argv[2];
        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        rewind(file);

        if (filesize > 1024 * 1024) {
            fprintf(stderr, "File size exceeds limit\n");
            fclose(file);
            return 1;
        }

        char *buffer = malloc(filesize + 1);
        if (!buffer) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            return 1;
        }

        size_t bytesRead = fread(buffer, 1, filesize, file);
        if (bytesRead == 0 && ferror(file)) {
            perror("Error reading file");
            free(buffer);
            fclose(file);
            return 1;
        }
        buffer[bytesRead] = '\0';
        fclose(file);

        char value[256] = {0};
        extract_value(buffer, "\"content\"", value, sizeof(value));
        print_with_newlines(value);

        free(buffer);
    } else if (strcmp(key, "--bot") == 0) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s --bot\n", argv[0]);
            return 1;
        }
        neurosym_init();
        char value[MAX_INPUT] = {0};
        char input[MAX_INPUT];

        while (1) {
            printf("What would you like to know? ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                break;
            }

            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "exit") == 0) {
                break;
            }

            char *call = response(input);
            if (call) {
                extract_value(call, "\"content\"", value, sizeof(value));
                print_with_newlines(value);
                printf("\n");
                free(call);
            } else {
                printf("No response available.\n");
            }
        }
        neurosym_cleanup(); // Assuming cleanup function exists
    } else {
        fprintf(stderr, "Usage: %s [--extract <filename> | --bot]\n", argv[0]);
        return 1;
    }

    return 0;
}
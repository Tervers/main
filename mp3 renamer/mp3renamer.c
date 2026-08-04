#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "id3v2lib.h"

#define MAX_PATH_LEN 512

void sanitize_filename(char *str) {
    const char *illegal = "\\/:*?\"<>|";
    for (; *str; ++str) {
        if (strchr(illegal, *str)) *str = '_';
    }
}

int main(void) {
    WIN32_FIND_DATA find_data;
    HANDLE hFind = FindFirstFile("*.mp3", &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No .mp3 files found.\n");
        return 0;
    }

    do {
        const char *filename = find_data.cFileName;
        printf("Processing: %s\n", filename);

        ID3v2_Tag *tag = ID3v2_read_tag(filename);
        if (!tag) {
            fprintf(stderr, "Could not read tag for %s\n", filename);
            continue;
        }

        ID3v2_Frame *artist_frame = ID3v2_Tag_get_frame(tag, "TPE2");
        ID3v2_Frame *title_frame  = ID3v2_Tag_get_frame(tag, "TIT2");

        const char *artist = (artist_frame && artist_frame->data.text) ? artist_frame->data.text : "Unknown Artist";
        const char *title  = (title_frame && title_frame->data.text) ? title_frame->data.text : "Unknown Title";

        char new_name[MAX_PATH_LEN];
        snprintf(new_name, sizeof(new_name), "%s - %s.mp3", artist, title);
        sanitize_filename(new_name);

        if (strcmp(filename, new_name) != 0) {
            if (rename(filename, new_name) == 0)
                printf("Renamed to: %s\n", new_name);
            else
                perror("rename failed");
        } else {
            printf("Filename already matches tag: %s\n", filename);
        }

        ID3v2_free_tag(tag);

    } while (FindNextFile(hFind, &find_data));

    FindClose(hFind);
    return 0;
}
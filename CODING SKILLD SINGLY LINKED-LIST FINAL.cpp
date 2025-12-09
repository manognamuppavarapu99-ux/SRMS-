#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char title[50];
    char artist[50];
    struct Song *next;
};

struct Song *head = NULL;

// Create a new song node
struct Song* createSong(char title[], char artist[]) {
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song));
    if (newSong == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->next = NULL;
    return newSong;
}

// Add song at the end of the playlist
void addSongAtEnd(char title[], char artist[]) {
    struct Song *newSong = createSong(title, artist);

    if (head == NULL) {
        head = newSong;
        printf("Song added as the first song.\n");
        return;
    }

    struct Song *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newSong;

    printf("Song added at the end.\n");
}

// Add song at the beginning
void addSongAtBeginning(char title[], char artist[]) {
    struct Song *newSong = createSong(title, artist);
    newSong->next = head;
    head = newSong;

    printf("Song added at the beginning.\n");
}

// Display playlist
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song *temp = head;
    printf("\n=== MUSIC PLAYLIST ===\n");
    while (temp != NULL) {
        printf("Song: %s | Artist: %s\n", temp->title, temp->artist);
        temp = temp->next;
    }
    printf("======================\n");
}

// Play the next song (move head)
void playNext() {
    if (head == NULL) {
        printf("Playlist is empty. No songs to play.\n");
        return;
    }

    printf("Now Playing: %s by %s\n", head->title, head->artist);
    head = head->next;  // move to next song
}

// Search for a song
void searchSong(char title[]) {
    struct Song *temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            printf("Song found at position %d: %s by %s\n", pos, temp->title, temp->artist);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("Song not found in the playlist.\n");
}

// Delete song by title
void deleteSong(char title[]) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song *temp = head;
    struct Song *prev = NULL;

    // Delete first song
    if (strcmp(head->title, title) == 0) {
        head = head->next;
        free(temp);
        printf("Song deleted successfully.\n");
        return;
    }

    // Search for song in the playlist
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Song not found
    if (temp == NULL) {
        printf("Song not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Song deleted successfully.\n");
}

int main() {
    int choice;
    char title[50], artist[50];

    while (1) {
        printf("\n===== MUSIC PLAYLIST MENU =====\n");
        printf("1. Add Song at End\n");
        printf("2. Add Song at Beginning\n");
        printf("3. Display Playlist\n");
        printf("4. Play Next Song\n");
        printf("5. Search Song\n");
        printf("6. Delete Song\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                fgets(title, 50, stdin);
                title[strcspn(title, "\n")] = '\0';

                printf("Enter artist name: ");
                fgets(artist, 50, stdin);
                artist[strcspn(artist, "\n")] = '\0';

                addSongAtEnd(title, artist);
                break;

            case 2:
                printf("Enter song title: ");
                fgets(title, 50, stdin);
                title[strcspn(title, "\n")] = '\0';

                printf("Enter artist name: ");
                fgets(artist, 50, stdin);
                artist[strcspn(artist, "\n")] = '\0';

                addSongAtBeginning(title, artist);
                break;

            case 3:
                displayPlaylist();
                break;

            case 4:
                playNext();
                break;

            case 5:
                printf("Enter song title to search: ");
                fgets(title, 50, stdin);
                title[strcspn(title, "\n")] = '\0';
                searchSong(title);
                break;

            case 6:
                printf("Enter song title to delete: ");
                fgets(title, 50, stdin);
                title[strcspn(title, "\n")] = '\0';
                deleteSong(title);
                break;

            case 7:
                printf("Exiting Playlist...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}


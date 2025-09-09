#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ID = 1;
typedef struct Song{
    int id;
    char title[50];
    char artist[50];
    float duration;
    struct Song *next;
    struct Song *prev;
} Song;
Song *current = NULL;
//creat song
Song *creatSong(char *title, char *artist , float duration){
    Song *newSong = (Song *)malloc(sizeof(Song));
    if (newSong != NULL){
        newSong->id = ID++;
        strcpy(newSong->title, title);
        strcpy(newSong->artist, artist);
        newSong->duration = duration;
        newSong->next = NULL;
        newSong->prev = NULL;
    }
    else{
        printf("failed to creat Song!!\n");
    }
    return newSong;
}

//add Song
void addSong(Song **head, char *title, char *artist, float duration){
    Song *new = creatSong(title, artist, duration);
    if (*head == NULL){
        *head = new;
        (*head)->next = *head;
        (*head)->prev = *head;
        current = new;
    }
    else {
        Song *last = (*head)->prev;
        last->next = new;
        new->next = *head;
        new->prev = last;
        (*head)->prev = new;
    }
}
//delete Song
void deleteSong(Song **head, int id){
    //playlist empty
    if (*head == NULL){
        printf("Playlist is already empty!!\n");
        return;
    }
    //playlis non empty
    Song *deleted = *head;
    while (deleted->id != id && deleted->next != *head){
        deleted = deleted->next;
    }
    //if playlist doest have the Song
    if (deleted->id != id){
        printf("Song to be deleted not found in playlist!!\n");
        return;
    }
    //playlist have only one Song
    if (deleted->next == deleted){
        *head == NULL;
    }
    else {
        deleted->prev->next = deleted->next;
        deleted->next->prev = deleted->prev;
    }
    if (deleted == *head){
        *head = deleted->next;
    }
    free(deleted);
}
// search for Song
void SearchSong(Song *head, char *title){
    if (head == NULL){
        printf("playlist is empty!!\n");
        return;
    }
    Song *curr = head;
    //head is the song
    do{
        if (strcmp(curr->title, title) == 0){
            printf("id: %d -> title: %s by %s\n", curr->id, curr->title, curr->artist);
            return;
        }
        curr = curr->next;
    }while (curr != head);
    printf("Song Not Found!!\n");
}
//display all songs
void displayPlaylist(Song *head){
    if (head == NULL){ 
        printf("playlist is empty\n");
        return;
    }
    Song *temp = head;
    do {
        printf("%d: %s by %s duration : %f \n", temp->id, temp->title, temp->artist, temp->duration);
        temp = temp->next;
    } while(temp != head);
    printf("\n");
}
//play current Song
void playCurrent(){
    if (current == NULL){
        printf("No songs in playlist!\n");
        return;
    }
    printf("Now playing: %s (Duration: %f)\n", current->title, current->duration);
}

//play next Song
void playNext(){
    current = current->next;
    playCurrent();
}
void playPrevious(){
    current = current->prev;
    playCurrent();
}
//count songs
int countSongs(Song *head){
    int count = 0;
    if (head != NULL){
        Song *temp = head;
        do {
            count++;
            head = head->next;
        } while(temp != head);
    }
    return count;
}
//delete playlist
void freePlaylist(Song **head){
    Song *temp = *head;
    Song *ptemp = NULL;
    do {
        ptemp = temp;
        temp = temp->next;
        free(ptemp);
    } while (temp != NULL);
}

int main(){
    Song *head = NULL;
    char title[50];
    char artist[50];
    float duration;
    int option;
    printf("=============Welcome to the Playlist==================\n");
    printf("0.Play Song\n1. Add Song\n2. Delete Song\n3. Search Song\n4. Show Playlist\n5. Play Next\n6. Play Previous\n7. Count Songs\n8. Exit/n");
    printf("=======================================================\n");
    while (1){
        printf("chose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 0:
                playCurrent();
                break;
            case 1:
                printf("enter titlle: ");
                scanf("%s",title);
                printf("enter artist name: ");
                scanf("%s",artist);
                printf("enter duration: ");
                scanf("%f",&duration);
                addSong(&head, title, artist, duration);
                break;
            case 2:
                int id;
                printf("enter id: ");
                scanf("%d", &id);
                deleteSong(&head, id);
                break;
            case 3:
                printf("enter title: ");
                scanf("%s", title);
                SearchSong(head, title);
                break;
            case 4:
                displayPlaylist(head);
                break;
            case 5:
                playNext();
                break;
            case 6:
                playPrevious();
                break;
            case 7:
                int count = countSongs(head);
                printf("there is %d songs in the playlist!!\n", count);
                break;
            case 8:
                freePlaylist(&head);
                return 0;                
        }   
    }
    return 0;
}
#ifndef _FUN_H_
#define _FUN_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_RESET   "\x1b[0m"

    typedef struct Patient{
        int id;
        char name[50];
        char status[50];
    }patient;

    typedef struct Rooms{
        int occupation;
        int room_num;
        struct room *priv_room;
        struct room *next_room;
        patient r_pationt;
    }room;

    room *head = NULL;

    void add_room(room **list);
    void check_empty_rooms(room *list);
    void reserv(room **list, patient data, int room_number);
    void remove_current_reservation(room **list, int room_number);
    int search_patient(room **list, int id);
    void update_patient_status(room **list, patient new_data, int location);
    void display_patient_data(room **list, int location);

#endif
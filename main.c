#include "fun.h"

int num_of_rooms = 0;

int main(){
    room room1;
    patient pat1;
    pat1.id = 123;
    pat1.name[0] = 'a';
    pat1.status[0] = 'd';
    //room1.r_pationt.id = pat1.id;
    //printf("%d\n", room1.r_pationt.id);
    printf("how many rooms in your hospital : ");
    scanf("%d", &num_of_rooms);
    add_room(&head);
    reserv(&head, pat1, 1);
    display_patient_data(&head, search_patient(&head,123));

    //printf("%d\n", search_patient(&head,123));
    //printf("%d", pat1.id);
    
    //remove_current_reservation(&head, 2);
    //printf("%d\n", search_patient(&head,123));
    /*reserv(&head, 1);
    check_empty_rooms(head);
    printf("-----------\n");
    for (int i = 1; i <= 5; i++){
        reserv(&head, i);
        check_empty_rooms(head);
        printf("-----------\n");
    }
    remove_current_reservation(&head, 1);
    check_empty_rooms(head);
    remove_current_reservation(&head, 1);*/
}

void add_room(room **list){
    //system("cls");
    room *temp = NULL;
    int i = num_of_rooms;
    while (i){
        temp = (room *)malloc(sizeof(room));
        if (temp != NULL){
            temp -> occupation = 0;
            temp -> room_num = i;
            if (*list == NULL){
                temp -> priv_room = NULL;
                temp -> next_room = NULL;
                (*list) = temp;
            }else{
                temp -> next_room = (*list);
                temp -> priv_room = NULL;
                (*list) -> priv_room = temp;
                (*list) = temp;
            }
        }else{
            printf(ANSI_COLOR_RED);
            printf("Memory err, Can not add rooms.\n");
            printf(ANSI_COLOR_RESET);
            break;
        }
        i--;
    }
    printf(ANSI_COLOR_GREEN);
    printf("%d rooms were added.\n", num_of_rooms);
    printf(ANSI_COLOR_RESET);
}

void check_empty_rooms(room *list){
    //system("cls");
    room *temp = list;
    int rooms_count = 0;
    printf("empty rooms : \n");
    while (temp){
        if (temp -> occupation == 0){
            printf("%d\n", temp -> room_num);
            rooms_count++;
        }
        temp = temp -> next_room;
    }
    if(rooms_count == 0){
        printf("NAN\n");
    }
}

void reserv(room **list, patient data, int room_number){
    room *temp = NULL;
    temp = (*list);
    int location = room_number - 1;
    while (location){
        location--;
        temp = temp -> next_room;
    }
    if (temp -> occupation == 1){
        printf(ANSI_COLOR_RED);
        printf("the room is already reserved\n");
        printf(ANSI_COLOR_RESET);
    }else{
        if(temp){
            temp -> occupation = 1;
            temp -> r_pationt.id = data.id;
            for (int i = 0; i < 50; i++){
                temp -> r_pationt.name[i] = data.name[i];
                temp -> r_pationt.status[i] = data.status[i];
            }
        }else{
            printf(ANSI_COLOR_RED);
            printf("invaled room\n");
            printf(ANSI_COLOR_RESET);
        }
    }
}

void remove_current_reservation(room **list, int room_number){
    room *temp = NULL;
    temp = (*list);
    int location = room_number - 1;
    while (location){
        location--;
        temp = temp -> next_room;
    }
    if (temp -> occupation == 0)
    {
        printf(ANSI_COLOR_RED);
        printf("the room is already free\n");
        printf(ANSI_COLOR_RESET);
    }
    else{
        if(temp){
            temp -> occupation = 0;
            temp -> r_pationt.id = 0;
            for (int i = 0; i < 50; i++){
                temp -> r_pationt.name[i] = '\0';
                temp -> r_pationt.status[i] = '\0';
            }
        }else{
            printf(ANSI_COLOR_RED);
            printf("invaled room\n");
            printf(ANSI_COLOR_RESET);
        }
    }
}

int search_patient(room **list, int id){
    room *temp = NULL;
    temp = (*list);
    int location = 1;
    while (temp){
        if (temp -> r_pationt.id == id){
            return location;
        }
        location++;
        temp = temp -> next_room;
    }
    return 0; // not found
}

void update_patient_status(room **list, patient new_data, int location){
    room *temp = NULL;
    temp = (*list);
    int pos = location - 1;
    while (temp && pos){
        pos--;
        temp = temp -> next_room;
    }
    if(temp){
        for (int i = 0; i < 50; i++){
            temp -> r_pationt.status[i] = new_data.status[i];
        }
    }else{
        printf("invaled id\n");
    }
}

void display_patient_data(room **list, int location){
    //system("cls");
    int pos = location;
    room *this_room = NULL;
    this_room = *list;
    while (pos > 1){
        this_room = this_room -> next_room;
        pos--;
    }
    printf("Patient name: %s \nPatient ID: %d \nPatient status: %s\n", this_room -> r_pationt.name, this_room -> r_pationt.id, this_room -> r_pationt.status);
}


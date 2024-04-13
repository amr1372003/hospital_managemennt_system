#include "fun.h"

int num_of_rooms = 0;

int main(){
    system("cls");
    room rooms;
    patient patients;
    int state = 0, room_num = 0, patient_id = 0, back = 0;
    printf("how many rooms in your hospital : ");
    scanf("%d", &num_of_rooms);
    add_room(&head);
    Sleep(250);
    while (state != 7){
start:
        system("cls");
        printf("choose function : \n1) Check empty rooms.\n2) Make a reservation.\n3) Remove a reservation.\n4) Search for a patient.\n5) Update patient status.\n6) Display patient data\n7) Exit\n");
        printf("enter your choice : ");
        scanf("%d", &state);

        if (state == 1){
            check_empty_rooms(&head);
            printf("1) Back : ");
            scanf("%d", &back);
            goto start;
        }else if(state == 2){
            system("cls");
            printf("which room you would like to reserv : ");
            scanf("%d", &room_num);
            printf("patient ID : ");
            scanf("%d", &patients.id);
            if(check_id(patients.id) == 0){
                printf(ANSI_COLOR_RED);
                printf("invaled ID\n");
                printf(ANSI_COLOR_RESET);
                printf("1) Back : ");
                scanf("%d", &back);
                goto start;
            }else{
                printf("patient name : ");
                scanf("%s", &patients.name);
                printf("patient status : ");
                scanf("%s", &patients.status);
                reserv(&head, patients, room_num);
            }
            printf("1) Back : ");
            scanf("%d", &back);
            goto start;
        }else if(state == 3){
            system("cls");
            printf("which room you would like to remove its reservation : ");
            scanf("%d", &room_num);
            remove_current_reservation(&head, room_num);
            printf("1) Back : ");
            scanf("%d", &back);
            goto start;
        }else if(state == 4){
            system("cls");
            printf("please enter pation ID : ");
            scanf("%d", &patient_id);
            room_num = search_patient(&head, patient_id);
            if (room_num == 0)
            {
                printf(ANSI_COLOR_RED);
                printf("invaled ID\n");
                printf(ANSI_COLOR_RESET);
            }else{
                printf("your pationt is in room %d \n", room_num);
            }
            printf("1) Back : ");
            scanf("%d", &back);
            goto start;
        }else if(state == 5){
            system("cls");
            printf("please enter pation ID : ");
            scanf("%d", &patient_id);
            room_num = search_patient(&head, patient_id);
            if (search_patient(&head, patient_id) == 0){
                printf(ANSI_COLOR_RED);
                printf("invaled ID\n");
                printf(ANSI_COLOR_RESET);
            }else{
                printf("patient new status : ");
                scanf("%s", &patients.status);
                update_patient_status(&head, patients, room_num);
            }
            printf("1) Back : ");
            scanf("%d", &back);
            goto start;
        }else if(state == 6){
            system("cls");
            printf("please enter pation ID : ");
            scanf("%d", &patient_id);
            room_num = search_patient(&head, patient_id);
            display_patient_data(&head, room_num);
            printf("1) Back : ");
            scanf("%d", &back);
            goto start;
        }
    }
}

void add_room(room **list){
    system("cls");
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

void check_empty_rooms(room **list){
    system("cls");
    room *temp = *list;
    int rooms_count = 0;
    printf("empty rooms : \n");
    while (temp){
        if (temp -> occupation == 0){
            printf("%d | ", temp -> room_num);
            rooms_count++;
        }
        temp = temp -> next_room;
    }
    if(rooms_count == 0){
        printf("NONE");
    }
    printf("\n");
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
            printf(ANSI_COLOR_GREEN);
            printf("DONE\n");
            printf(ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_GREEN);
            printf("DONE\n");
            printf(ANSI_COLOR_RESET);
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
    }
}

void display_patient_data(room **list, int location){
    system("cls");
    int pos = location;
    room *this_room = NULL;
    this_room = *list;
    while (pos > 1){
        this_room = this_room -> next_room;
        pos--;
    }
    if (this_room -> r_pationt.id != 0 && this_room -> occupation != 0 && location != 0){
        printf("Patient name: %s \nPatient ID: %d \nPatient status: %s\n", this_room -> r_pationt.name, this_room -> r_pationt.id, this_room -> r_pationt.status);
    }
    else{
        printf(ANSI_COLOR_RED);
        printf("invaled ID\n");
        printf(ANSI_COLOR_RESET);
    }
}

int check_id(int id){
    if (id < 1000000 || id > 9999999){
        return 0;
    }else{
        return 1;
    }
}


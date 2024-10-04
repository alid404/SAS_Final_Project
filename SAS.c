#include <stdio.h>
#include <string.h>

typedef struct dental {
    char first_name[100];
    char last_name[100];
    char phone_number[100];
    int age; 
    int status;
    char unique_reference[20];
    char date[20];
} dental;

void display_menu();
void Add(dental user[], int *num);
void display_reservations(dental user[], int num);
void display_one(dental user);
const char* get_status(int status);
int delete_user(dental users[], int *num, dental *userToDelete);
dental* search(dental users[], int num);
dental* search_by_id(dental users[], int num);
void filter_by_status(dental users[], int num);
void sort_name(dental users[], int num);
char* gen_id(int count);
void Statistics(dental users[], int num);
void modify_user(dental *user);

int main(void) {
    dental user[100]; 
    int num = 0; 
    int choice;

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                Add(user, &num);
                break;
            case 2: {
              printf("Searching for a reservation to modify...\n");
                dental *found_user = search(user, num);
                if (found_user != NULL) {
                     modify_user(found_user);
                }
                break; 
            }
            case 3: {
                printf("Searching for a reservation to delete...\n");
                dental *found_user = search(user, num);
                if (found_user != NULL) {
                    delete_user(user, &num, found_user);
                }
                break;
            }
            case 4:
                printf("Viewing reservation details...\n");
                display_reservations(user, num);
                break;
            case 5:
                printf("Sorting reservations by last name...\n");
                sort_name(user, num);
                break;
            case 6:
                printf("Filtering reservations by status...\n");
                filter_by_status(user, num);
                break;
            case 7: 
                printf("Searching reservations...\n");
                dental *searched_user = search(user, num);
                if (searched_user != NULL) {
                    display_one(*searched_user);
                }
                break;
            case 8: 
                printf("Searching reservations by ID...\n");
                dental *id_user = search_by_id(user, num);
                if (id_user != NULL) {
                    display_one(*id_user);
                }
                break;
            case 9:
                printf("Generating statistics...\n");
                Statistics(user, num);
                break;
            case 10:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void display_menu() {
    printf("Dental Appointment Booking System\n");
    printf("1. Add a Reservation\n");
    printf("2. Modify a Reservation\n");
    printf("3. Delete a Reservation\n");
    printf("4. View Reservation Details\n");
    printf("5. Sort Reservations by last name\n");
    printf("6. Filter Reservations by Status\n");
    printf("7. Search Reservations by name\n");
    printf("8. Search Reservations by unique reference (ID)\n");
    printf("9. Generate Statistics\n");
    printf("10. Exit\n");
    printf("Choose an option (1-10): ");
}

void Add(dental user[], int *num) {
    dental new_user; 

    strcpy(new_user.unique_reference, gen_id(*num));
    new_user.status = 1;  

    printf("Enter the first name of the user: ");
    fgets(new_user.first_name, sizeof(new_user.first_name), stdin);
    new_user.first_name[strcspn(new_user.first_name, "\n")] = 0;

    printf("Enter the last name of the user: ");
    fgets(new_user.last_name, sizeof(new_user.last_name), stdin);
    new_user.last_name[strcspn(new_user.last_name, "\n")] = 0;

    printf("Enter the phone number of the user: ");
    fgets(new_user.phone_number, sizeof(new_user.phone_number), stdin);
    new_user.phone_number[strcspn(new_user.phone_number, "\n")] = 0;

    printf("Enter the age of the user: ");
    scanf("%d", &new_user.age);
    getchar(); 

    printf("Enter the date of reservation (YYYY-MM-DD): ");
    fgets(new_user.date, sizeof(new_user.date), stdin);
    new_user.date[strcspn(new_user.date, "\n")] = 0;

    user[*num] = new_user; 
    (*num)++;
}

void display_reservations(dental user[], int num) {
    for (int i = 0; i < num; i++) {
        printf("%d. First Name: %s, Last Name: %s, Age: %d\n", 
            i + 1, user[i].first_name, user[i].last_name, user[i].age);
        printf("   Date: %s, Phone Number: %s\n", 
            user[i].date, user[i].phone_number);
        printf("   Status: %s\n", get_status(user[i].status));
        printf("   Unique Reference: %s\n", user[i].unique_reference);
    }
}

void display_one(dental user) {
    printf("First Name: %s, Last Name: %s, Age: %d\n", 
        user.first_name, user.last_name, user.age);
    printf("Date: %s, Phone Number: %s\n", 
        user.date, user.phone_number);
    printf("Status: %s\n", get_status(user.status));
}

const char* get_status(int status) {
    switch (status) {
        case 1: return "Validated";
        case 2: return "Postponed";
        case 3: return "Canceled";
        case 4: return "Processed";
        default: return "Unknown";
    }
}


void modify_user(dental *user) {
    printf("Modify the first name of the user: ");
    fgets(user->first_name, sizeof(user->first_name), stdin);
    user->first_name[strcspn(user->first_name, "\n")] = 0;

    printf("Modify the last name of the user: ");
    fgets(user->last_name, sizeof(user->last_name), stdin);
    user->last_name[strcspn(user->last_name, "\n")] = 0;

    printf("Modify the phone number of the user: ");
    fgets(user->phone_number, sizeof(user->phone_number), stdin);
    user->phone_number[strcspn(user->phone_number, "\n")] = 0;

    printf("Modify the age of the user: ");
    scanf("%d", &user->age);
    getchar(); 

    printf("Enter the date of reservation (dd-mm-yyyy): ");
    fgets(user->date, sizeof(user->date), stdin);
    user->date[strcspn(user->date, "\n")] = 0;

    printf("Current status: %s\n", get_status(user->status));
    printf("Enter new status (1-Validated, 2-Postponed, 3-Canceled, 4-Processed): ");
    scanf("%d", &user->status);
    getchar(); 
}


int delete_user(dental users[], int *num, dental *userToDelete) {
    if (userToDelete != NULL) {
        for (int i = 0; i < *num; i++) {
            if (&users[i] == userToDelete) {
                for (int j = i; j < *num - 1; j++) {
                    users[j] = users[j + 1];
                }
                printf("User has been deleted\n");
                (*num)--; 
                return 1; 
            }
        }
    }
    return 0; 
}

dental* search(dental users[], int num) {
    char name[100];
    printf("Enter the name of the user: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < num; i++) { 
        if (strcasecmp(users[i].first_name, name) == 0 || 
            strcasecmp(users[i].last_name, name) == 0) {
            return &users[i]; 
        }
    }
    printf("User not found\n");
    return NULL;
}

dental* search_by_id(dental users[], int num) {
    char id[20];
    printf("Enter the unique reference (ID): ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < num; i++) { 
        if (strcmp(users[i].unique_reference, id) == 0) {
            return &users[i]; 
        }
    }
    printf("User not found\n");
    return NULL;
}

void filter_by_status(dental users[], int num) {
    int status_choice;
    printf("Choose status to filter by:\n");
    printf("1. Validated\n");
    printf("2. Postponed\n");
    printf("3. Canceled\n");
    printf("4. Processed\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &status_choice);
    getchar(); 

    for (int i = 0; i < num; i++) {
        if (users[i].status == status_choice) {
            display_one(users[i]);
        }
    }
}

void sort_name(dental users[], int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcasecmp(users[i].last_name, users[j].last_name) > 0) {
                dental temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

char* gen_id(int count) {
    static char id[20];
    int new_count = count * 6 + 6; 
    sprintf(id, "ID%05d", new_count);
    return id;
}


void Statistics(dental users[], int num) {
    int sum = 0, x = 0, y = 0, z = 0;
    int a = 0, b = 0, c = 0, d = 0;

    for (int i = 0; i < num; i++) {
        if (users[i].age > 0 && users[i].age <= 18)
            x++;
        else if (users[i].age >= 19 && users[i].age <= 35)
            y++;
        else if (users[i].age > 35)
            z++;

        sum += users[i].age;

        switch (users[i].status) {
            case 1: a++; break;  
            case 2: b++; break; 
            case 3: c++; break;  
            case 4: d++; break;  
        }
    }

    printf("The average age of patients who booked is %.2f\n", num > 0 ? (float)sum / num : 0);
    printf("The number of patients with age from 0-18 years is %d\n", x);
    printf("The number of patients with age from 19-35 years is %d\n", y);
    printf("The number of patients with age 36+ years is %d\n", z);
    printf("The total number of validated bookings is %d, Postponed bookings is %d, Canceled bookings is %d, Processed bookings is %d\n", a, b, c, d);
}

#include <stdio.h>
#include <string.h>

typedef struct dental {
    char first_name[100];
    char last_name[100];
    char phone_number[100];
    int age; 
    int status;
    char unique_reference[20];
    char date[20];
} dental;

void display_menu();
void Add(dental user[], int *num);
void display_reservations(dental user[], int num);
void display_one(dental user);
const char* get_status(int status);
int delete_user(dental users[], int *num, dental *userToDelete);
dental* search(dental users[], int num);
dental* search_by_id(dental users[], int num);
void sort_by_status(dental users[], int num);
void sort_name(dental users[], dental sorted_users[], int num);
char* gen_id(int count, dental users[], int num);
void Statistics(dental users[], int num);
void modify_user(dental *user);

int main(void) {
    dental user[100];
    dental sorted_users[100]; 
    int num = 0; 
    int choice;

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                Add(user, &num);
                break;
            case 2: {
              printf("Searching for a reservation to modify...\n");
                dental *found_user = search(user, num);
                if (found_user != NULL) {
                     modify_user(found_user);
                }
                break; 
            }
            case 3: {
                printf("Searching for a reservation to delete...\n");
                dental *found_user = search(user, num);
                if (found_user != NULL) {
                    delete_user(user, &num, found_user);
                }
                break;
            }
            case 4:
                printf("Viewing reservation details...\n");
                display_reservations(user, num);
                break;
            case 5:
                printf("Sorting reservations by last name...\n");
                sort_name(user,sorted_users, num);
                display_reservations(sorted_users, num);
                break;
            case 6:
                printf("Sorting reservations by status...\n");
                sort_by_status(user, num);
                break;
            case 7: 
                printf("Searching reservations...\n");
                dental *searched_user = search(user, num);
                if (searched_user != NULL) {
                    display_one(*searched_user);
                }
                break;
            case 8: 
                printf("Searching reservations by ID...\n");
                dental *id_user = search_by_id(user, num);
                if (id_user != NULL) {
                    display_one(*id_user);
                }
                break;
            case 9:
                printf("Generating statistics...\n");
                Statistics(user, num);
                break;
            case 10:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void display_menu() {
    printf("Dental Appointment Booking System\n");
    printf("1. Add a Reservation\n");
    printf("2. Modify a Reservation\n");
    printf("3. Delete a Reservation\n");
    printf("4. View Reservation Details\n");
    printf("5. Sort Reservations by last name\n");
    printf("6. Filter Reservations by Status\n");
    printf("7. Search Reservations by name\n");
    printf("8. Search Reservations by unique reference (ID)\n");
    printf("9. Generate Statistics\n");
    printf("10. Exit\n");
    printf("Choose an option (1-10): ");
}

void Add(dental user[], int *num) {
    dental new_user; 

    strcpy(new_user.unique_reference, gen_id(*num, user, *num));
    new_user.status = 1;  

    printf("Enter the first name of the user: ");
    fgets(new_user.first_name, sizeof(new_user.first_name), stdin);
    new_user.first_name[strcspn(new_user.first_name, "\n")] = 0;

    printf("Enter the last name of the user: ");
    fgets(new_user.last_name, sizeof(new_user.last_name), stdin);
    new_user.last_name[strcspn(new_user.last_name, "\n")] = 0;

    printf("Enter the phone number of the user: ");
    fgets(new_user.phone_number, sizeof(new_user.phone_number), stdin);
    new_user.phone_number[strcspn(new_user.phone_number, "\n")] = 0;

    printf("Enter the age of the user: ");
    scanf("%d", &new_user.age);
    getchar(); 

    printf("Enter the date of reservation (YYYY-MM-DD): ");
    fgets(new_user.date, sizeof(new_user.date), stdin);
    new_user.date[strcspn(new_user.date, "\n")] = 0;

    user[*num] = new_user; 
    (*num)++;
}

void display_reservations(dental user[], int num) {
    for (int i = 0; i < num; i++) {
        printf("%d. First Name: %s, Last Name: %s, Age: %d\n", 
            i + 1, user[i].first_name, user[i].last_name, user[i].age);
        printf("   Date: %s, Phone Number: %s\n", 
            user[i].date, user[i].phone_number);
        printf("   Status: %s\n", get_status(user[i].status));
        printf("   Unique Reference: %s\n", user[i].unique_reference);
    }
}

void display_one(dental user) {
    printf("First Name: %s, Last Name: %s, Age: %d\n", 
        user.first_name, user.last_name, user.age);
    printf("Date: %s, Phone Number: %s\n", 
        user.date, user.phone_number);
    printf("Status: %s\n", get_status(user.status));
}

const char* get_status(int status) {
    switch (status) {
        case 1: return "Validated";
        case 2: return "Postponed";
        case 3: return "Canceled";
        case 4: return "Processed";
        default: return "Unknown";
    }
}


void modify_user(dental *user) {
    printf("Modify the first name of the user: ");
    fgets(user->first_name, sizeof(user->first_name), stdin);
    user->first_name[strcspn(user->first_name, "\n")] = 0;

    printf("Modify the last name of the user: ");
    fgets(user->last_name, sizeof(user->last_name), stdin);
    user->last_name[strcspn(user->last_name, "\n")] = 0;

    printf("Modify the phone number of the user: ");
    fgets(user->phone_number, sizeof(user->phone_number), stdin);
    user->phone_number[strcspn(user->phone_number, "\n")] = 0;

    printf("Modify the age of the user: ");
    scanf("%d", &user->age);
    getchar(); 

    printf("Enter the date of reservation (dd-mm-yyyy): ");
    fgets(user->date, sizeof(user->date), stdin);
    user->date[strcspn(user->date, "\n")] = 0;

    printf("Current status: %s\n", get_status(user->status));
    printf("Enter new status (1-Validated, 2-Postponed, 3-Canceled, 4-Processed): ");
    scanf("%d", &user->status);
    getchar(); 
}


int delete_user(dental users[], int *num, dental *userToDelete) {
    if (userToDelete != NULL) {
        for (int i = 0; i < *num; i++) {
            if (&users[i] == userToDelete) {
                for (int j = i; j < *num - 1; j++) {
                    users[j] = users[j + 1];
                }
                printf("User has been deleted\n");
                (*num)--; 
                return 1; 
            }
        }
    }
    return 0; 
}

dental* search(dental users[], int num) {
    char name[100];
    printf("Enter the name of the user: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < num; i++) { 
        if (strcasecmp(users[i].first_name, name) == 0 || 
            strcasecmp(users[i].last_name, name) == 0) {
            return &users[i]; 
        }
    }
    printf("User not found\n");
    return NULL;
}

dental* search_by_id(dental users[], int num) {
    char id[20];
    printf("Enter the unique reference (ID): ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < num; i++) { 
        if (strcmp(users[i].unique_reference, id) == 0) {
            return &users[i]; 
        }
    }
    printf("User not found\n");
    return NULL;
}

void sort_by_status(dental users[], int num) {
    int status_choice;
    printf("Choose status to filter by:\n");
    printf("1. Validated\n");
    printf("2. Postponed\n");
    printf("3. Canceled\n");
    printf("4. Processed\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &status_choice);
    getchar(); 

    for (int i = 0; i < num; i++) {
        if (users[i].status == status_choice) {
            display_one(users[i]);
        }
    }
}

void sort_name(dental users[], dental sorted_users[], int num) {
    for (int i = 0; i < num; i++) {
        sorted_users[i] = users[i];
    }
    for (int i = 0; i < num - 1; i++) {
        for (int j = i + 1; j < num; j++) {
            if (strcasecmp(sorted_users[i].last_name, sorted_users[j].last_name) > 0) {
                dental temp = sorted_users[i];
                sorted_users[i] = sorted_users[j];
                sorted_users[j] = temp;
            }
        }
    }
}


char* gen_id(int count, dental users[], int num) {
    static char id[20];
    int new_count = count * 6 + 6; 
    sprintf(id, "ID%05d", new_count);

    for (int i = 0; i < num; i++) {
        if (strcmp(users[i].unique_reference, id) == 0) {
            return gen_id(count + 1, users, num); 
        }
    }

    return id; 
}



void Statistics(dental users[], int num) {
    int sum = 0, x = 0, y = 0, z = 0;
    int a = 0, b = 0, c = 0, d = 0;

    for (int i = 0; i < num; i++) {
        if (users[i].age > 0 && users[i].age <= 18)
            x++;
        else if (users[i].age >= 19 && users[i].age <= 35)
            y++;
        else if (users[i].age > 35)
            z++;

        sum += users[i].age;

        switch (users[i].status) {
            case 1: a++; break;  
            case 2: b++; break; 
            case 3: c++; break;  
            case 4: d++; break;  
        }
    }

    printf("The average age of patients who booked is %.2f\n", num > 0 ? (float)sum / num : 0);
    printf("The number of patients with age from 0-18 years is %d\n", x);
    printf("The number of patients with age from 19-35 years is %d\n", y);
    printf("The number of patients with age 36+ years is %d\n", z);
    printf("The total number of validated bookings is %d, Postponed bookings is %d, Canceled bookings is %d, Processed bookings is %d\n", a, b, c, d);
}

void data(dental user[], int *size) {
    strcpy(user[*size].first_name, "bilal");
    strcpy(user[*size].last_name, "ohio");
    strcpy(user[*size].phone_number, "0612332435");
    user[*size].age = 22;
    user[*size].status = 4; 
    strcpy(user[*size].unique_reference, "02");
    strcpy(user[*size].date, "2023-12-28");
    (*size)++;

    strcpy(user[*size].first_name, "mouad");
    strcpy(user[*size].last_name, "solo");
    strcpy(user[*size].phone_number, "06123456922");
    user[*size].age = 22;
    user[*size].status = 1; 
    strcpy(user[*size].unique_reference, "03");
    strcpy(user[*size].date, "2024-10-21");
    (*size)++;

    strcpy(user[*size].first_name, "Morad");
    strcpy(user[*size].last_name, "Ahmed");
    strcpy(user[*size].phone_number, "0623295678");
    user[*size].age = 22;
    user[*size].status = 2; 
    strcpy(user[*size].unique_reference, "04");
    strcpy(user[*size].date, "2024-01-20");
    (*size)++;

    strcpy(user[*size].first_name, "salma");
    strcpy(user[*size].last_name, "dala");
    strcpy(user[*size].phone_number, "061299278");
    user[*size].age = 22;
    user[*size].status = 3; 
    strcpy(user[*size].unique_reference, "05");
    strcpy(user[*size].date, "2024-03-20");
    (*size)++;

    strcpy(user[*size].first_name, "reda");
    strcpy(user[*size].last_name, "msali");
    strcpy(user[*size].phone_number, "061347777728");
    user[*size].age = 22;
    user[*size].status = 4; 
    strcpy(user[*size].unique_reference, "06");
    strcpy(user[*size].date, "2024-10-03");
    (*size)++;

    strcpy(user[*size].first_name, "Ayoub");
    strcpy(user[*size].last_name, "hilaoui");
    strcpy(user[*size].phone_number, "0610929288");
    user[*size].age = 22;
    user[*size].status = 2; 
    strcpy(user[*size].unique_reference, "07");
    strcpy(user[*size].date, "2023-02-08");
    (*size)++;

    strcpy(user[*size].first_name, "omar");
    strcpy(user[*size].last_name, "bari");
    strcpy(user[*size].phone_number, "06257339178");
    user[*size].age = 22;
    user[*size].status = 4; 
    strcpy(user[*size].unique_reference, "08");
    strcpy(user[*size].date, "2024-11-01");
    (*size)++;

    strcpy(user[*size].first_name, "hannibal");
    strcpy(user[*size].last_name, "lion");
    strcpy(user[*size].phone_number, "06122344338");
    user[*size].age = 22;
    user[*size].status = 2; 
    strcpy(user[*size].unique_reference, "09");
    strcpy(user[*size].date, "2023-04-22");
    (*size)++;

    strcpy(user[*size].first_name, "badr");
    strcpy(user[*size].last_name, "ibiks");
    strcpy(user[*size].phone_number, "0607385678");
    user[*size].age = 22;
    user[*size].status = 2; 
    strcpy(user[*size].unique_reference, "10");
    strcpy(user[*size].date, "2024-02-08");
    (*size)++;
}


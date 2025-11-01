#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Wel_Mes(void) {
    printf("\t\t  Welcome To ' Yalla Ticket ' Application\n\n");
    printf("\t\t\033[1;33mThis Program was developed by Achievers Team\033[0m\n");
}

int choices(const char* mes[], const char* options[], int n) {
    int choice;
    printf("\n%s\n", mes);

    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }


    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > n)  printf("\033[1;31mInvalid choise, \033[0mPlease Try again :");
    } while (choice < 1 || choice > n);

    return choice - 1;
}

void Book_Ticket(int num) {
    FILE *fptr = fopen("Tick.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char name[40], id[20];
    for (int i = 0; i < num; i++) {
        if (num > 1) printf("\033[1;33m\t--Passenger [%d] data --\033[0m\n", i + 1);
        printf("Enter Name: ");
        while (getchar() != '\n');
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        printf("Enter your 14-digit National ID: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;
        while (strlen(id) != 14) {
            printf("\033[1;31mInvalid ID, it must be 14 digits.\033[0m\n");
            printf("Enter your 14-digit National ID: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = 0;
        }

        const char* Countries[] = {"Egypt", "France", "USA"};
        const char* Egy_Air[] = {"Cairo International Airport", "Alexandria Airport", "Sharm El Sheikh Airport"};
        const char* Fra_Air[] = {"Charles de Gaulle", "Orly", "Nice Cote d'Azur"};
        const char* Usa_Air[] = {"JFK", "LAX", "Chicago O'Hare"};
        const char* date[] = {"20/05/2025 | 10:00 Am" , "21/05/2025 | 10:00 Am", "22/05/2025 | 10:00 Am", "23/05/2025 | 10:00 Am", "24/05/2025 | 10:00 Am"};

        int des_c = choices("Choose destination Country :", Countries, 3);
        int dep_air;

        switch (des_c) {
            case 0: dep_air = choices("Choose Airport :", Egy_Air, 3); break;
            case 1: dep_air = choices("Choose Airport :", Fra_Air, 3); break;
            case 2: dep_air = choices("Choose Airport :", Usa_Air, 3); break;
        }





        int flight_date = choices("Choose Flight Date : ", date, 5);




        // Save to file
        fprintf(fptr, "\tPassenger %d:\nName: %s\nID: %s\nFlight Date : %s\nCountry: %s\nAirport: ", i + 1, name, id, date[flight_date], Countries[des_c]);
        switch (des_c) {
            case 0: fprintf(fptr, "%s", Egy_Air[dep_air]); break;
            case 1: fprintf(fptr, "%s", Fra_Air[dep_air]); break;
            case 2: fprintf(fptr, "%s", Usa_Air[dep_air]); break;
        }
        fprintf(fptr, "\n----------------------\n");
    }

    fclose(fptr);

    printf("\033[1;32mYour flight has been booked successfully.\033[0m\n");
    printf("Thank You For Using Our application Yalla Ticket\n");
    printf("Please arrive at the airport at least 2 hours before your flight.\n");
}

void Cancel_Ticket() {
    FILE *fptr = fopen("Tick.txt", "r");
    if (fptr == NULL) {
        printf("\033[1;33mNo booking found to cancel.\033[0m\n");
        return;
    }
    fclose(fptr);
    remove("Tick.txt");
    printf("\033[1;33mYour booking has been canceled successfully.\033[0m\n");
}

void View_Ticket() {
    FILE *fptr = fopen("Tick.txt", "r");
    if (fptr == NULL) {
        printf("\033[1;33mNo ticket found.\033[0m\n");
        return;
    }

    printf("\t\033[1;34m--- Your Ticket Details ---\033[0m\n");
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    fclose(fptr);
}








int main() {
    int choice;
    Wel_Mes();

    do {
        printf("\n ---- Main Menu ---- \n");
        printf("1. Book a Flight\n2. Cancel a Flight\n3. View a Ticket\n4. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int n;
                printf("\nNumber of Tickets: ");
                scanf("%d", &n);
                if (n > 0) Book_Ticket(n);
                break;
            }
            case 2: Cancel_Ticket(); break;
            case 3: View_Ticket(); break;
            case 4: printf("Exiting the program...\n"); break;
            default: printf("\033[1;31mInvalid Choise, Try again..\033[0m\n");
        }
    } while (choice != 4);

    return 0;
}

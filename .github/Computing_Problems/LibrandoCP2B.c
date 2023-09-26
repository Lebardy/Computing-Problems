// Jan Angel H. Librando
// CSS - 4 - B
// Date Started: September 6, 2023
// Date Finished: September 6, 2023
// changes the implementation of cp1 from array of structures to singly linked list
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <stdbool.h>

#define name 64

typedef struct record
{
    char lastname[name];
    char firstname[name];
    float height;
    float weight;
    float bmi;
    char category[name];
} rec;

typedef struct sllnode *nd;
struct sllnode
{
    rec record;
    nd next;
} NODE;

char menu();
void input(nd *head);
rec data(nd *head, bool *check);
bool duplicate_check(nd *head, rec record);
float bmi(float height, float weight);
char *type(float bmi);
nd search(nd *head);
void display_record(nd *head);
void display_all(nd *head);
void gotoxy(short x, short y);
void quit(void);

int main(void)
{
    nd head = NULL;
    char choice;

    do
    {
        choice = menu();
        choice = tolower(choice);

        switch (choice)
        {
        case 'a':
            system("cls");
            input(&head);
            break;

        case 'b':
            system("cls");
            display_record(&head);
            break;

        case 'c':
            system("cls");
            display_all(&head);
            break;

        case 'd':
            system("cls");
            quit();
            break;

        default:
            printf("\n\nInvald Input! Please try again.");
            printf("\nPress Enter to Continue");
            getch();
            break;
        }
    } while (choice != 'd');
}

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

char menu()
{
    char choice;
    int valid = 0;
    do
    {
        system("cls");

        printf("\t\tMenu");
        printf("\nA. Add New Record");
        printf("\nB. Search for Record");
        printf("\nC. Display All Records");
        printf("\nD. Exit this Program");

        printf("\n\nChoice: ");
        scanf(" %c", &choice);

        if (isalpha(choice))
        {
            valid = 1;
        }

        if (valid == 0)
        {
            printf("\n\nInvalid Choice. Please Try Again.\n");
            getch();
        }
    } while (!valid);

    return choice;
}

void input(nd *head)
{
    // sll variables
    nd h = *head, p = NULL, temp = NULL;

    // user variable
    rec record;

    // bool var
    bool dupCheck = false;

    record = data(&h, &dupCheck);

    if (dupCheck == true)
    {
        printf("\n\n");
        printf("Duplicate Detected. Please Try again");
        getch();

        return;
    }

    if (h == NULL)
    {
        h = malloc(sizeof(NODE));
        h->next = NULL;

        h->record = record;

        *head = h;

        return;
    }

    temp = malloc(sizeof(NODE));
    temp->next = NULL;

    temp->record = record;

    p = h;

    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = temp;

    return;
}

rec data(nd *head, bool *dupCheck)
{
    rec record;
    nd h = *head;
    bool duplicate = *dupCheck;
    char ln[name], fn[name];
    char *category;
    float height, weight, BMI;
    int i;

    printf("Enter Details");

    fflush(stdin);

    // Last Name
    printf("\n\n\tLast Name: ");
    fgets(ln, sizeof(ln), stdin);
    ln[strcspn(ln, "\n")] = 0;
    ln[0] = toupper(ln[0]);
    for (i = 1; i < strlen(ln); i++)
    {
        ln[i] = tolower(ln[i]);
    }
    strcpy(record.lastname, ln);

    printf("\tFirst Name: ");
    fgets(fn, sizeof(fn), stdin);
    ln[strcspn(fn, "\n")] = 0;
    fn[0] = toupper(fn[0]);
    for (i = 1; i < strlen(fn); i++)
    {
        fn[i] = tolower(fn[i]);
    }
    strcpy(record.firstname, fn);

    // duplicate trap
    duplicate = duplicate_check(&h, record);

    if (duplicate == true)
    {
        *dupCheck = duplicate;
        return record;
    }

    printf("\tHeight(cm): ");
    scanf("%f", &height);
    record.height = height;

    printf("\tWeight(lb): ");
    scanf("%f", &weight);
    record.weight = weight;

    BMI = bmi(height, weight);
    record.bmi = BMI;

    category = type(BMI);
    strcpy(record.category, category);

    return record;
}

bool duplicate_check(nd *head, rec record)
{
    nd h = *head;

    while (h != NULL)
    {
        if (strcmp(h->record.lastname, record.lastname) != 0 && strcmp(h->record.firstname, record.firstname) != 0)
        {
            h = h->next;
        }

        else
        {
            // when duplicate is found
            return true;
        }
    }

    // when no duplicates is found
    return false;
}

float bmi(float height, float weight)
{
    float meters = 0, kilograms = 0;

    meters = height / 100;

    kilograms = weight * 0.45359237;

    return kilograms / (meters * meters);
}

char *type(float bmi)
{
    static char assessment[name];

    if (bmi < 18.5)
    {
        strcpy(assessment, "Underweight");
    }

    if (bmi >= 18.5 && bmi < 24.9)
    {
        strcpy(assessment, "Normal Weight");
    }

    if (bmi >= 25 && bmi < 29.9)
    {
        strcpy(assessment, "Overweight");
    }

    if (bmi > 30)
    {
        strcpy(assessment, "Obese");
    }

    return assessment;
}

void display_record(nd *head)
{

    nd h = *head;
    nd p = NULL;

    // search for record
    p = search(&h);

    printf("\n");

    if (p == NULL)
    {
        printf("No record found. Please try again");
        getch();

        return;
    }

    printf("%s, ", p->record.lastname);
    printf("%s", p->record.firstname);
    printf("\nHeight: %.2f centimeters", p->record.height);
    printf("\nWeight: %.2f pounds", p->record.weight);
    printf("\nYour BMI is %.2f and you are %s", p->record.bmi, p->record.category);

    printf("\n\nPress any key to continue");
    getch();

    return;
}

nd search(nd *head)
{
    nd p = *head;
    char ln[name], fn[name];

    fflush(stdin);
    printf("Last Name: ");
    fgets(ln, sizeof(ln), stdin);
    ln[strcspn(ln, "\n")] = '\0';

    printf("First Name: ");
    fgets(fn, sizeof(fn), stdin);
    fn[strcspn(fn, "\n")] = '\0';

    // traverses list of matches
    while (p != NULL)
    {
        if ((strcmpi(p->record.lastname, ln) != 0) && (strcmpi(p->record.firstname, fn) != 0))
        {
            p = p->next;
        }

        else
        {
            // match is found
            return p;
        }
    }

    // returns NULL if no matches
    return p;
}

void display_all(nd *head)
{
    int x = 2, y = 1;
    nd current = *head;

    if (current == NULL)
    {
        printf("No Available Records. Press Enter to Continue");
        getch();
        return;
    }

    // Print headers
    gotoxy(x, y);
    printf("Last Name");
    x += 20;
    gotoxy(x, y);
    printf("First Name");
    x += 20;
    gotoxy(x, y);
    printf("Height(CM)");
    x += 20;
    gotoxy(x, y);
    printf("Weight(lb)");
    x += 20;
    gotoxy(x, y);
    printf("BMI");
    x += 20;
    gotoxy(x, y);
    printf("Category");
    y += 2;

    // Print all records
    while (current != NULL)
    {
        x = 2;
        gotoxy(x, y);
        printf("%s", current->record.lastname);
        x += 20;

        gotoxy(x, y);
        printf("%s", current->record.firstname);
        x += 20;

        gotoxy(x, y);
        printf("%.2f", current->record.height);
        x += 20;

        gotoxy(x, y);
        printf("%.2f", current->record.weight);
        x += 20;

        gotoxy(x, y);
        printf("%.2f", current->record.bmi);
        x += 20;

        gotoxy(x, y);
        printf("%s", current->record.category);
        y++;

        current = current->next;
    }

    x = 1;
    y += 3;

    gotoxy(x, y);
    printf("Press Enter To Continue");
    getch();
}

void quit(void)
{
    printf("Exiting Program! Press Enter to Continue");
    getch();
}

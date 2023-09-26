// Jan Angel Librando
// CSS 4 - B
// Date Started: September 13, 2023
// Date Finished: September 13, 2023
// Summary: converts CP2 into a doubly-linked list implementation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

#define name 50

typedef struct record
{
    char lastname[name];
    char firstname[name];
    float height;
    float weight;
    float bmi;
    char category[name];
} rec;

typedef struct dllnode *nd;
struct dllnode
{
    rec record;
    nd left;
    nd right;
} node;

char menu();
void AddNode(nd *head);
rec data(nd *head, bool *check);
bool duplicate_check(nd *head, rec record);
float bmi(float height, float weight);
char *type(float bmi);
nd search(nd *head);
void display_record(nd *head);
void display_all(nd *head);
void display_list(nd *head);
void edit_record(nd *head);
void delete_record(nd *head);
void quit(void);

int main(void)
{
    nd head = NULL;
    char choice;

    do
    {
        choice = menu();

        switch (choice)
        {
        case 'a':
            system("cls");
            AddNode(&head);
            break;

        case 'b':
            system("cls");
            display_record(&head);
            break;

        case 'c':
            system("cls");
            edit_record(&head);
            break;

        case 'd':
            system("cls");
            delete_record(&head);
            break;

        case 'e':
            system("cls");
            display_all(&head);
            break;

        case 'f':
            system("cls");
            quit();
            break;

        default:
            printf("\n\nInvalid Input! Please try again\n");
            printf("\nPress Enter to Continue");
            getch();
            break;
        }

    } while (choice != 'f');

    return 0;
}

void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

char menu()
{
    char choice;
    bool valid = false;

    do
    {
        system("cls");

        printf("\t\tMenu");
        printf("\nA. Add new record");
        printf("\nB. Search for a record");
        printf("\nC. Search and edit a record");
        printf("\nD. Delete a record");
        printf("\nE. Display all records");
        printf("\nF. Quit this program");

        printf("n\nChoice: ");
        scanf(" %c", &choice);

        valid = isalpha(choice);

        if (valid == false)
        {
            printf("\n\nInvalid Choice. Please enter try again.\n");
            getch();
        }

    } while (valid == false);

    return tolower(choice);
}

void AddNode(nd *head)
{
    // dll variables
    nd h = *head, p = NULL, temp = NULL;

    // user variable
    rec record;

    // bool variable exist
    bool dupCheck = false;

    record = data(&h, &dupCheck);

    if (dupCheck == true)
    {
        printf("\n\n");
        printf("Duplicate Detected. Please Try Again");
        getch();

        return;
    }

    if (h == NULL)
    {
        h = malloc(sizeof(node));
        h->left = NULL;
        h->right = NULL;
        h->record = record;

        *head = h;

        return;
    }

    temp = malloc(sizeof(node));
    temp->left = NULL;
    temp->right = NULL;
    temp->record = record;

    p = h;

    // traverse list
    while (p->right != NULL)
    {
        p = p->right;
    }

    // add node at the end of the list
    p->right = temp;
    temp->left = p;

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
            h = h->right;
        }

        else
        {
            return true;
        }
    }

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

    if (bmi >= 50 && bmi < 29.9)
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

    if (p == NULL)
    {
        return;
    }

    int x = 2, y = 5;
    // headers;
    gotoxy(x, y);
    printf("\tPrevious Node");
    x += 50;
    gotoxy(x, y);
    printf("\tCurrent Node");
    x += 50;
    gotoxy(x, y);
    printf("\tNext Node");

    // previous Node
    x = 2;
    if (p->left == NULL)
    {
        y = 8;
        gotoxy(x, y);
        printf("\tNo Available Record");
        x += 50;
    }

    else
    {
        x = 2;
        y = 8;
        p = p->left;
        gotoxy(x, y);
        printf("%s, ", p->record.lastname);
        y++;
        gotoxy(x, y);
        printf("%s", p->record.firstname);
        y++;
        gotoxy(x, y);
        printf("Height: %.2f centimeters", p->record.height);
        y++;
        gotoxy(x, y);
        printf("Weight: %.2f pounds", p->record.weight);
        y++;
        gotoxy(x, y);
        printf("Your BMI is %.2f and you are %s", p->record.bmi, p->record.category);
        x += 50;
    }

    // Current Node
    y = 8;
    gotoxy(x, y);
    printf("%s, ", p->record.lastname);
    y++;
    gotoxy(x, y);
    printf("%s", p->record.firstname);
    y++;
    gotoxy(x, y);
    printf("Height: %.2f centimeters", p->record.height);
    y++;
    gotoxy(x, y);
    printf("Weight: %.2f pounds", p->record.weight);
    y++;
    gotoxy(x, y);
    printf("Your BMI is %.2f and you are %s", p->record.bmi, p->record.category);
    x += 50;

    // Next Node
    if (p->right == NULL)
    {
        y = 8;
        gotoxy(x, y);
        printf("\tNo Available Record");
        x += 50;
    }

    else
    {
        y = 8;
        p = p->right;
        gotoxy(x, y);
        printf("%s, ", p->record.lastname);
        y++;
        gotoxy(x, y);
        printf("%s", p->record.firstname);
        y++;
        gotoxy(x, y);
        printf("Height: %.2f centimeters", p->record.height);
        y++;
        gotoxy(x, y);
        printf("Weight: %.2f pounds", p->record.weight);
        y++;
        gotoxy(x, y);
        printf("Your BMI is %.2f and you are %s", p->record.bmi, p->record.category);
        x += 50;
    }

    x = 2;
    y = 15;
    gotoxy(x, y);
    printf("\n\nPress any key to continue");
    getch();

    return;
}

nd search(nd *head)
{
    nd p = *head;
    char choice;
    char ln[name], fn[name];

    do
    {
        system("cls");
        fflush(stdin);
        printf("Last Name: ");
        fgets(ln, sizeof(ln), stdin);
        ln[strcspn(ln, "\n")] = '\0';

        printf("First Name: ");
        fgets(fn, sizeof(fn), stdin);
        fn[strcspn(fn, "\n")] = '\0';

        // traverses list of matches
        while (p != NULL && (strcmpi(p->record.lastname, ln) != 0 && strcmpi(p->record.firstname, ln) != 0))
        {
            p = p->right;
        }

        printf("\n");

        if (p != NULL)
        {
            printf("Record Found\n\n");
        }

        if (p == NULL)
        {
            printf("No record found\n\n");
        }

        printf("Do you want to proceed(Y/N): ");
        scanf(" %c", &choice);
    } while (tolower(choice) != 'y');

    if (tolower(choice) == 'y')
    {
        system("cls");
        printf("Last Name: %s", ln);
        printf("\nFirst Name: %s", fn);
    }

    if (tolower(choice) == 'n')
    {
        return NULL;
    }

    return p;
}

void edit_record(nd *head)
{
    nd h = *head;
    nd p = NULL;
    float height, weight;
    char *category;
    char choice;

    p = search(&h);

    if (p == NULL)
    {
        return;
    }

    do
    {
        system("cls");
        // display record
        printf("Details: ");
        printf("\n\tLast Name: %s", p->record.lastname);
        printf("\n\tFirst Name: %s", p->record.firstname);
        printf("\n\tHeight: %.2f cm", p->record.height);
        printf("\n\tWeight: %.2f lb", p->record.weight);
        printf("\n\tBMI: %.2f", p->record.bmi);
        printf("\n\tCategory: %s", p->record.category);

        printf("\n\nDo you want to edit this record(Y/N): ");
        scanf(" %c", &choice);

        if (tolower(choice) == 'y')
        {
            printf("Record Changes: ");
            printf("\n\tHeight(cm): ");
            scanf(" %f", &height);
            p->record.height = height;
            printf("\n\tWeight(lb): ");
            scanf(" %f", &weight);
            p->record.weight = weight;

            p->record.bmi = bmi(height, weight);
            category = type(p->record.bmi);
            strcpy(p->record.category, category);

            system("cls");
            printf("Changed Record: ");
            printf("\n\tLast Name: %s, ", p->record.lastname);
            printf("\n\tFirst Name: %s", p->record.firstname);
            printf("\n\tHeight: %.2f", p->record.height);
            printf("\n\tWeight: %.2f", p->record.weight);
            printf("\n\tCategory: %s", p->record.category);

            printf("\n\nPress Enter to Return to Menu");
            getch();
        }

        else if (tolower(choice) == 'n')
        {
            printf("\n\nRecord is unchanged");
            printf("\nReturning to Menu");
            return;
        }

        else if (tolower(choice) != 'n' && tolower(choice) != 'y')
        {
            printf("\nInvalid Choice. Please try again");
            getch();
        }
    } while (isdigit(choice));

    return;
}

void delete_record(nd *head)
{
    nd h = *head, p = NULL;
    char choice;

    p = search(&h);

    if (p == NULL)
    {
        return;
    }

    do
    {
        system("cls");
        printf("Details: ");
        printf("\n\tLast Name: %s", p->record.lastname);
        printf("\n\tFirst Name: %s", p->record.firstname);
        printf("\n\tHeight: %.2f cm", p->record.height);
        printf("\n\tWeight: %.2f cm", p->record.weight);
        printf("\n\tBMI: %.2f", p->record.bmi);
        printf("\n\tCategory: %s", p->record.category);

        printf("\n\nDo You Want to Delete this Record(Y/N): ");
        scanf(" %c", &choice);

        if (tolower(choice) == 'y')
        {
            printf("\n\nRecord Deleted");

            if (p->left == NULL)
            {
                if (p->right != NULL)
                {
                    p->right->left = NULL;
                }

                h = p->right;
                *head = h;
                free(p);
            }

            else if (p->right == NULL)
            {
                p->left->right = NULL;

                free(p);

                *head = h;
            }

            else if (p->left != NULL && p->right != NULL)
            {
                p->left->right = p->right;
                p->right->left = p->left;
                free(p);

                *head = h;
            }

            if (h == NULL)
            {
                printf("\n\nAll Records Deleted");
                printf("\nPress Enter to return to the Menu");
                getch();
                return;
            }

            else
            {
                system("cls");
                display_list(&h);
                printf("\n\nThe List after changes");
                printf("\nPress Enter to return to Menu");
                getch();
                return;
            }
        }

        if (tolower(choice) == 'n')
        {
            printf("\n\nDeletion  Cancelled");
            printf("\nPress Enter to return to the Menu");
            return;
        }

        else
        {
            printf("Invalid Input. Press Enter to Try Again");
            getch();
        }
    } while (isdigit(choice)); // trap if user inputs a number instead of a letter
}

void display_list(nd *head)
{
    int x = 2, y = 1;
    nd current = *head;

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

        current = current->right;
    }
}

void display_all(nd *head)
{
    int x = 2, y = 3;
    nd current = *head;
    int counter = 0;

    if (current == NULL)
    {
        printf("No Available Records. Press Enter to Continue");
        getch();
        return;
    }

    printf("Normal List: ");

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

        current = current->right;
        counter++;
    }
    x = 1;
    y += 3;
    gotoxy(x, y);
    printf("Number of Nodes: %d", counter);
    y += 2;
    gotoxy(x, y);
    printf("Press Enter to See a Reversed List");
    getch();

    system("cls");
    x = 2, y = 3;

    printf("Reversed List: ");

    // move to the last node
    current = *head;
    while (current != NULL && current->right != NULL)
    {
        current = current->right;
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

        current = current->left;
    }

    x = 1;
    y += 3;

    gotoxy(x, y);
    printf("Press Enter To Continue");
    getch();

    return;
}

void quit(void)
{
    printf("Exiting Program! Press Enter to Continue");
    getch();
}
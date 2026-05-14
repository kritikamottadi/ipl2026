#include <stdio.h>
#include <stdlib.h>

// Structure definition (one record)
struct student {
    int id;
    char name[20];
};


// 🔹 FUNCTION 1: WRITE RECORDS TO FILE
void writeRecords() {
    FILE *fp;
    int n, i;

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Open file in write binary mode
    fp = fopen("data.dat", "wb");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    struct student s;  // temporary variable

    for (i = 0; i < n; i++) {
        printf("Enter id and name: ");
        scanf("%d %s", &s.id, s.name);

        // Write one record at a time
        fwrite(&s, sizeof(s), 1, fp);
    }

    fclose(fp);
    printf("Records stored successfully!\n");
}


// 🔹 FUNCTION 2: FETCH m-th RECORD USING fseek
void fetchRecord() {
    FILE *fp;
    int m;

    fp = fopen("data.dat", "rb");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter record number to fetch: ");
    scanf("%d", &m);

    struct student s;

    // Move file pointer to m-th record
    fseek(fp, (m-1) * sizeof(s), SEEK_SET);

    // Read that record
    fread(&s, sizeof(s), 1, fp);

    printf("Record found: %d %s\n", s.id, s.name);

    fclose(fp);
}


// 🔹 FUNCTION 3: DELETE m-th RECORD
void deleteRecord() {
    FILE *fp, *temp;
    int m, count = 0;

    fp = fopen("data.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter record number to delete: ");
    scanf("%d", &m);

    struct student s;

    // Read each record one by one
    while (fread(&s, sizeof(s), 1, fp)) {
        count++;

        // Skip the record to delete
        if (count != m) {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    // Replace old file with new file
    remove("data.dat");
    rename("temp.dat", "data.dat");

    printf("Record deleted successfully!\n");
}


// 🔹 MAIN FUNCTION (MENU DRIVEN)
int main() {
    int choice;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Write Records\n");
        printf("2. Fetch m-th Record\n");
        printf("3. Delete m-th Record\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                writeRecords();
                break;

            case 2:
                fetchRecord();
                break;

            case 3:
                deleteRecord();
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
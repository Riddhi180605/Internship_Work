#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_ID "Riddhi"
#define ADMIN_PASS "1865"

struct Account {
    int accNo;
    char name[30];
    float balance;
};

int accountExists(int accNo);
int adminLogin();

int main() {
    int roleChoice;

    while (1) {
        printf("\n\n===== BANKING SYSTEM =====");
        printf("\n1. Admin");
        printf("\n2. User");
        printf("\n0. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &roleChoice);

        if (roleChoice == 1) {
            if (!adminLogin()) {
                printf("\nToo many failed attempts. Program exiting.\n");
                exit(0);
            }

            int adminChoice;
            while (1) {
                printf("\n\n===== ADMIN MENU =====");
                printf("\n1. Create Account");
                printf("\n2. Display All Accounts");
                printf("\n3. Search Account");
                printf("\n4. Delete Account");
                printf("\n0. Logout");
                printf("\nEnter choice: ");
                scanf("%d", &adminChoice);

                if (adminChoice == 1) {
                    FILE *fp;
                    struct Account a;

                    printf("\nEnter Account Number: ");
                    scanf("%d", &a.accNo);

                    if (accountExists(a.accNo)) {
                        printf("\nAccount number already exists!");
                        continue;
                    }

                    printf("Enter Name: ");
                    scanf("%s", a.name);
                    printf("Enter Initial Balance: ");
                    scanf("%f", &a.balance);

                    fp = fopen("bank.dat", "ab");
                    if (fp == NULL) {
                        printf("\nFile error!");
                        continue;
                    }

                    fwrite(&a, sizeof(a), 1, fp);
                    fclose(fp);
                    printf("\nAccount Created Successfully!");

                } else if (adminChoice == 2) {
                    FILE *fp;
                    struct Account a;

                    fp = fopen("bank.dat", "rb");
                    if (fp == NULL) {
                        printf("\nNo records found!");
                        continue;
                    }

                    printf("\nAccNo\tName\tBalance");
                    printf("\n----------------------------");
                    while (fread(&a, sizeof(a), 1, fp)) {
                        printf("\n%d\t%s\t%.2f", a.accNo, a.name, a.balance);
                    }
                    fclose(fp);

                } else if (adminChoice == 3) {
                    FILE *fp;
                    struct Account a;
                    int acc, found = 0;

                    fp = fopen("bank.dat", "rb");
                    if (fp == NULL) {
                        printf("\nFile not found!");
                        continue;
                    }

                    printf("\nEnter Account Number: ");
                    scanf("%d", &acc);

                    while (fread(&a, sizeof(a), 1, fp)) {
                        if (a.accNo == acc) {
                            printf("\nAccount Found");
                            printf("\nName: %s", a.name);
                            printf("\nBalance: %.2f", a.balance);
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                        printf("\nAccount Not Found!");

                    fclose(fp);

                } else if (adminChoice == 4) {
                    FILE *fp, *temp;
                    struct Account a;
                    int acc, found = 0;

                    fp = fopen("bank.dat", "rb");
                    temp = fopen("temp.dat", "wb");

                    if (fp == NULL || temp == NULL) {
                        printf("\nFile error!");
                        continue;
                    }

                    printf("\nEnter Account Number to Delete: ");
                    scanf("%d", &acc);

                    while (fread(&a, sizeof(a), 1, fp)) {
                        if (a.accNo != acc)
                            fwrite(&a, sizeof(a), 1, temp);
                        else
                            found = 1;
                    }

                    fclose(fp);
                    fclose(temp);

                    remove("bank.dat");
                    rename("temp.dat", "bank.dat");

                    if (found)
                        printf("\nAccount Deleted Successfully!");
                    else
                        printf("\nAccount Not Found!");

                } else if (adminChoice == 0) {
                    break;
                } else {
                    printf("\nInvalid choice!");
                }
            }

        } else if (roleChoice == 2) {
            int userChoice;

            while (1) {
                printf("\n\n===== USER MENU =====");
                printf("\n1. Deposit");
                printf("\n2. Withdraw");
                printf("\n3. Check Balance");
                printf("\n4. Transfer Money");
                printf("\n0. Back");
                printf("\nEnter choice: ");
                scanf("%d", &userChoice);

                if (userChoice == 1) {
                    FILE *fp;
                    struct Account a;
                    int acc;
                    float amt;

                    fp = fopen("bank.dat", "rb+");
                    if (fp == NULL) {
                        printf("\nFile not found!");
                        continue;
                    }

                    printf("\nEnter Account Number: ");
                    scanf("%d", &acc);
                    printf("Enter Amount: ");
                    scanf("%f", &amt);

                    while (fread(&a, sizeof(a), 1, fp)) {
                        if (a.accNo == acc) {
                            a.balance += amt;
                            fseek(fp, -sizeof(a), SEEK_CUR);
                            fwrite(&a, sizeof(a), 1, fp);
                            printf("\nDeposit Successful!");
                            break;
                        }
                    }
                    fclose(fp);

                } else if (userChoice == 2) {
                    FILE *fp;
                    struct Account a;
                    int acc;
                    float amt;

                    fp = fopen("bank.dat", "rb+");
                    if (fp == NULL) {
                        printf("\nFile not found!");
                        continue;
                    }

                    printf("\nEnter Account Number: ");
                    scanf("%d", &acc);
                    printf("Enter Amount: ");
                    scanf("%f", &amt);

                    while (fread(&a, sizeof(a), 1, fp)) {
                        if (a.accNo == acc) {
                            if (a.balance >= amt) {
                                a.balance -= amt;
                                fseek(fp, -sizeof(a), SEEK_CUR);
                                fwrite(&a, sizeof(a), 1, fp);
                                printf("\nWithdraw Successful!");
                            } else {
                                printf("\nInsufficient Balance!");
                            }
                            break;
                        }
                    }
                    fclose(fp);

                } else if (userChoice == 3) {
                    FILE *fp;
                    struct Account a;
                    int acc;

                    fp = fopen("bank.dat", "rb");
                    if (fp == NULL) {
                        printf("\nFile not found!");
                        continue;
                    }

                    printf("\nEnter Account Number: ");
                    scanf("%d", &acc);

                    while (fread(&a, sizeof(a), 1, fp)) {
                        if (a.accNo == acc) {
                            printf("\nCurrent Balance: %.2f", a.balance);
                            break;
                        }
                    }
                    fclose(fp);

                } else if (userChoice == 4) {
                    FILE *fp;
                    struct Account a1, a2;
                    int from, to;
                    float amt;
                    long pos1 = -1, pos2 = -1;

                    fp = fopen("bank.dat", "rb+");
                    if (fp == NULL) {
                        printf("\nFile not found!");
                        continue;
                    }

                    printf("\nFrom Account: ");
                    scanf("%d", &from);
                    printf("To Account: ");
                    scanf("%d", &to);
                    printf("Amount: ");
                    scanf("%f", &amt);

                    while (fread(&a1, sizeof(a1), 1, fp)) {
                        if (a1.accNo == from) {
                            pos1 = ftell(fp) - sizeof(a1);
                            break;
                        }
                    }

                    rewind(fp);
                    while (fread(&a2, sizeof(a2), 1, fp)) {
                        if (a2.accNo == to) {
                            pos2 = ftell(fp) - sizeof(a2);
                            break;
                        }
                    }

                    if (pos1 == -1 || pos2 == -1) {
                        printf("\nAccount not found!");
                        fclose(fp);
                        continue;
                    }

                    if (a1.balance < amt) {
                        printf("\nInsufficient balance!");
                        fclose(fp);
                        continue;
                    }

                    a1.balance -= amt;
                    a2.balance += amt;

                    fseek(fp, pos1, SEEK_SET);
                    fwrite(&a1, sizeof(a1), 1, fp);
                    fseek(fp, pos2, SEEK_SET);
                    fwrite(&a2, sizeof(a2), 1, fp);

                    printf("\nTransfer Successful!");
                    fclose(fp);

                } else if (userChoice == 0) {
                    break;
                } else {
                    printf("\nInvalid choice!");
                }
            }

        } else if (roleChoice == 0) {
            printf("\nThank you for using the Banking System.\n");
            exit(0);
        } else {
            printf("\nInvalid choice!");
        }
    }
    return 0;
}

int accountExists(int accNo) {
    FILE *fp;
    struct Account a;

    fp = fopen("bank.dat", "rb");
    if (fp == NULL)
        return 0;

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int adminLogin() {
    char id[20], pass[20];
    int attempts = 3;

    while (attempts--) {
        printf("\nEnter Admin ID: ");
        scanf("%s", id);
        printf("Enter Password: ");
        scanf("%s", pass);

        if (strcmp(id, ADMIN_ID) == 0 && strcmp(pass, ADMIN_PASS) == 0)
            return 1;

        printf("\nInvalid credentials! Attempts left: %d\n", attempts);
    }
    return 0;
}

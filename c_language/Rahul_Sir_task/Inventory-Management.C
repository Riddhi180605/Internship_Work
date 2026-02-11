#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

struct Product {
    int id;
    char name[50];
    char category[30];
    int quantity;
    float price;
    int active;
};

struct Product products[SIZE];
int count = 0;

int login();
void addProduct();
void displayProducts();
void searchProduct();
void sortByPrice();
void updateProduct();
void deleteProduct();

int main() {
    int choice;

    if (!login()) {
        printf("\nAccess Denied. Exiting program...\n");
        return 0;
    }

    do {
        printf("\n\n------> PRODUCT INVENTORY MANAGEMENT <------");
        printf("\n1. Add Product");
        printf("\n2. Display All Products");
        printf("\n3. Search Product by ID");
        printf("\n4. Sort Products by Price");
        printf("\n5. Update Product By ID");
        printf("\n6. Delete Product By ID");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); 
                    break;
            case 2: displayProducts(); 
                    break;
            case 3: searchProduct(); 
                    break;
            case 4: sortByPrice(); 
                    break;
            case 5: updateProduct(); 
                    break;
            case 6: deleteProduct(); 
                    break;
            case 0: printf("\nProgram terminated.\n"); 
                    break;
            default: printf("\nInvalid choice.. Please select a valid choice.\n");
        }

    } while (choice != 0);

    return 0;
}

/* Login Function */
int login() {
    char username[20], password[20];
    int attempts = 0;

    while (attempts < 3) {
        printf("\nLOGIN :-");
        printf("\n\tUsername: ");
        scanf("%s", username);
        printf("\tPassword: ");
        scanf("%s", password);

        if (strcmp(username, "Riddhi") == 0 &&
            strcmp(password, "1865") == 0) {
            printf("\nLogin Successful!\n");
            return 1;
        } else {
            attempts++;
            printf("\nInvalid credentials. Attempts left: %d\n",
                   3 - attempts);
        }
    }
    return 0;
}

/* Add Product */
void addProduct() {
    if (count >= SIZE) {
        printf("\nInventory full!\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &products[count].id);
    printf("Enter Product Name: ");
    scanf("%s", products[count].name);
    printf("Enter Category: ");
    scanf("%s", products[count].category);
    printf("Enter Quantity: ");
    scanf("%d", &products[count].quantity);
    printf("Enter Price: ");
    scanf("%f", &products[count].price);

    products[count].active = 1;
    count++;

    printf("\nProduct added successfully.\n");
}

/* Display Products */
void displayProducts() {
    int i, found = 0;

    printf("\nID\tName\tCategory\tQty\tPrice");
    printf("\n--------------------------------------------");

    for (i = 0; i < count; i++) {
        if (products[i].active == 1) {
            printf("\n%d\t%s\t%s\t\t%d\t%.2f",
                   products[i].id,
                   products[i].name,
                   products[i].category,
                   products[i].quantity,
                   products[i].price);
            found = 1;
        }
    }

    if (!found)
        printf("\nNo active products found.\n");
}

/* Search Product by ID */
void searchProduct() {
    int id, i;

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (products[i].id == id && products[i].active == 1) {
            printf("\nProduct Found");
            printf("\nName: %s", products[i].name);
            printf("\nCategory: %s", products[i].category);
            printf("\nQuantity: %d", products[i].quantity);
            printf("\nPrice: %.2f\n", products[i].price);
            return;
        }
    }
    printf("\nProduct not found.\n");
}

/* Sort Products by Price */
void sortByPrice() {
    int i,j,sort;
    if(count == 0){
        printf("\nList of Student records are empty.\n");
        return;
    }
    printf("\nHow do you want to sort the array?");
    printf("\n1. Accending Order");
    printf("\n2. Descending Order");
    printf("\nChoice :- ");
    scanf("%d" , &sort);
    struct Product temp;
    while (1)
    {    
        if(sort==1){
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    if (products[i].active && products[j].active &&
                        products[i].price > products[j].price) {
                        temp = products[i];
                        products[i] = products[j];
                        products[j] = temp;
                    }
                }
            }
            break;
        }
        else if(sort==2){
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    if (products[i].active && products[j].active &&
                        products[i].price < products[j].price) {
                        temp = products[i];
                        products[i] = products[j];
                        products[j] = temp;
                    }
                }
            }
            break;
        }
        else
        {
            printf("Enter Valid Choice");
            break;
        }
    }
    
    printf("\nProducts sorted by price (ascending).\n");
    displayProducts();
}

/* Update Product */
void updateProduct() {
    int id, i;

    printf("\nEnter Product ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (products[i].id == id && products[i].active == 1) {
            printf("Enter new Name: ");
            scanf("%s", products[i].name);
            printf("Enter new Category: ");
            scanf("%s", products[i].category);
            printf("Enter new Quantity: ");
            scanf("%d", &products[i].quantity);
            printf("Enter new Price: ");
            scanf("%f", &products[i].price);

            printf("\nProduct updated successfully.\n");
            return;
        }
    }
    printf("\nProduct not found.\n");
}

/* Delete Product */
void deleteProduct() {
    int id, i;

    printf("\nEnter Product ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (products[i].id == id && products[i].active == 1) {
            products[i].active = 0;
            printf("\nProduct deleted successfully.\n");
            return;
        }
    }
    printf("\nProduct not found.\n");
}

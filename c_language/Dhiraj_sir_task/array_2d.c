#include<stdio.h>
#include<stdlib.h>

#define Row 30
#define Col 30

int a[Row][Col], b[Row][Col], c[Row][Col]={0};
int sortedarray[Row][Col];
int arr[Row*Col];

int r1,r2,c1,c2;
int choice,choice1;
int i,j,k;
int temp,exc;
int key;

/* ---------- Function Declaration ---------- */
void menu();
void scanarray();
void displayarray();
void add();
void sub();
void mul();
void division();
void Searchkey();

void bubbleSort();
void selectionSort();
void insertionSort();
void mergeSortWrapper();
void quickSortWrapper();

void mergeSort(int l,int r);
void merge(int l,int m,int r);
void quickSort(int low,int high);
int partition(int low,int high);

/* ---------- MAIN ---------- */
void main(){
    scanarray();
    displayarray();

    while(1){
        menu();
        printf("\nEnter choice (1-7): ");
        scanf("%d",&choice);

        switch(choice){
            case 1: add(); break;
            case 2: sub(); break;
            case 3: mul(); break;
            case 4: division(); break;

            case 5:
                printf("\n1. Bubble Sort");
                printf("\n2. Selection Sort");
                printf("\n3. Insertion Sort");
                printf("\n4. Merge Sort");
                printf("\n5. Quick Sort");
                printf("\nEnter sorting choice: ");
                scanf("%d",&choice1);

                switch(choice1){
                    case 1: bubbleSort(); break;
                    case 2: selectionSort(); break;
                    case 3: insertionSort(); break;
                    case 4: mergeSortWrapper(); break;
                    case 5: quickSortWrapper(); break;
                    default: printf("\nInvalid sorting choice!");
                }
                break;

            case 6: Searchkey(); break;
            case 7: exit(0);
            default: printf("\nInvalid choice!");
        }
    }
}

/* ---------- MENU ---------- */
void menu(){
    printf("\n-----------------------------------------");
    printf("\n1. Addition");
    printf("\n2. Subtraction");
    printf("\n3. Multiplication");
    printf("\n4. Division");
    printf("\n5. Sorting");
    printf("\n6. Searching");
    printf("\n7. Exit");
    printf("\n-----------------------------------------");
}

/* ---------- SCAN ---------- */
void scanarray(){
    printf("\nEnter rows & cols for first matrix: ");
    scanf("%d %d",&r1,&c1);
    printf("\nEnter rows & cols for second matrix: ");
    scanf("%d %d",&r2,&c2);

    if(r1>30 || c1>30 || r2>30 || c2>30){
        printf("\nSize exceeds limit!");
        exit(0);
    }

    printf("\nEnter first matrix elements:\n");
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            scanf("%d",&a[i][j]);

    printf("\nEnter second matrix elements:\n");
    for(i=0;i<r2;i++)
        for(j=0;j<c2;j++)
            scanf("%d",&b[i][j]);
}

/* ---------- DISPLAY ---------- */
void displayarray(){
    printf("\nFirst Matrix:\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++)
            printf("%d\t",a[i][j]);
        printf("\n");
    }

    printf("\nSecond Matrix:\n");
    for(i=0;i<r2;i++){
        for(j=0;j<c2;j++)
            printf("%d\t",b[i][j]);
        printf("\n");
    }
}

/* ---------- ADD ---------- */
void add(){
    if(r1==r2 && c1==c2){
        for(i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                c[i][j]=a[i][j]+b[i][j];
                printf("%d\t",c[i][j]);
            }
            printf("\n");
        }
    } else printf("\nAddition not possible");
}

/* ---------- SUB ---------- */
void sub(){
    if(r1==r2 && c1==c2){
        for(i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                c[i][j]=a[i][j]-b[i][j];
                printf("%d\t",c[i][j]);
            }
            printf("\n");
        }
    } else printf("\nSubtraction not possible");
}

/* ---------- MUL ---------- */
void mul(){
    if(c1==r2){
        for(i=0;i<r1;i++)
            for(j=0;j<c2;j++)
                c[i][j]=0;

        for(i=0;i<r1;i++){
            for(j=0;j<c2;j++){
                for(k=0;k<c1;k++)
                    c[i][j]+=a[i][k]*b[k][j];
                printf("%d\t",c[i][j]);
            }
            printf("\n");
        }
    } else printf("\nMultiplication not possible");
}

/* ---------- DIV ---------- */
void division(){
    if(r1==r2 && c1==c2){
        for(i=0;i<r1;i++){
            for(j=0;j<c1;j++){
                if(b[i][j]!=0)
                    printf("%d\t",a[i][j]/b[i][j]);
                else
                    printf("0\t");
            }
            printf("\n");
        }
    } else printf("\nDivision not possible");
}

/* ---------- SEARCH ---------- */
void Searchkey(){
    printf("\n1. Linear Search");
    printf("\n2. Binary Search");
    printf("\nEnter choice: ");
    scanf("%d", &choice1);

    if(choice1 == 1){
        printf("\nEnter key: ");
        scanf("%d", &key);

        for(i = 0; i < r1; i++){
            for(j = 0; j < c1; j++){
                if(a[i][j] == key){
                    printf("\nKey found at row %d col %d", i, j);
                    return;
                }
            }
        }
        printf("\nKey not found");
    }

    else if(choice1 == 2){
        printf("\nEnter key: ");
        scanf("%d", &key);

        bubbleSort();  

        for(i = 0; i < r1; i++){
            int low = 0, high = c1 - 1;
            while(low <= high){
                int mid = (low + high) / 2;

                if(sortedarray[i][mid] == key){
                    printf("\nKey found at row %d col %d", i, mid);
                    return;
                }
                else if(key < sortedarray[i][mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
        }
        printf("\nKey not found");
    }
    else{
        printf("Enter valid number(1 or 2).");
    }
}

/* ---------- BUBBLE SORT ---------- */
void bubbleSort(){
    int total=r1*c1;
    exc=1; k=0;

    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            arr[k++]=a[i][j];

    for(i=0;i<total-1 && exc;i++){
        exc=0;
        for(j=0;j<total-1-i;j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j]; arr[j]=arr[j+1]; arr[j+1]=temp;
                exc=1;
            }
        }
    }

    k=0;
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            sortedarray[i][j]=arr[k++];

    printf("\nSorted Matrix (Bubble Sort):\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++)
            printf("%d\t",sortedarray[i][j]);
        printf("\n");
    }
}

/* ---------- SELECTION SORT ---------- */
void selectionSort(){
    int total=r1*c1; k=0;

    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            arr[k++]=a[i][j];

    for(i=0;i<total-1;i++){
        int min=i;
        for(j=i+1;j<total;j++)
            if(arr[j]<arr[min]) min=j;
        temp=arr[i]; arr[i]=arr[min]; arr[min]=temp;
    }

    k=0;
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            sortedarray[i][j]=arr[k++];

    printf("\nSorted Matrix (Selection Sort):\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++)
            printf("%d\t",sortedarray[i][j]);
        printf("\n");
    }
}

/* ---------- INSERTION SORT ---------- */
void insertionSort(){
    int total=r1*c1; k=0;

    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            arr[k++]=a[i][j];

    for(i=1;i<total;i++){
        temp=arr[i];
        j=i-1;
        while(j>=0 && arr[j]>temp){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }

    k=0;
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            sortedarray[i][j]=arr[k++];

    printf("\nSorted Matrix (Insertion Sort):\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++)
            printf("%d\t",sortedarray[i][j]);
        printf("\n");
    }
}

/* ---------- MERGE SORT ---------- */
void merge(int l,int m,int r){
    int tempArr[Row*Col];
    int i=l,j=m+1,k=l;

    while(i<=m && j<=r){
        if(arr[i]<=arr[j]) tempArr[k++]=arr[i++];
        else tempArr[k++]=arr[j++];
    }
    while(i<=m) tempArr[k++]=arr[i++];
    while(j<=r) tempArr[k++]=arr[j++];

    for(i=l;i<=r;i++)
        arr[i]=tempArr[i];
}

void mergeSort(int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(l,m);
        mergeSort(m+1,r);
        merge(l,m,r);
    }
}

void mergeSortWrapper(){
    int total=r1*c1; k=0;

    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            arr[k++]=a[i][j];

    mergeSort(0,total-1);

    k=0;
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            sortedarray[i][j]=arr[k++];

    printf("\nSorted Matrix (Merge Sort):\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++)
            printf("%d\t",sortedarray[i][j]);
        printf("\n");
    }
}

/* ---------- QUICK SORT ---------- */
int partition(int low,int high){
    int pivot=arr[high];
    int i=low-1;
    for(j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            temp=arr[i]; arr[i]=arr[j]; arr[j]=temp;
        }
    }
    temp=arr[i+1]; arr[i+1]=arr[high]; arr[high]=temp;
    return i+1;
}

void quickSort(int low,int high){
    if(low<high){
        int pi=partition(low,high);
        quickSort(low,pi-1);
        quickSort(pi+1,high);
    }
}

void quickSortWrapper(){
    int total=r1*c1; k=0;

    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            arr[k++]=a[i][j];

    quickSort(0,total-1);

    k=0;
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            sortedarray[i][j]=arr[k++];

    printf("\nSorted Matrix (Quick Sort):\n");
    for(i=0;i<r1;i++){
        for(j=0;j<c1;j++)
            printf("%d\t",sortedarray[i][j]);
        printf("\n");
    }
}

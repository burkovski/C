#include <stdio.h>
#include <stdlib.h>

#define ArraySize 500

typedef struct{
    char name[100];
	char address[100];
	unsigned int phone;
}CouchSurfing;

void menu()
{
	printf("+--------[Menu]------+\n");
	printf("| #1  Add new record |\n");
	printf("| #2  Remove record  |\n");
	printf("| #3  Search product |\n");
	printf("| #4  Change product |\n");
	printf("| #5  All  products  |\n");
	printf("| #6  Sort products  |\n");
	printf("+--------------------+\n");
	printf("\n-> Press any other key to Exit\n");
	printf("\n-> Choose the number of operation:\n");
}

int charToInt(char *string)         //Ïåðåâîäèòü ñòðîêó ñèìâîë³â ó ö³ëå ÷èñëî
{
    int i,j,len;
    unsigned int k = 0;

    for(len = 0;string[len];len++);

    for(i = len-1,j = 1;i >= 0;i--)
    {
        k += ((*(string+i))-48)*j;
        j*=10;
    }
    return k;
}

void NewProduct(CouchSurfing *element,int *sizePtr)
{
    int charToInt(char *);

    if(*sizePtr >= ArraySize-1)
        printf("-> Database is already full...\n");
    else
    {
        int i = *sizePtr+1;
        char tmpPrice[100], *tmpPricePtr;
        printf("-> Add new record(Name, Adress, Phone:\n>> ");
        scanf("%s%s%s",(element+i)->device,(element+i)->model,tmpPrice);
        tmpPricePtr = tmpPrice;
        (element+i)->price = charToInt(tmpPricePtr);
        (*sizePtr)++;
    }
}

void AllProducts(CouchSurfing *element,int *sizePtr)
{
    if(*sizePtr >= 0)
    {
        int i;
        for(i=0;i<=*sizePtr;i++)
            printf(" %d %s %s %u\n",i+1,(element+i)->device,(element+i)->model,(element+i)->price);
    }
    else
        printf("-> No elements to show yet, please first add record...\n");
}

void RemoveProduct(CouchSurfing *element,int *sizePtr)
{
    if(*sizePtr >= 0)
    {
        int i = 0;
        char scan[20];
        AllProducts(element,sizePtr);
        printf("-> Input index to remove\n>>");
        scanf("%s",scan);
        i = (scan[0])-48;
        if(i < 1 || i > *sizePtr+1)
        {
            printf("-> Invalid index...\n");
        }
        else
        {
            for(i;i <= *sizePtr;i++)
                element[i-1] = element[i];
                (*sizePtr)--;
                printf("-> Removing completed\n");
        }
    }
    else
        printf("-> No elements to remove yet, please first add product...\n");
}

int strstrF(const char *string1,const char *string2)            //Ïîøóê ï³äñòðîêè â ñòðîö³
{
    int i,j,len1,len2;

    for(len1 = 0;string1[len1];len1++);
    for(len2 = 0;string2[len2];len2++);

    for(i = 0;i <= len1 - len2;i++)
    {
        for(j = 0;string1[i + j] == string2[j];j++);

        if((j - len2 == 1 && i == len1 - len2) || j == len2)
            return i;
    }
    return -1;
}

void SearchProduct(CouchSurfing *element,int *sizePtr)
{
    int strcmpF(const char *,const char *);
    int strstrF(const char *,const char *);

    if(*sizePtr >= 0)
    {
        int i,j = 0,r = 0,h = 0,k = 0,n = 0;
        char searchData[100];
        char *searchDataPtr = searchData;
        printf("-> Input data to search\n>> ");
        scanf("%s",searchData);
        printf("-> Results:\n");
        for(i = 0;i <= *sizePtr;i++)
        {
            r = strcmpF((element+i)->device,searchDataPtr);
            h = strcmpF((element+i)->model,searchDataPtr);
            if(r == 0 || h == 0)
            {
                printf(" %d %s %s %u\n",i+1,(element+i)->device,(element+i)->model,(element+i)->price);
                j++;
            }
            else
            {
                k = strstrF((element+i)->device,searchDataPtr);
                n = strstrF((element+i)->model,searchDataPtr);
                if(k >= 0 || n >= 0)
                {
                    printf(" %d %s %s %u\n",i+1,(element+i)->device,(element+i)->model,(element+i)->price);
                    j++;
                }
            }
        }
        if(j == 0)
            printf("-> There are no records that match your search! ");
    }
    else
        printf("-> Nothing to search yet, please first add record! \n");
}

void ChangeProduct(CouchSurfing *element,int *sizePtr)
{
    void changeDevice(CouchSurfing *,int *);
    void changeModel(CouchSurfing *,int *);
    void changePrice(CouchSurfing *,int *);

    if(*sizePtr >= 0)
    {
        char scan[20];
        int choice = 0;
		printf("-> #1 Edit name\n");
		printf("-> #2 Edit address\n");
		printf("-> #3 Phone\n");
        printf("-> Press any other key to cansel\n");
        void(*f[3])(CouchSurfing *,int *) = {changeDevice,changeModel,changePrice};
        scanf("%s",scan);
        choice = (scan[0])-48;

        if(choice > 0 && choice < 4)
        {
            AllProducts(element,sizePtr);
            printf("-> Input index to edit\n>>");
            (*f[choice-1])(element,sizePtr);
        }
        else
            printf("-> Edit canceled\n");
    }
    else
        printf("-> No elements to change yet, please first add record! \n");
}

void changeDevice(CouchSurfing *element,int *sizePtr)
{
    int i = 0;
    char scan[20];
    scanf("%s",scan);
    i = (scan[0])-48;
    if(i < 1 || i > *sizePtr+1)
    {
        printf("-> Invalid index! \n");
    }
    else
    {
        printf("-> Input new data\n>>");
        scanf("%s",(element+i-1)->device);
        printf("-> Change completed\n");
    }
}

void changeModel(CouchSurfing *element,int *sizePtr)
{
    int i = 0;
    char scan[20];
    scanf("%s",scan);
    i = (scan[0])-48;
    if(i < 1 || i > *sizePtr+1)
    {
        printf("-> Invalid index! \n");
    }
    else
    {
        printf("-> Put new data\n>>");
        scanf("%s",(element+i-1)->model);
        printf("-> Change completed\n");
    }
}

void changePrice(CouchSurfing *element,int *sizePtr)
{
    int charToInt(char *);

    int i = 0;
    char scan[20], tmpPrice[100], *tmpPricePtr;
    scanf("%s",scan);
    i = (scan[0])-48;
    if(i < 1 || i > *sizePtr+1)
    {
        printf("-> Invalid index! \n");
    }
    else
    {
        printf("-> Put new data\n>>");
        scanf("%s",tmpPrice);
        tmpPricePtr = tmpPrice;
        (element+i-1)->price = charToInt(tmpPricePtr);
        printf("-> Change completed! \n");
    }
}




void QuickSort(CouchSurfing *element,int *sizePtr)
{
    void sortDevice(CouchSurfing *,int);
    void sortModel(CouchSurfing *,int);
    void sortPrice(CouchSurfing *,int);

    if(*sizePtr >= 0)
    {

        char scan[20];
        int choice = 0, size = *sizePtr;
		printf("-> #1 Sort by name\n");
		printf("-> #2 Sort by address\n");
		printf("-> #3 Sort by telephone\n");
        printf("-> Press any other key to cansel\n");
        void(*f[3])(CouchSurfing *,int) = {sortDevice,sortModel,sortPrice};
        scanf("%s",scan);
        choice = (scan[0])-48;

        if(choice > 0 && choice < 4)
        {
            (*f[choice-1])(element,size);
            printf("-> Sorted successfully! \n");
        }
        else
            printf("-> Sort canceled! \n");
    }
    else
        printf("-> Nothing to sort yet, please first add record! \n");
}

int strcmpF(const char *a,const char *b)
{
    return (*a == *b && *b) ? strcmpF(a+1, b+1) : (*a - *b);
}

void sortDevice(CouchSurfing *element,int size)
{
    int strcmpF(const char *,const char *);

    int i = 0,j = size;
    CouchSurfing tmp,x = element[size / 2];

    do{
        while (strcmpF((element+i)->device,x.device) < 0) i++;
        while (strcmpF((element+j)->device,x.device) > 0) j--;
        if(i <= j)
            {
                tmp = element[i];
                element[i] = element[j];
                element[j] = tmp;
                i++;
                j--;
            }
       }while(i <= j);

    if(j > 0)
        sortDevice(element,j);
    if(size > i)
        sortDevice(element+i,size-i);
}

void sortModel(CouchSurfing *element,int size)
{
    int strcmpF(const char *,const char *);

    int i = 0,j = size;
    CouchSurfing tmp,x = element[size / 2];

    do{
        while (strcmpF((element+i)->model,x.model) < 0) i++;
        while (strcmpF((element+j)->model,x.model) > 0) j--;
        if(i <= j)
            {
                tmp = element[i];
                element[i] = element[j];
                element[j] = tmp;
                i++;
                j--;
            }
       }while(i <= j);

    if(j > 0)
        sortDevice(element,j);
    if(size > i)
        sortDevice(element+i,size-i);
}

void sortPrice(CouchSurfing *element,int size)
{
    int i = 0,j = size;
    CouchSurfing tmp;
    unsigned int x = element[j / 2].price;

    do{
        while ((element+i)->price > x) i++;
        while ((element+j)->price < x) j--;
        if(i <= j)
            {
                tmp = element[i];
                element[i] = element[j];
                element[j] = tmp;
                i++;
                j--;
            }
       }while(i <= j);

    if(j > 0)
        sortPrice(element,j);
    if(size > i)
        sortPrice(element+i,size-i);
}

void menu();
void NewProduct(CouchSurfing *,int *);                     //ïðîòîòèïè ôóíêö³é
void RemoveProduct(CouchSurfing *,int *);
void SearchProduct(CouchSurfing *,int *);
void ChangeProduct(CouchSurfing *,int *);
void AllProducts(CouchSurfing *,int *);
void QuickSort(CouchSurfing *,int *);

main()
{
    int size = -1,choice = 0,*sizePtr;
    CouchSurfing shoparray[ArraySize];
    sizePtr = &size;
    void(*f[6])(CouchSurfing *,int *) = {NewProduct, RemoveProduct, SearchProduct, ChangeProduct, AllProducts, QuickSort};
    menu();
    scanf("%d",&choice);
        while(choice > 0 && choice < 7)
        {
            (*f[choice-1])(shoparray,sizePtr);
            menu();
            choice = 0;
            scanf("%d",&choice);
        }
        printf("\n Exit...\n");
    return 0;
}
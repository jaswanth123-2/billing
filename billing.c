#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct customer
{
  char num[12];
  char name[30];
  int visit;
}customer;

typedef struct items
{
  char name[20];
  int cost;
  char quantity[10];
  int rfid;
  int stock;
}itm;
struct bill
{
    int cost;
    int quantity;
    char name[30];
    char info[10];
}bil[1000];
int nop=0;
void cus();
void memship(char mnum[]);
void mobile_check (int visit);
void choice();
void stockreduction(int amt,int rd,int i);
void stockincriment(int inc,int rfid);
void creatproduct();
void inc_exist();
void delet_item();
void see(char name[] );
void list();

void cus()
{
    customer *c1;
    printf("To ensure quality service we would like to take the store of your visit Pls enter your mobile number!! : ");
    FILE *fp;
    char mnum[12];
    fp = fopen("Customer.txt","r");

    scanf("%s",mnum);
    while(fread(c1,sizeof(customer),1,fp))
    {
        if(strcmp(c1->num,mnum)==0)
        {
            printf ("customer name : %s\n",c1->name);
            printf ("customer mobile number : %s\n",c1->num);
            memship(mnum);
            printf("Number of visit : %d",c1->visit+1);
            mobile_check (c1->visit+1);
            break;
        }
    }
    fclose(fp);
    fp = fopen("Customer.txt","a");

        if(strcmp(c1->num,mnum)!=0)
        {
        customer *c2;
        c2 = (customer*)calloc(1,sizeof(customer));
        printf ("Enter customer name : ");
        scanf("%s",c2->name);
        strcpy(c2->num , mnum);
        c2->visit=0;
        fwrite(c2,sizeof(customer),1,fp);
        }

}
/*-----------------------------------------------------------*/
void memship(char mnum[])
{
    customer c1;
    FILE *fp,*fp1;
    int founnd=0;
    fp = fopen("Customer.txt","r");
    fp1= fopen("temp.txt","w");
    while(fread(&c1,sizeof(customer),1,fp))
    {
        if(strcmp(c1.num,mnum)==0)
        {
            founnd = 1;
            c1.visit=c1.visit+1;
        }
        fwrite(&c1,sizeof(customer),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if (founnd=1)
    {
        fp = fopen("Customer.txt","w");
        fp1= fopen("temp.txt","r");
        while(fread(&c1,sizeof(customer),1,fp1))
        {
            fwrite(&c1,sizeof(customer),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
}

/*-----------------------------------------------------------*/
void mobile_check (int visit)
{

      if (visit < 5)
        {
    printf ("\nMembership tier: GOLD\n");
        }
      else if (visit >= 5 && visit < 10)
        {
    printf ("\nMembership tier:SILVER\n");
        }
      else if (visit >= 10)
        {
    printf ("\nMembership tier:PLATINUM\n");
        }

}
/*-----------------------------------------------------------*/
void choice()
{
    FILE *f1;
    int rd,*rd1=&rd;
    itm it;
    int ch=0;
    int found;
    FILE *bi;
    int i=0;
    do
    {
        found=0;
        printf("\nEnter RFID : ");
        scanf("%d",rd1);
        f1 = fopen("product.txt","r");
        while(fread(&it,sizeof(itm),1,f1))
        {

            if(it.rfid==*rd1)
            {
                printf("\nPRODUCT  : %s\nQUANTITY : %s\nCOST     : Rs.%d",it.name,it.quantity,it.cost);
                found=1;
                printf("\nEnter 1 to add to cart  \nEnter 2 to exit \n");
                printf("Enter choice : ");
                scanf("%d",&ch);

                if(ch==1)
                {
                    printf("How many number of %s would you like to add to cart : ",it.name);
                    int amt;
                    scanf("%d",&amt);
                    if(amt>it.stock)
                    {
                        printf("\n\nOOPSE!!\nWe have only %d items in %s",it.stock,it.name);
                        printf("\nHow many number of %s would you like to add to cart : ",it.name);
                        scanf("%d",&amt);
                    }
                    stockreduction(amt,rd,i);
                    i++;
                    nop++;
                    printf("\n\nEnter 1 to continue\nEnter 0 to end shopping\n");
                    printf("Enter choice : ");
                    scanf("%d",&ch);

                    break;
                }

            }

        }
        if (found==0)
                {
                    printf("OOPSE!!!\nREENTER CORRECT RFID");
                    rd=0;
                    ch=1 ;
                }


    }while(ch!=0);
    fclose(f1);
}
/*------------------------------------------------------*/
void stockreduction(int amt,int rd,int i)
{
    FILE *f1,*fp;
    itm it;
    int found=0;
    int ch;
    f1 = fopen("product.txt","r");
    fp = fopen("ptemp.txt","w");
    while(fread(&it,sizeof(itm),1,f1))
        {
            if(rd==it.rfid)
            {
                found=1;
                it.stock = it.stock - amt;
                strcpy(bil[i].name,it.name);
                bil[i].cost=it.cost*amt;
                bil[i].quantity=amt;
                strcpy(bil[i].info,it.quantity);
            }
            fwrite(&it,sizeof(itm),1,fp);
        }
    fclose(fp);
    fclose(f1);
    if (found==1)
    {
        f1 = fopen("product.txt","w");
        fp = fopen("ptemp.txt","r");
        while(fread(&it,sizeof(itm),1,fp))
        {
            fwrite(&it,sizeof(itm),1,f1);
        }
    }
    fclose(fp);
    fclose(f1);

}
/*-----------------------------------------------------------*/

void inc_exist()
{
    itm *c1;
    FILE *fp;
    int ch;
    int rfid;
    int inc;
    do
    {
        printf("Enter rfid to increase the stock : ");
        scanf("%d",&rfid);
        fp = fopen("product.txt","a+");
        while(fread(c1,sizeof(itm),1,fp))
        {
            if(rfid==c1->rfid)
            {
                printf ("Productt name : %s\n",c1->name);
                printf ("Stock : %d\n",c1->stock);
                printf("How much would u lie to incriment : ");
                scanf("%d",&inc);
                stockincriment(inc,rfid);

                break;
            }
        }
        printf("If you want it increase stockk for another item enter 1\nEnter 0 to exit\n");
        printf("Enter choice : ");
        scanf("%d",&ch);

    }while(ch==1);
	fclose(fp);
}
/*-----------------------------------------------------------*/
void stockincriment(int inc,int rfid)
{
    itm c1;
    FILE *fp,*fp1;
    int founnd=0;
    fp = fopen("product.txt","r");
    fp1= fopen("temp_product.txt","w");
    while(fread(&c1,sizeof(itm),1,fp))
    {
        if(rfid==c1.rfid)
        {
            founnd = 1;
            c1.stock=c1.stock+inc;
        }
        fwrite(&c1,sizeof(itm),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if (founnd=1)
    {
        fp = fopen("product.txt","w");
        fp1= fopen("temp_product.txt","r");
        while(fread(&c1,sizeof(itm),1,fp1))
        {
            fwrite(&c1,sizeof(itm),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);

}
/*-----------------------------------------------------------*/
void creatproduct()
{
    itm c1;
    FILE *fp;
    int ch1,inc,last=1001,ch2,found;
    char pname[20];
    int rfid;
    do
    {

        ++last;
        fp = fopen("product.txt","r");
        printf("Enter rfid of new product: ");
        scanf("%d",&rfid);
        found=0;

        while(fread(&c1,sizeof(struct items),1,fp))
        {

            if(rfid==c1.rfid)
            {
                printf("This product already exist!!");
                printf("\nEnter 1 to increment the stock of %s \nEnter 0 to add different product",c1.name);
                printf("\nEnter choice : ");
                scanf("%d",&ch1);
                if(ch1==1)
                {
                    printf("\nHow much would u lie to increment : ");
                    scanf("%d",&inc);
                    stockincriment(inc,c1.rfid);
                    found=1;
                }

                break;
            }

        }

        fclose(fp);
        if(found==0){
        fp = fopen("product.txt","a");
        strcat(c1.name,"\t\t");
        if(c1.rfid!=rfid)
        {
            itm c2;
            printf("Enter name of product : ");
            scanf(" %[^\n]",c2.name);
            printf ("\nEnter quantity : ");
            scanf("%s",c2.quantity);
            c2.rfid=rfid;
            printf ("\nEnter stock : ");
            scanf("%d",&c2.stock);
            printf ("\nEnter cost : Rs.");
            scanf("%d",&c2.cost);
            fwrite(&c2,sizeof(itm),1,fp);
        }
        }

        printf("if you like to add another product Enter 1 \nEnter 0 to exit\nEnter choice : ");
        scanf("%d",&ch2);
    }while(ch2==1);
}
/*------------------------------------------------------*/
void delet_item()
{
    itm c1;
    FILE *fp,*fp1;
    int found=0,ch;
    char name[20];
    do{
    found=0;
    printf("Enter name of the product : ");
    scanf("%s",name);
    fp = fopen("product.txt","r");
    fp1= fopen("temp_product.txt","w");
    while(fread(&c1,sizeof(itm),1,fp))
    {
        if(strcmp(name,c1.name)==0)
        {
           found=1;
        }
        else
        {
            fwrite(&c1,sizeof(itm),1,fp1);
        }

    }
    fclose(fp);
    fclose(fp1);
    if (found=1)
    {
        fp = fopen("product.txt","w");
        fp1= fopen("temp_product.txt","r");
        while(fread(&c1,sizeof(itm),1,fp1))
        {
            fwrite(&c1,sizeof(itm),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
    printf("if you like to delet another product Enter 1 \nEnter 0 to exit\nEnter choice : ");
    scanf("%d",&ch);
    }while(ch==1);
}
/*-----------------------------------------------------------*/
void see(char name[] )
{
    struct items *c1;
    FILE *fp;

    fp = fopen(name,"r");
    printf("\n\nRFID CODE\t\tAMOUNT\t\tNAME\n\n");
    while(fread(c1,sizeof(struct items),1,fp))
    {
        printf("%d\t\t\t%d\t\t%s(%s)\n",c1->rfid,c1->cost,c1->name,c1->quantity);
    }
    fclose(fp);
}
/*-----------------------------------------------------------*/
void list()
{
    printf("\n\nRFID CODE\tAMOUNT\t\tSTOCK\t\tNAME\n\n");

    struct items *c1;
    FILE *fp;

    fp = fopen("product.txt","r");

    while(fread(c1,sizeof(struct items),1,fp))
    {
        printf("%d\t\tRs.%d\t\t%d\t\t%s(%s)\n",c1->rfid,c1->cost,c1->stock,c1->name,c1->quantity);
    }

}

/*------------------------------------------------------*/
int main()
{

    int ch,ch1;
    printf("%60s\n","WELCOME");
    printf("If customer enter : 1\nIf emploiee enter : 2");
    printf("\nEnter choice : ");
    do{
        scanf("%d",&ch);
        if(ch==1)
           {
            cus();
            see("product.txt");
            break;
           }
        else if (ch==2)
          {
            list();
            printf("\nEnter 1 to incriment existing product\nEnter 2 to creat new product\nEnter 3 to delet item\nEnter 4 to exit");
            printf("\nEnter choice : ");
            scanf("%d",&ch1);
            if(ch1==1)
            {
                inc_exist();
            }
            else if (ch1==2)
            {
                creatproduct();
            }
            else if(ch1==3)
            {
                delet_item();
            }
            else if(ch1==4)
            {
                exit(0);
            }
            break;
          }
        printf("\nRenter choice : ");
    }while(ch!=1||ch!=2);
 /*---------------------------------------------------------*/

/*-----------------------------------------------------------*/
    int total = 0;
    if(ch==1)
    {
        while(1)
        {
            printf("\nWolud you like to start shoppint?\nEnter 1 if yes\nEnter 2 to exit");
            printf("\nEnter choice : ");
            scanf("%d",&ch);

            if (ch==1)
            {
                choice();
                printf("\n\nNAME\t\t\t\tQUANTITY\t\t\tAMOUNT(In Rs.)\n");
                printf("---------------------------------------------------------------------------------\n");

                for(int i=0;i<nop;i++)
                {
                    printf("%s",bil[i].name);
                    printf("%30d",bil[i].quantity);
                    printf("%33d\n",bil[i].cost);

                    total= total+bil[i].cost;
                }
                printf("\t\t\t\t\t\t\t      TOTAL  :  Rs.%d",total);
                    break;
            }
            else if (ch==2)
            {
                printf("\n\nEnter 2 again To re conform exit \nEnter 1 to continue shoping \n");
                scanf("%d",&ch);
                if(ch==2)
                {
                    printf("\n\nSorry for inconvinence!!\nWe will surely full fill your need next time");
                    return 0;
                }
            }
        }
    }
    return 0;

}


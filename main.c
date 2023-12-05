#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>


typedef struct
{
    int year;
    int month;
    int day;
} date;
typedef struct
{
    int car_id;
    char type[100];
    char owner_name[100];
    long phone;
} car;
typedef struct
{
    int maintenance_number;
    int car_id;
    date maintenance_date;
    int typesnumber;
    int  pieces[100][100];
    int coast;
    int total_coast;

} maintenance;
typedef struct
{
    int piece_id;
    char name[100];
    int price;
} piece;

char* cartype(char*name,int id)

{
    FILE *fp;

    int found=0;
    car car1;

    fp=fopen(name, "rb");
    if (!fp)
    {
        printf("Unable to open file %s", name);
        return -1;
    }

    while (fread(&car1,sizeof(car),1,fp) !=0)
    {

        if (car1.car_id==id)

        {

            return car1.type;

            found=1;
        }
    }


    fclose(fp);

    if (! found)
    {
        printf("No record(s) found with the requested number: %d\n\n",id);
    }
    return NULL;

}
int findpieceprice(char *fname, int p)
{
    FILE *fp;
    int pricee=0;
    int found=0,i=0;
    piece pi;
    fp=fopen(fname, "rb");
    if (!fp)
    {
        printf("Unable to open file %s", fname);
        return -1;
    }

    while (fread(&pi,sizeof(piece),1,fp) !=0)
    {

        if ( pi.piece_id==p)

        {

            pricee=pi.price;
            found=1;
        }
    }
    if (! found)
    {
        pricee=-1;
    }
    fclose(fp);
    return pricee;
}
bool findtire (char*fname, int p)
{
    FILE *fp;

    int found=0,i=0;
    piece pi;

    fp=fopen(fname, "rb");
    if (!fp)
    {
        printf("Unable to open file %s", fname);
        return -1;
    }

    while (fread(&pi,sizeof(piece),1,fp) !=0)
    {

//printf("%d    %d",pi.piece_id,p);

        if ( pi.piece_id==p)

        {
            if(strcmp(pi.name,"tire")==0)
            {

                found=1;
                return true;

            }
        }
    }
    return false;
    fclose(fp);

}


void tirecars(char*name,char*pi,char*ca)
{
    FILE*fp;
    maintenance m;
    fp=fopen(name, "rb");
    if (!fp)
    {
        printf("Unable to open file %s", name);
        return -1;
    }
    int i;
    while (fread(&m,sizeof(maintenance),1,fp) !=0)
    {

        for(i=0; i<m.typesnumber; i++)
        {


            if(findtire(pi,m.pieces[0][i])==true)
            {
                printf(" car with type %s switched a tire \n",cartype(ca,m.car_id));

            }
        }

    }

}
typedef struct
{
    maintenance number;
    struct sll* next;
} sll;
typedef sll* sptr;

void print_m(maintenance m)
{

    int i;
    printf("maintenance number :");
    printf("%d\n", m.maintenance_number);
    printf("car id : %d\n",m.car_id);
    printf("maintenance date : %d\\%d\\%d \n",m.maintenance_date.day,m.maintenance_date.month,m.maintenance_date.year);
    printf("the total coast of maintenance : %d\n",m.total_coast);
    printf("used pieces :\n");
    printf("piece id:\t");
    printf("\ttimes used :\n");
    for(i=0; i<m.typesnumber; i++)
    {
        printf("%d\t\t\t",m.pieces[0][i]);
        printf("%d\n",m.pieces[1][i]);
    }




    printf("\n");
}
void Print(sptr ls)
{
    while (ls != NULL)
    {
        int i;
        printf("maintenance number :");
        printf("%d\n", ls->number.maintenance_number);
        printf("car id : %d\n",ls->number.car_id);
        printf("maintenance date : %d\\%d\\%d \n",ls->number.maintenance_date.day,ls->number.maintenance_date.month,ls->number.maintenance_date.year);
        printf("the total coast of maintenance : %d\n",ls->number.total_coast);
        printf("used pieces :\n");
        printf("piece id:\t");
        printf("\ttimes used :\n");
        for(i=0; i<ls->number.typesnumber; i++)
        {
            printf("%d\t\t\t",ls->number.pieces[0][i]);
            printf("%d\n",ls->number.pieces[1][i]);
        }




        printf("\n");


        ls = ls->next;
    }
}
void Insert (sptr* ls, maintenance num)
{
    sptr temp, prev_ptr= NULL, next_ptr= NULL;
    temp = (sptr) malloc(sizeof(sll));
    temp->number = num;
    temp->next = NULL;
    if (*ls == NULL)
        *ls = temp;
    else
    {
        next_ptr= *ls;
        bool located = false;
        while ((next_ptr!= NULL) && (located == false))
        {
            if ((next_ptr->number.car_id) < num.car_id)
            {
                prev_ptr= next_ptr;
                next_ptr= next_ptr->next;
            }
            else
                located = true;
        }
        temp->next = next_ptr;
        if (*ls == next_ptr)
            *ls = temp;
        else
            prev_ptr->next = temp;
    }
}
sptr fromfiletolincked(char *filename)
{
    sptr lincked=NULL;
    maintenance m;
    FILE*fp;
    fp=fopen(filename, "rb");
    while (fread(&m,sizeof(maintenance),1,fp) !=0)
    {

        Insert(&lincked,m);

    }
    fclose(fp);

    return lincked;
}
bool test(date d)
{
    if (d.day<0 || d.month<0 || d.month>12 || d.year<1900 || d.year>2018)
        return false;
    else if ((d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 || d.month == 8 || d.month == 10 || d.month == 12) && d.day>31)
        return false;
    else if (d.month == 2 && d.day>28)
        return false;
    else if (d.day>30)
        return false;
    else
        return true;
}
date readdate()
{
    date d;
    printf("enter the day :\n");
    scanf("%d",&d.day);
    printf("enter the month\n");
    scanf("%d",&d.month);
    printf("enter the year\n");
    scanf("%d",&d.year);
    return d;
}
bool validid(char*fname,int id )
{
    FILE *fp;
    fp=fopen(fname, "rb");
    if (!fp)
    {
        printf("Unable to open file %s\n", fname);
        return false;
    }
    if(strcmp(fname,"cars.bin")==0)
    {

        car car1;
        while (fread(&car1,sizeof(car),1,fp) !=0)
        {
            if(car1.car_id==id)
                return false;
        }
    }
    else if(strcmp("maintanance.bin",fname)==0)
    {

        maintenance m;
        while (fread(&m,sizeof(maintenance),1,fp) !=0)
        {
            if(m.maintenance_number==id)
                return false;
        }
    }
    if(strcmp(fname,"pieces.bin")==0)
    {

        piece p;
        while (fread(&p,sizeof(piece),1,fp) !=0)
        {
            if(p.piece_id==id)
                return false;
        }
    }
    return true;
}
void addpiece(char*fname)
{
    FILE*f= fopen(fname,"ab");
    piece p;
    printf("enter the piece number :\n");
    scanf("%d",&p.piece_id);
    if(f)
    {
        while(validid(fname,p.piece_id)==false)
        {
            printf("this id belongs to another car please enter a valid id: \n");
            scanf("%d",&p.piece_id);
        }
    }
    printf("enter the piece name :\n");
    scanf("%s",&p.name);
    printf("enter piece price");
    scanf("%d",&p.price);



    if(!f)
    {
        printf("error in file openning ");
        exit(1);
    }
    fwrite(&p,sizeof(piece),1,f);
    fclose(f);

}
void addcar(char*fname)
{
    FILE*f= fopen(fname,"ab");
    car c;

    printf("please enter car id\n");
    scanf("%d",&c.car_id);
    if(f)
    {
        while(validid(fname,c.car_id)==false)
        {
            printf("this id belongs to another car please enter a valid id: \n");
            scanf("%d",&c.car_id);
        }
    }
    printf("please enter car type\n");
    scanf("%s",&c.type);
    printf("please enter owner of the car's name/n");
    scanf("%s",&c.owner_name);
    printf("please enter phone number n");
    scanf("%ld",&c.phone);





    if(!f)
    {
        printf("error in file openning ");
        exit(1);
    }
    fwrite(&c,sizeof(car),1,f);
    fclose(f);
}
void addmaintanence (int m_number,char* pieces,char*fnam)
{
    FILE *f=fopen(fnam,"ab");
    maintenance m;
    printf("enter maintenance number :\n");
    scanf("%d",&m.maintenance_number);
    if(f)
    {
        while(validid(fnam,m.maintenance_number)==false)
        {
            printf("this id belongs to another maintenance please enter a valid number: \n");
            scanf("%d",&m.maintenance_number);
        }
    }
    printf("enter the number of the car you want to fix :\n");
    scanf("%d",&m.car_id);
    printf("enter the date of fixing:\n");
    date d=readdate();
    while(test(d)==false)
    {
        printf("date unvalid reenter your date\n ");
        d=readdate();
    }
    m.maintenance_date.day=d.day;
    m.maintenance_date.month=d.month;
    m.maintenance_date.year=d.year;
    printf("how many types are used to fix?\n");
    scanf("%d",&m.typesnumber);
    int i;
    for( i=0; i<m.typesnumber; i++)
    {
        printf("piece number :\n");
        scanf("%d",&m.pieces[0][i]);
        while( findpieceprice(pieces,m.pieces[0][i])==-1)
        {
            printf("there is no piece with this number \n");
            printf("piece number :\n");
            scanf("%d",&m.pieces[0][i]);

        }

        printf("how many piesces from this type ?\n");
        scanf("%d",&m.pieces[1][i]);

    }


    printf("enter the coast of maintenance : \n");
    scanf("%d",&m.coast);
    int k,piece_coast=0;
    for(k=0; k<m.typesnumber; k++)
    {
        piece_coast=piece_coast+findpieceprice(pieces,m.pieces[0][k])*m.pieces[1][k];
    }
    m.total_coast=m.coast+piece_coast;
      printf("%d\n",m.total_coast);

    if(!f)
    {
        printf("error in file openning ");
        exit(1);
    }
    fwrite(&m,sizeof(maintenance),1,f);
    fclose(f);


}
int findownercar(char *fname, char* owner)
{

    FILE *fp;

    int found=0;
    car car1;

    fp=fopen(fname, "rb");
    if (!fp)
    {
        printf("Unable to open file %s\n", fname);
        return -1;
    }


    while (fread(&car1,sizeof(car),1,fp) !=0)
    {


        if (strcmp (owner, car1.owner_name) == 0)

        {

           printf("%s has car with number %d\n",car1.car_id);

            found=1;
        }
    }


    fclose(fp);


    if (! found)
    {
        printf("No record(s) found with the requested name: %s\n\n", owner);
    }

    return 0;
}
void afterdate(char*fname,date d)
{

    FILE *p;

    int found=0,coast=0;
    maintenance m;
    p=fopen(fname, "rb");
    if (!p)
    {
        printf("Unable to open file %s", fname);
        return -1;
    }

    while (fread(&m,sizeof(maintenance),1,p) !=0)
    {

        if (d.year<m.maintenance_date.year||(d.year==m.maintenance_date.year&&d.month<m.maintenance_date.month)||(d.year==m.maintenance_date.year&&d.month==m.maintenance_date.month&&d.day<m.maintenance_date.day))


        {

            print_m(m);

            found=1;
        }
    }


    fclose(p);

    if (! found)
    {
        printf("No record(s) found after the requested date\n");
    }



    return 0;
}


int mostusedpiece(char*fname)
{
    FILE*f;
    maintenance m;
    int arr[100]= {0};

    int found=0,max_m=0,max_id=0;
    int i;
    f=fopen(fname,"rb");
    if (!f)
    {
        printf("Unable to open file %s", fname);
        return -1;
    }

    while (fread(&m,sizeof(maintenance),1,f) !=0)
    {

        for(i=0; i<m.typesnumber; i++)
        {

            if(m.pieces[0][i]>max_id)
            {

                max_id=m.pieces[0][i];

            }

            arr[m.pieces[0][i]]=arr[m.pieces[0][i]]+m.pieces[1][i];
        }






    }

    for(i=0; i<max_id+1; i++)
    {
        if(arr[i]>max_m)
            max_m=arr[i];
    }

    printf("the most used piece has the number %d and it is used %d times\n",max_id,max_m);
}

int carmaintenances(char*  fname,int id)
{
    FILE *p;

    int found=0,coast=0;
    maintenance m;
    int price=0;
    p=fopen(fname, "rb");
    if (!p)
    {
        printf("Unable to open file %s", fname);
        return -1;
    }

    while (fread(&m,sizeof(maintenance),1,p) !=0)
    {


        if ( m.car_id==id)

        {

            coast=coast+m.total_coast;
            print_m(m);

            found=1;
        }
    }


    fclose(p);


    if (! found)
    {
        printf("No record(s) found with the requested number: %d\n\n", id);
    }

    printf("the total coast for this car is:%d",coast);

    return 0;
}
int deleteRecordBynumber(char *fname, int k)
{
    FILE *fp;
    FILE *fp_tmp;
    int found=0;
    car car1;

    fp=fopen(fname, "rb");
    if (!fp)
    {
        printf("Unable to open file %s", fname);
        return -1;
    }
    fp_tmp=fopen("tmp.bin", "wb");
    if (!fp_tmp)
    {
        printf("Unable to open file temp file.");
        return -1;
    }

    while (fread(&car1,sizeof(car),1,fp) !=0)
    {

        if (car1.car_id==k)
        {
            printf("A car with this number found and deleted.\n\n");
            found=1;
        }
        else
        {
            fwrite(&car1, sizeof(car), 1, fp_tmp);
        }
    }
    if (! found)
    {
        printf("No record(s) found with the requested number: %d\n\n", k);
    }


    fclose(fp);
    fclose(fp_tmp);

    remove(fname);
    rename("tmp.bin", fname);

    return 0;
}
int main()
{

    while(1)
    {
        int n;
        printf("choose:\n");
        printf( "1 to add a piece\n");
        printf("2 to add a car \n");
        printf("3 to add a maintenance\n");
        printf("4 to delete a car by its id\n");
        printf("5 to serch for someone's cars\n");
        printf("6 show all maintenances sorted by the car id\n");
        printf("7 show all car's mauntenances and the cost of it\n");
        printf("8 to know the most used piece\n");
        printf("9 to show all the cars that had a maintenance after a certain date \n");
        printf("10 show the types of the cars that replaced a tire \n");
        scanf("%d",&n);
        switch ( n)
        {
        case 1:
        {
            addpiece("pieces.bin");
            break;
        }
        case 2:
        {
            addcar("cars.bin");
            break;

        }
        case 3:
        {
            addmaintanence(0,"pieces.bin","maintanance.bin");
            break;
        }
        case 4:
        {

            int d;
            printf("enter the number of the car you want to delete :\n");
            scanf("%d",&d);
            deleteRecordBynumber("cars.bin",d);
            break;
        }
        case 5:
        {
            char s[10];
            printf("enter the name of the owner : \n ");
            scanf("%s",&s);

            findownercar("cars.bin",s);
            break;
        }
        case 6:
        {
            sptr s=NULL;
            s=fromfiletolincked("maintanance.bin");
            Print(s);
            break;
        }
        case 7:
        {
            int d;
            printf("enter the number of the car you want to search :\n");
            scanf("%d",&d);
            carmaintenances("maintanance.bin",d);
            break;
        }
        case 8:
        {
            mostusedpiece("maintanance.bin");
            break;
        }
        case 9:
        {
            date d;
            printf("enter the date:\n");
            printf("day:");
            scanf("%d",&d.day);
            printf("month:");
            scanf("%d",&d.month);
            printf("year:");
            scanf("%d",&d.year);
            afterdate("maintanance.bin",d);
            break;

        }
        case 10:
        {
            tirecars("maintanance.bin","pieces.bin","cars.bin");
            break;
        }

        default :
            printf("error !! enter a number between 1 to 10\n");



        }

    }

    //   FILE*p=fopen("pieces.bin","ab");
    //   addpiece("pieces.bin");
    // addcar("cars.bin");
    //addmaintanence(4,"pieces.bin","maintanance.bin");
    //  tirecars("maintanance.bin","pieces.bin","cars.bin");
    //   addcar("cars.bin");
    // addmaintanence(m_number,"pieces.bin","maintanance.bin");
    //add_car
    /*FILE*f= fopen("cars.bin","ab");

    car car1=addcar();
    addpiece("pieces.bin");
    if(!f)
    {
        printf("error in file openning ");
        exit(1);
    }
    fwrite(&car1,sizeof(car),1,f);
    fclose(f);*/
//add _maintanence
    /*  FILE*maintenanc =fopen("maintanance.bin","ab");

      maintenance m=addmaintanence(m_number,"pieces.bin","maintanance.bin");
      printf(" this is it %d",m.car_id);
      m_number++;
      if(!maintenanc)
      {
          printf("error in file openning ");
          exit(1);
      }
      fwrite(&m,sizeof(maintenance),1,maintenanc);
      fclose(maintenanc);*/

    /* sptr s=NULL;
     s=fromfiletolincked("maintanance.bin");
     Print(s);*/

    //deleteRecordBynumber("cars.bin",9);
    /*  car car2;
      f=fopen("cars.bin","rb");
    while (fread(&car2,sizeof(car),1,f)!=0){

         printf("%d",car2.car_id);
       }
       fclose(f);*/
    // int r=deleteRecordBynumber("cars.bin",5);
//int sa=findownercar("cars.bin","2");
    // printf("lincked\n");
    //  Print(s);

    // carmaintenances("maintanance.bin",3);
    //printf("blshnaaa");

    // mostusedpiece("maintanance.bin");
  /*  date d;
    d.day=1;
    d.month=1;
    d.year=1997;*/
    // afterdate("maintanance.bin",d);

    return 0;
}


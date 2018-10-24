#include <stdio.h>
#include <stdlib.h>         // for malloc
#include <string.h>         // for strcpy
#include<time.h>            // for clock() function
#include <sys/resource.h>   // for rusage
#include <sqlite3.h>   // for sqlite3

typedef struct _Rec {
  int id;         /* unikalny identyfikator, klucz główny */
  char name[20];  /* nazwa */
  char desc[90];  /* opis */
} Rec;

int main()
{
    clock_t c1,c2;
    int size=1000000; // one million rows
    struct rusage mem;

    //sqlite3 initialization
    int rc;
    sqlite3 *db;
    char loc[]=":memory:";

    rc=sqlite3_open(loc,&db);
    if (rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    //------------DATA ALLOCATION

    Rec* records = malloc(sizeof(Rec) * size);
    if (records==NULL) {
        fprintf(stderr,"Mem alloc error\n");
        return 1;
    }

    c1=clock();
    for(int i=0;i<size;i++){
        records[i].id=i+1;
        strcpy(records[i].name, "name");
        strcpy(records[i].desc, "Desc");
    }

    c2=clock();
    printf("records data fulfillment took: %f[s]\n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);

    //-------------DATA SEARCHING

    c1=clock();
    for(int i=0;i<size;i++){
        if(records[i].id==999999){
            c2=clock();
        }
    }

    printf("record with id=999999999 found in: %f[s]\n", ((float)c2-(float)c1)/CLOCKS_PER_SEC);
   
    // ---------------RESOURCE USAGE
    getrusage(RUSAGE_SELF,&mem);
    printf("Max mem usage[kB]: %ld\n", mem.ru_maxrss);



   free(records);
   sqlite3_close(db);

   return 0;
}
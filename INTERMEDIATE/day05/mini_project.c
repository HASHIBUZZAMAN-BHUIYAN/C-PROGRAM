/*
 * Int Day 05 Mini-Project — Phone Book using Hash Table
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_SIZE 32
typedef struct E { char name[64]; char phone[20]; struct E *next; } E;
typedef struct { E *b[HT_SIZE]; } HT;

unsigned int hf(const char *k) {
    unsigned int h=5381; while(*k) h=h*33^(unsigned char)(*k++); return h%HT_SIZE;
}
void ht_add(HT *ht, const char *name, const char *phone) {
    unsigned int i=hf(name);
    for(E *e=ht->b[i];e;e=e->next) if(strcmp(e->name,name)==0){strncpy(e->phone,phone,19);return;}
    E *e=malloc(sizeof(E)); strncpy(e->name,name,63); strncpy(e->phone,phone,19);
    e->next=ht->b[i]; ht->b[i]=e;
}
const char *ht_lookup(const HT *ht, const char *name) {
    unsigned int i=hf(name);
    for(E *e=ht->b[i];e;e=e->next) if(strcmp(e->name,name)==0) return e->phone;
    return NULL;
}
void ht_list(const HT *ht) {
    for(int i=0;i<HT_SIZE;i++) for(E *e=ht->b[i];e;e=e->next) printf("  %-20s %s\n",e->name,e->phone);
}
void ht_free(HT *ht) {
    for(int i=0;i<HT_SIZE;i++){E *e=ht->b[i];while(e){E *t=e->next;free(e);e=t;}}
}

int main(void) {
    HT pb = {0};
    printf("=== Phone Book ===\nEnter name phone (blank name to stop):\n");
    char nm[64], ph[20];
    while(1){
        printf("Name : "); fgets(nm,64,stdin); nm[strcspn(nm,"\n")]='\0';
        if(!nm[0]) break;
        printf("Phone: "); fgets(ph,20,stdin); ph[strcspn(ph,"\n")]='\0';
        ht_add(&pb,nm,ph);
    }
    printf("\nAll contacts:\n"); ht_list(&pb);
    printf("\nLookup: "); fgets(nm,64,stdin); nm[strcspn(nm,"\n")]='\0';
    const char *r=ht_lookup(&pb,nm);
    printf(r?"Found: %s\n":"Not found\n", r?r:"");
    ht_free(&pb);
    return 0;
}

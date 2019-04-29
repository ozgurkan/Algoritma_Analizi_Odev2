#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define tablodakiElemansayisi 500
#define loadFactor 0.70
    int m=571;
    int r=569;

    typedef struct veri{
        int key;
        char value[50];
    }v;
    v table[tablodakiElemansayisi];

int FindKey(char buffer[50]){
    int word_length = strlen(buffer);
    int key=0;
    int i=0;
    if(isupper(buffer[i])){
        //kelime büyük harflerse bunu yap
        for(i=0;i < word_length; i++) key += (buffer[i] - 'A' )*26*i ;
    }else{
        //kelime kücük harrflerse bunu yap
        for (i = 0; i < word_length; i++)key += buffer[i];
    }
    return key;
}

int InsertToHash(v data){
    int i=0;
    int a=(data.key%m+ i*(r-(data.key%r))) % m;
    while(a>tablodakiElemansayisi || table[a].key!=-1){
        i++;
        a=(data.key%m+ i*(r-(data.key%r))) % m;
    }
        table[a].key=data.key;
        strcpy(table[a].value,data.value);
    return 1;
}

int SearchToHash(v data,int ModSecim){
    int i=0;

    int a=(data.key%m+ i*(r-(data.key%r))) % m;
    if(ModSecim==1){
        printf("i=%d    m=%d    r=%d    key=%d  value=%s    h1=%d   offset=%d   indis=%d\n",i,m,r,data.key,data.value,data.key%m,r-(data.key%r),a);

    }
    while(a>tablodakiElemansayisi){
        i++;
        a=(data.key%m+ i*(r-(data.key%r))) % m;
        if(ModSecim==1){
            printf("i=%d    m=%d    r=%d    key=%d  value=%s    h1=%d   offset=%d   indis=%d\n",i,m,r,data.key,data.value,data.key%m,r-(data.key%r),a);

        }
    }
    printf("-------------------------------------------------------------------\n");
    while(a<tablodakiElemansayisi && strcmp(table[a].value,data.value)!=0 && table[a].key!=-1){
        i++;
        a=(data.key%m+ i*(r-(data.key%r))) % m;
        if(ModSecim==1){
            printf("i=%d    m=%d    r=%d    key=%d  value=%s    h1=%d   offset=%d   indis=%d\n",i,m,r,data.key,data.value,data.key%m,r-(data.key%r),a);

        }
            while(a>tablodakiElemansayisi){
            i++;
            a=(data.key%m+ i*(r-(data.key%r))) % m;
            if(ModSecim==1){
                printf("i=%d    m=%d    r=%d    key=%d  value=%s    h1=%d   offset=%d   indis=%d\n",i,m,r,data.key,data.value,data.key%m,r-(data.key%r),a);
            }
            }

    }

    if(strcmp(table[a].value,data.value)==0){
        printf("ARANAN KELIME BULUNDU");
        return 1;
    }else{
        printf("ARANAN KELIME BULUNAMADI");
        return 0;
    }
}

void OnerilenSearchToHash(v data){
    int i=0;
    int a=(data.key%m+ i*(r-(data.key%r))) % m;
    while(a>tablodakiElemansayisi){
        i++;
        a=(data.key%m+ i*(r-(data.key%r))) % m;
    }
    while(a<tablodakiElemansayisi && strcmp(table[a].value,data.value)!=0){
        i++;
        a=(data.key%m+ i*(r-(data.key%r))) % m;
            while(a>tablodakiElemansayisi){
            i++;
            a=(data.key%m+ i*(r-(data.key%r))) % m;
            }
    }
    if(strcmp(table[a].value,data.value)==0){
        printf("    %s\n",data.value);
    }
}

int KelimeOner(v data){
    printf("\nKelime Onerileri:\n");
    int lenght_word=strlen(data.value);
    int i=0,j=0,temp;
        for(j=0;i<lenght_word;i++){
            temp=data.value[i];
            for(j=97;j<=122;j++){
                data.value[i]=j;
                data.key=FindKey(data.value);
                OnerilenSearchToHash(data);
            }
            data.value[i]=temp;
        }
}

int main()
{
    int i;
    int ModSecim=0;
    printf("NORMAL MOD ICIN =0 , DEBUG MOD =1 GIRINIZ:");
    scanf("%d",&ModSecim);
    if(ModSecim==0){
        printf("NORMAL MOD SECILDI.");
    }
    else if(ModSecim==1){
        printf("DEBUG MOD SECILDI.");
    }
    else{
        printf("YANLIS GIRIS....PROGRAM DEFAULT OLARAK NORMAL MODDA CALISACAK.");
        ModSecim=0;
    }

    int HashTableOlsunMu=0;
    printf("\nHASH TABLOSU OLUSTURMAK ICIN =0 , OLUSTURMAMAK ICIN =1 GIRINIZ:");
    scanf("%d",&HashTableOlsunMu);
    if(HashTableOlsunMu==0){
            FILE* sozluk;
            sozluk = fopen("smallDictionary.txt", "r");
                for(i=0;i<tablodakiElemansayisi;i++){
                    table[i].key=-1;
                }
                if (sozluk == NULL){
                    printf("Dosya acilamadi.");
                }else{
                    printf("Dosya acildi.\n");
                    char buffer[50];
                    while (fscanf(sozluk, "%s", buffer) > 0)
                    {
                        v data;
                        data.key=FindKey(buffer);
                        strcpy(data.value,buffer);
                        InsertToHash(data);
                    }
                }
        fclose(sozluk);
        FILE *fp=fopen("HashTable.txt","a");
            for(i=0;i<tablodakiElemansayisi;i++){
                //printf("%d %s\n",table[i].key,table[i].value);
                fprintf(fp," %d %s\n",table[i].key,table[i].value);
            }
        fclose(fp);
        printf("Hash Tablosu olusturuldu ve HashTable.txt dosyasýna yazýldý.");
    }
    else if(HashTableOlsunMu==1){
        char isim[100];
        int k=0;
        printf("HASH TABLONUZUN SAKLI OLDUGU DOSYA ISMINI GIRINIZ:");
        scanf("%s",isim);
        FILE* sozluk;
        sozluk = fopen(isim, "r");
                if (sozluk == NULL){
                    printf("Dosya acilamadi.");
                }else{
                    printf("Hash dosyanýz acildi.\n");
                    int key;
                    char buffer[50];
                    for(k=0;k<tablodakiElemansayisi;k++){
                        fscanf(sozluk, "%d", &key);
                        if(key!=-1){
                            fscanf(sozluk, "%s", buffer);
                        }else{
                            strcpy(buffer,"");
                        }
                        table[k].key=key;
                        strcpy(table[k].value,buffer);
                    }
                    /*Kullanýcýnýn kendi Hash Tablosu ekrana yazdýrma*/
                    for(i=0;i<tablodakiElemansayisi;i++){
                        printf("%d %s\n",table[i].key,table[i].value);
                    }
                }
    }
    /*Kelime ARAMA*/
                char aranan[50];
                printf("\nAranacak kelimeyi giriniz:");
                scanf("%s",aranan);
                v data;
                data.key=FindKey(aranan);
                strcpy(data.value,aranan);
                int kontrol;
                kontrol=SearchToHash(data,ModSecim);

                if(kontrol==0){
                     KelimeOner(data);
                }

    return 0;
}


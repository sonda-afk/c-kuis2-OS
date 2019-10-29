// Library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <pthread.h>

#define MAX_SIZE 1000

// Struktur data
typedef struct {
    char c;                     // Menampung masukan karakter/huruf
    int m;                      // Menampung jumlah kata/huruf masukan di dalam file
    int n;                      // Menampung jumlah kata dalam file
    char s[MAX_SIZE];           // Menampung masukan kata 
    char str[MAX_SIZE];         // Menampung string saat scan isi file text
    char temp[MAX_SIZE];        // Menampung string saat scan isi file text untuk dibandingkan
    char fileName[MAX_SIZE];    // Menampung nama file
    FILE *fdata;                // Menampung value fopen
    struct dirent *dir;         // Pointer file dalam direktori
    int found;                  // Status ketemu
    int menu;                   // Pilihan menu
} struct1;

// Prosedur untuk dijalankan oleh thread
void *printHasil(void* var){

    // Struct penunjuk
    struct1 *vars; 
    vars = (struct1*) var;

    // Output
    printf("Process ID Parent : %d | Process ID Child : %d\n", getppid(), getpid());
    printf("Nama File : %s\n", vars->fileName);
    printf("Jumlah kata dalam file : %d\n", vars->n);
    // Jika memilih menu 1
    if(vars->menu == 1){
        printf("Jumlah kata yang mengandung karakter '%c' : %d\n", vars->c, vars->m);
    }   
    // Jika memilih menu 2
    else if(vars->menu == 2){
        printf("Jumlah kata '%s' dalam file : %d\n", vars->s, vars->m);
    }
    // Jika memilih menu 3
    else if(vars->menu == 3){
        printf("Jumlah huruf vokal dalam file : %d\n", vars->m);
    }
    // Jika memilih menu 4
    else {
        printf("Jumlah huruf konsonan dalam file : %d\n", vars->m);
    }
    printf("\n");

    return NULL;
}

// Proses untuk pilihan menu pertama
void proses_satu(struct1 *var){

    // Menampung nama file
    strcpy(var->fileName, var->dir->d_name);

    // Menampung lebar string nama file
    int len = strlen(var->fileName);

    // Menampung jumlah kata dan huruf
    var->m = 0, var->n = 0;

    // Proses akan berjalan apabila file berformat "txt"
    if((len > 4) && (var->fileName[len - 1] == 't') && (var->fileName[len - 2] == 'x') && (var->fileName[len - 3] == 't') && (var->fileName[len - 4] == '.')){

        // Membuka file dalam read mode
        var->fdata = fopen(var->fileName, "r");

        // Mengecek apakah file bisa dibuka atau tidak
        if(var->fdata == NULL){
            printf("File %s tidak dapat dibuka.\n\n", var->fileName);
        }

        // Iterator
        int i;     

        // Membuat thread
        pthread_t thread1;

        // Loop proses
        do {
            
            // Membaca string pada file text
            fscanf(var->fdata, "%999s", var->str);
            // Menyalin ke variabel temporary
            strcpy(var->temp, var->str);

            // Inisialisasi status ketemu
            var->found = 0;

            // Pencarian huruf
            for(i = 0; i < strlen(var->temp); i++){
                if(var->temp[i] == var->c){
                    var->found = 1;
                }
            }
            if(var->found == 1){
                var->m++;
            }

            // Menambah jumlah kata setiap iterasi
            var->n++;
        }
        // Akan looping selama file text masih ada stringnya
        while(fgetc(var->fdata) != EOF);

        // Menjalankan thread
        pthread_create(&thread1, NULL, printHasil, (void*) var);
        pthread_join(thread1, NULL);

        // Menutup file
        fclose(var->fdata);
    }
}

// Proses untuk pilihan menu kedua
void proses_dua(struct1 *var){

    // Menampung nama file
    strcpy(var->fileName, var->dir->d_name);

    // Menampung lebar string nama file
    int len = strlen(var->fileName);

    // Menampung jumlah kata dan huruf
    var->m = 0, var->n = 0;

    // Proses akan berjalan apabila file berformat "txt"
    if((len > 4) && (var->fileName[len - 1] == 't') && (var->fileName[len - 2] == 'x') && (var->fileName[len - 3] == 't') && (var->fileName[len - 4] == '.')){

        // Membuka file dalam read mode
        var->fdata = fopen(var->fileName, "r");

        // Mengecek apakah file bisa dibuka atau tidak
        if(var->fdata == NULL){
            printf("File %s tidak dapat dibuka.\n\n", var->fileName);
        }

        // Membuat thread
        pthread_t thread1;

        // Loop proses
        do {

            // Membaca string dalam file
            fscanf(var->fdata, "%s", var->str);
            // Menyalin ke variabel temporary
            strcpy(var->temp, var->str);

            // Mencari jumlah kata inputan dalam file text
            if(strcmp(var->temp, var->s) == 0){
                var->m++;
            }

            // Menambah jumlah kata setiap iterasi
            var->n++;
        }
        // Akan looping selama file text masih ada stringnya
        while(fgetc(var->fdata) != EOF);

        // Menjalankan thread
        pthread_create(&thread1, NULL, printHasil, (void*) var);
        pthread_join(thread1, NULL);

        // Menutup file
        fclose(var->fdata);
    }
}

// Proses untuk pilihan menu ketiga
void proses_tiga(struct1 *var){

    // Menampung nama file
    strcpy(var->fileName, var->dir->d_name);

    // Menampung lebar string nama file
    int len = strlen(var->fileName);

    // Menampung jumlah kata dan huruf
    var->m = 0, var->n = 0;

    // Proses akan berjalan apabila file berformat "txt"
    if((len > 4) && (var->fileName[len - 1] == 't') && (var->fileName[len - 2] == 'x') && (var->fileName[len - 3] == 't') && (var->fileName[len - 4] == '.')){

        // Membuka file dalam read mode
        var->fdata = fopen(var->fileName, "r");

        // Mengecek apakah file bisa dibuka atau tidak
        if(var->fdata == NULL){
            printf("File %s tidak dapat dibuka.\n\n", var->fileName);
        }

        // Iterator
        int i;

        // Membuat thread
        pthread_t thread1;

        // Loop proses
        do {

            // Membaca string dalam file
            fscanf(var->fdata, "%s", var->str);
            // Menyalin ke variabel temporary
            strcpy(var->temp, var->str);

            // Proses mencari huruf vokal
            for(i = 0; i < strlen(var->temp); i++){
                if(
                    (var->temp[i] == 'a') || 
                    (var->temp[i] == 'A') || 
                    (var->temp[i] == 'i') || 
                    (var->temp[i] == 'I') || 
                    (var->temp[i] == 'u') || 
                    (var->temp[i] == 'U') || 
                    (var->temp[i] == 'e') || 
                    (var->temp[i] == 'E') || 
                    (var->temp[i] == 'o') || 
                    (var->temp[i] == 'O'))
                    {
                    var->m++;
                }
            }

            // Menambah jumlah kata setiap iterasi
            var->n++;
        }
        // Akan looping selama file text masih ada stringnya
        while(fgetc(var->fdata) != EOF);

        // Menjalankan thread
        pthread_create(&thread1, NULL, printHasil, (void*) var);
        pthread_join(thread1, NULL);

        // Menutup file
        fclose(var->fdata);
    }
}

// Proses untuk pilihan menu keempat
void proses_empat(struct1 *var){

    // Menampung nama file
    strcpy(var->fileName, var->dir->d_name);

    // Menampung lebar string nama file
    int len = strlen(var->fileName);

    // Menampung jumlah kata dan huruf
    var->m = 0, var->n = 0;

    // Proses akan berjalan apabila file berformat "txt"
    if((len > 4) && (var->fileName[len - 1] == 't') && (var->fileName[len - 2] == 'x') && (var->fileName[len - 3] == 't') && (var->fileName[len - 4] == '.')){

        // Membuka file dalam read mode
        var->fdata = fopen(var->fileName, "r");

        // Mengecek apakah file bisa dibuka atau tidak
        if(var->fdata == NULL){
            printf("File %s tidak dapat dibuka.\n\n", var->fileName);
        }

        // Iterator
        int i;

        // Membuat thread
        pthread_t thread1;

        // Loop proses
        do {

            // Membaca string dalam file
            fscanf(var->fdata, "%s", var->str);
            // Menyalin ke variabel temporary
            strcpy(var->temp, var->str);

            // Proses mencari huruf konsonan
            for(i = 0; i < strlen(var->temp); i++){
                if(
                    (var->temp[i] != 'a') && 
                    (var->temp[i] != 'A') && 
                    (var->temp[i] != 'i') && 
                    (var->temp[i] != 'I') && 
                    (var->temp[i] != 'u') && 
                    (var->temp[i] != 'U') && 
                    (var->temp[i] != 'e') && 
                    (var->temp[i] != 'E') && 
                    (var->temp[i] != 'o') && 
                    (var->temp[i] != 'O'))
                    {
                    var->m++;
                }
            }

            // Menambah jumlah kata setiap iterasi
            var->n++;
        }
        // Akan looping selama file text masih ada stringnya
        while(fgetc(var->fdata) != EOF);

        // Menjalankan thread
        pthread_create(&thread1, NULL, printHasil, (void*) var);
        pthread_join(thread1, NULL);

        // Menutup file
        fclose(var->fdata);
    }
}

int main(){

    // Variabel-variabel
    int m_stat = 1;                 // Status menu
    DIR *directory;                 // Variabel untuk membaca direktori
    struct dirent *dir;             // Pointer file dalam direktori
    char dirName[MAX_SIZE];         // Untuk menampung nama direktori
    int status;                     // Status proses fork
    int pid;                        // Menampung process id

    // Struct
    struct1 *var;
    var = (struct1*) malloc (sizeof(struct1));

    // Loop proses
    while(m_stat == 1){

        // Input nama directory
        printf("Silahkan input direktori (ketik 'end.' untuk exit): ");
        scanf("%s", dirName);

        // Jika command exit
        if(strcmp(dirName, "end.") == 0){
            m_stat = 0;
        }

        // Jika bukan command exit
        else {

            // Membuka direktori
            directory = opendir(dirName);

            // Jika direktori valid
            if((directory) && ((var->dir = readdir(directory)) != NULL)){

                // Pilihan menu
                printf("Pilih Menu :\n");
                printf("1. Mencari jumlah kata berdasarkan karakter/huruf masukan\n");
                printf("2. Mencari jumlah kata berdasarkan kata masukan\n");
                printf("3. Mencari jumlah huruf vokal\n");
                printf("4. Mencari jumlah huruf konsonan\n");
                scanf("%d", &var->menu);
                printf("\n");

                // Jika memilih menu pertama
                if(var->menu == 1){
                    printf("Masukan karakter/huruf : ");
                    scanf(" %c", &var->c);
                    printf("\n");
                }
                // Jika memilih menu kedua
                else if(var->menu == 2){
                    printf("Masukan kata : ");
                    scanf("%s", var->s);
                    printf("\n");
                }

                // Loop membaca file
                while(var->dir != NULL){

                    // Jika proses menu pertama
                    if(var->menu == 1){

                        // Membuat child process
                        // Jika gagal membuat child process
                        if((pid = fork()) < 0){
                            perror("error fork");
                            exit(-1);
                        }
                        // Jika berhasil membuat child process
                        else if(pid == 0){
                            proses_satu(var);
                            exit(0);
                        }
                    }

                    // Jika proses menu kedua
                    else if(var->menu == 2){

                        // Membuat child process
                        // Jika gagal membuat child process
                        if((pid = fork()) < 0){
                            perror("error fork");
                            exit(-1);
                        }
                        // Jika berhasil membuat child process
                        else if(pid == 0){
                            proses_dua(var);
                            exit(0);
                        }
                    }

                    // Jika proses menu ketiga
                    else if(var->menu == 3){

                        // Membuat child process
                        // Jika gagal membuat child process
                        if((pid = fork()) < 0){
                            perror("error fork");
                            exit(-1);
                        }
                        // Jika berhasil membuat child process
                        else if(pid == 0){
                            proses_tiga(var);
                            exit(0);
                        }
                    }

                    // Jika proses menu keempat
                    else if(var->menu == 4){

                        // Membuat child process
                        // Jika gagal membuat child process
                        if((pid = fork()) < 0){
                            perror("error fork");
                            exit(-1);
                        }
                        // Jika berhasil membuat child process
                        else if(pid == 0){
                            proses_empat(var);
                            exit(0);
                        }
                    }

                    // Iterasi
                    var->dir = readdir(directory);
                }

                // Menunggu sampai semua child process selesai setelah itu kembali ke proses parent awal
                while(wait(&status) > 0);
            }

            // Jika direktori tidak valid
            else {
                printf("Direktori tidak valid atau direktori kosong.\n");
            }

            // Menutup directory
            closedir(directory);
        }
    }
    return 0;
}
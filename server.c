#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>


#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define COMMAND_SIZE 6
#define MAX_LENGTH 1000

/*
TO DO user commands
1. Stworzyć plik
2. Udostępnić plik
3. Lista połączonych użytkowników
4. Usunąć plik
5. Skopiować plik
6. Zmienić nazwę pliku
 */

char* commands[6] = {"touch", "share", "list", "delete", "copy", "rename"};

// struktura zawierająca dane, które zostaną przekazane do wątku "klienta"
struct thread_data_t
{
    int max_number_of_clients;  //<---maksymalny rozmiar klientow
    //musimy dodac dynamiczna tablice client_socketfd
    int *client_socketfd;
    int number_of_clients;      //<---teraz zalogowanych
    int last_connected;         //<---ostatnio polaczony
    char name_identificator;    //<---identyfikator klienta (klient na start wpisuje). Tworzony na podstawie tego jest tworzony/otwierany odpowiedni folder z dokumentami

    // mutex do operacji na danych w strukturze
    pthread_mutex_t thread_data_mutex;
};

// funkcje odczytujaca przeslane wiadomosci od klienta
//************************************
// funkcja odpowiedzialna za podzial. Zczytana tablica wprowadzonych argumentow
char** buf_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    printf("Wprowadzony string: %s\n", a_str);
    /* Count how many elements will be extracted. */
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;
    result = malloc(sizeof(char*) * count);
    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token){
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }

        printf("%d\n", count);
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}

//odczyt pierwszej wczytanej wartosci do spacji i zrzutowanie jej na wartosc numeryczna
int readCommand(char** tokens, char* buf[]){
    tokens = buf_split(buf, ' '); //<-- wynik tablica wskaznikow char
    if (tokens){
        int i;
        for (i = 0; *(tokens + i); i++){
            printf("Argument: %s\n", *(tokens + i));
            //free(*(tokens + i));
        }
        printf("\n");
        //free(tokens);
    }
    int i;
    char* word = " ";
    word = *(tokens + 0);

    for (i = 0; i < COMMAND_SIZE; i++){
        fwrite(commands[i], 1, strlen(commands[i]), stdout);

        //strncpy(word, *(tokens + i), 10);
        printf("\nword %s\n", word);

        printf(" Indeks i: %d\n", i);
        if(strcmp(word, commands[i]) == 0){
            return i;
        }
        else
            printf("Lancuchy nie sa rowne\n");
    }
}
//***********************

void createMainDocument(){

}

// funkcja wypisująca zawartość tablicy typu int
void print_array_content(int *arr, int len) {
    printf("Polaczone gniazda\n");
    for (int i = 0; i < len; i++)
        printf("\t %d ", *(arr+i));
    printf("\n\n");
}

//obslugiwanie i tworzenie pliku dla komendy TOUCH
void touchCommand(){
    //readlink("/proc/self/exe", path, sizeof(path)); //<--- w systemach uniksowych do znalezienia sciezki musimy odwolac sie do /usr/bin/perl
    //komenda na gorze powinna dzialac ale no wlasnie cos jest nie tak. Przejdziemy do podstepu i wykonamy komende linuksowa z przekierowaniem do /dev/null
    //system("pwd >/dev/null 2>&1");
    //inne podejscie
    puts("Informacje o utworzonej sciezce\n");
    printf("\tFolder: %s\n", getenv("PWD"));
    //printf("\tWykonywany plik: %s/%s\n", getenv("PWD"), __FILE__);
    char* path = getenv("PWD");

    char* dirname = "DOCUMENTS";

    //sprawdz czy istnieje
    DIR* dir = opendir(dirname);
    if(!(dir)) {
        closedir(dir);
        printf("Tworzenie folderu\n");
        mkdir(dirname, 0777);
    }
    dir = opendir(dirname);
    strcat(path, "/");
    strcat(path, dirname);
    strcat(path, "/NAME.txt");
    printf("Sciezka tworzonego pliku: %s\n", path);

    FILE* file_descriptor = open(path, O_RDWR|O_CREAT);
    if (file_descriptor == -1) {
        printf("Błąd przy próbie tworzenia pliku\n");
        exit(-1);
    }
    fclose(file_descriptor);
};

void shareCommand(){
    //POMYSLEC NAD ROZWIAZANIEM
    //Mamy dwie opcje udostepniania/zabezpieczenia udzielenia dostepu
    //Number uno (zabezpieczenie)
    //Przy tworzeniu pliku tworzymy rowniez uzytkownika na linuksie. Tworzymy rowniez grupe o takiej samej nazwie
    //pryz udostepnianiu uzytkownikowi dodajemy go do grupy uzytkownika wlasciciela

    //Number secondo (udostepnienie)
    //Przy kazdym zalogowaniu sie uzytkownika musimy identyfikowac czy ma stworzony folder ze swoja nazwa i dokument
    //Identyfikacja? Narazie wpisujemy przy laczeniu nazwe uzytkownika (po stronie klienta). Potem mozna zamienic na adres ip
    //Po zalogowaniu i sprawdzeniu czy dokument istnieje program pobiera deskryptor pliku -> pobiera liste zalogowanych uzytkownikow i przekazuje je do udostepnienia
}

void listCommand(struct thread_data_t *t_data_ptr){
    //modyfikacja tablicy na nieograniczony rozmiar
    printf("Obecnie połączone gniazda:\n");
    print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
}

// funkcja zerująca komórki tablicy, w których dotychczas znajdowała się podana wartość
void clear_array_cell(int *arr, int len, int value) {
    for(int i = 0; i < len; i++)
        if (arr[i] == value)
            arr[i] = 0;
}

// funkcja znajdująca indeks tablicy typu int, dla którego wartość tablicy = 0
// jeśli nie ma takiego indeksu, funkcja zwraca -1
int find_empty_cell(int *arr, int len) {
    for (int i = 0; i < len; i++)
        if (arr[i] == 0)
            return(i);
    return(-1);
}

// funkcja opisująca zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
void *ThreadBehavior(void *t_data)
{
    pthread_detach(pthread_self());    //<--wątek odłączony, jak się odblokuje watek skończy automatycznie zwalniane zasoby
    struct thread_data_t *t_data_ptr = (struct thread_data_t *)t_data;

    int client_socket =  t_data_ptr->last_connected;
    printf("\nObecnie połączone gniazda:\n");
    print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
    pthread_mutex_unlock(&(t_data_ptr->thread_data_mutex));

    // odczytaj wiadomość od klienta obsługiwanego przez ten wątek
    char buf[100];
    int read_result = 1;
    int write_result;
    int file_descriptor;
    char** tokens;
    int choose_command;

    //czytamy czy byl juz taki uzytkownik
    //read_result = read(client_socket, buf, sizeof(buf));

    while(read_result > 0){
        read_result = read(client_socket, buf, sizeof(buf));
        if ( read_result == 0 ) {
            printf("Zamykam socket: %d\n", client_socket);
            exit(-1);
        }

        printf("%s\n", buf);
        buf[strcspn(buf, "\n")] = 0;
        if ( read_result == -1 ) {
            printf("Błąd przy próbie odczytu z gniazda %d\n", client_socket);
            exit(-1);
        }
        //fwrite(buf, 1, strlen(buf), stdout);
        choose_command = readCommand(tokens, buf);
        printf("Wynik rzutowania komendy: %d\n", choose_command);

        memset(buf, 0, 100);
        switch(choose_command)
        {
            case 0:
                printf("\t KOMENDA: TOUCH\n");
                touchCommand();
                sleep(15);

                break;
            case 1:
                printf("\t KOMENDA: SHARE\n");
                shareCommand();
                break;
            case 2:
                printf("\t KOMENDA: LIST\n");
                listCommand(t_data_ptr);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        }
    }

    /*
            // obsłuż utratę połączenia z klientem
        else if ( read_result == 0)
        {
            //pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
            clear_array_cell(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients, client_socket);
            //pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

            //pthread_mutex_lock(&t_data_ptr->number_of_clients_lock);
            t_data_ptr->number_of_clients--;
            //pthread_mutex_unlock(&t_data_ptr->number_of_clients_lock);

            printf("Połączenie z gniazdem %d zostało zakończone\nObecne połączone gniazda:\n", client_socket);
            print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
        }

        // wyślij odczytaną wiadomość do wszystkich podłączonych klientów
        // (poza klientem obsługiwanym przez ten wątek)

        //pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
        for (int i = 0; i < t_data_ptr->max_number_of_clients; i++)
        {
            if(t_data_ptr->client_socketfd[i] != 0 && t_data_ptr->client_socketfd[i] != client_socket)
            {
                write_result = write(t_data_ptr->client_socketfd[i], buf, strlen(buf));
                if (write_result == -1)
                {
                    printf("Błąd przy próbie wysłania wiadomości do klienta\n");
                    exit(-1);
                }
            }
        }
        //pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

        // wyczyść bufer
        memset(buf, 0, 100);
    */
    pthread_exit(NULL);
}


// funkcja obsługująca połączenie z nowym klientem
void handleConnection(int connection_socket_descriptor, struct thread_data_t *t_data_ptr)
{
    printf("Nowe połączenie. Gniazdo klienta: %d\n", connection_socket_descriptor);

    // sprawdzenie, czy jest wolne miejsce w współdzielonej tablicy z numerami połączonych gniazd
    pthread_mutex_lock(&(t_data_ptr->thread_data_mutex));
    printf("lock mutex: %d", t_data_ptr->thread_data_mutex);
    int index = find_empty_cell(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);

    if (t_data_ptr->max_number_of_clients == t_data_ptr->number_of_clients){
        printf("Limit polaczen osiagniety");
    }

    else
    {
        t_data_ptr->client_socketfd[index] = connection_socket_descriptor;
        t_data_ptr->number_of_clients++;
        t_data_ptr->last_connected = connection_socket_descriptor;

        // uchwyt na wątek
        pthread_t thread1;

        // utworzenie nowego wątku dla obsługi klienta
        // wątek wykonuje polecenia zawarte w funkcji <ThreadBehavior()>
        int create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)t_data_ptr);
        if (create_result)
        {
            printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
            exit(-1);
        }
    }
}


void initThreadStart(int max_num_of_clients, struct thread_data_t *t_data_ptr){
    // dynamiczne utworzenie współdzielonej instancji struktury
    //struct thread_data_t *t_data_ptr = malloc(sizeof(struct thread_data_t));
    t_data_ptr->client_socketfd = malloc(sizeof(int) * max_num_of_clients);
}

void createThreadClient(int max_num_of_clients, struct thread_data_t *t_data_ptr){
    t_data_ptr->number_of_clients = 0;
    t_data_ptr->max_number_of_clients = max_num_of_clients;
    t_data_ptr->last_connected = 0;
    for( int i = 0; i < max_num_of_clients; i++){
        t_data_ptr->client_socketfd[i] = 0;
    }
    t_data_ptr->name_identificator = "";
}

void initMutex(struct thread_data_t *t_data_ptr){
    if (pthread_mutex_init(&(t_data_ptr->thread_data_mutex), NULL) != 0){
        perror("\n Mutex init failed!\n");
        exit (1);
    }
}

void initAdreessServer(struct sockaddr_in *server_address){
    // Inicjalizacja adresu serwera
    memset(server_address, 0, sizeof(struct sockaddr));    //<---- UWAGA!!! Korci cie aby wrzucic to do maina? Chcesz mocno? Pamietaj aby dopisac & do server_address!!!
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = htonl(INADDR_ANY);
    server_address->sin_port = htons(SERVER_PORT);
}

void checkServerSocketDescriptor(int server_socket_descriptor, char* argv[]){
    if (server_socket_descriptor < 0){
        fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
        exit(1);
    }
}

void socketInfo(int server_socket_descriptor){
    printf("\nSocket zostal poprawnie skonfigurowany\n");
    printf("server_socket_descriptor: %d\n", server_socket_descriptor);
    printf("SOL_SOCKET: %d\n", SOL_SOCKET);
    printf("SO_REUSEADDR %d\n", SO_REUSEADDR);
    printf("\n");
}

void checkBindResult(int bind_result, char* argv[]){
    while (bind_result < 0){
        fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do socketu.\n", argv[0]);
        printf("Port zajety\n\n");
        sleep(1);
        //exit(1);
    }
}

void bindInfo(){
    printf("Poprawnie utworzono bind\n\n");
}

void checkListen(int listen_result, char* argv[]){
    if (listen_result < 0) {
        fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
        exit(1);
    }
}

void infoListen(){
    printf("Poprawnie utworzono listen\n");
    printf("QUEUE_SIZE: %d\n\n", QUEUE_SIZE);
}

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int server_socket_descriptor;
    int connection_socket_descriptor;
    int bind_result;
    int listen_result;
    char reuse_addr_val = 1;
    struct sockaddr_in server_address;
    int max_num_of_clients = 3;

    struct thread_data_t *t_data_ptr = malloc(sizeof(struct thread_data_t));

    initThreadStart(max_num_of_clients, t_data_ptr);
    createThreadClient(max_num_of_clients, t_data_ptr);
    initMutex(t_data_ptr);
    initAdreessServer(&server_address);

    // Utworzenie gniazda do połączenia z serwerem
    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    checkServerSocketDescriptor(server_socket_descriptor, argv[0]);
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));
    socketInfo(server_socket_descriptor);

    // Dowiązanie adresu serwera do stworzonego gniazda
    bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    checkBindResult(bind_result, argv[0]);
    bindInfo();

    // Włączenie nasłuchiwania na utworzonym gnieździe
    listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
    checkListen(listen_result, argv[0]);
    infoListen();

    //STWORZENIE WATKU EPOLL



    // w nieskończonej pętli: akceptuj wszystkie przychodzące połączenia po skutecznym ustaleniu połączenia z klientem, wykonuj dalsze instrukcje


    while(1){
        connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
            exit(1);
        }
        printf("Operacja accept zakonczona sukcesem\n");
        handleConnection(connection_socket_descriptor, t_data_ptr);
    }

    // zamknięcie gniazda
    close(server_socket_descriptor);

    // usuń mutexy
//    for (int i = 0; i < 3; i++)
//        pthread_mutex_destroy(locks[i]);
    pthread_mutex_destroy(&(t_data_ptr->thread_data_mutex));

    // uwalnianie pamięci
    free(t_data_ptr->client_socketfd);
    free(t_data_ptr);

    return(0);
}

/*
 cmake_minimum_required(VERSION 3.21)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(untitled1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -pthread)

find_package(Threads REQUIRED)

add_executable(untitled1 server.c)
target_link_libraries(untitled1 pthread)
 */
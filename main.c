#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5


// struktura zawierająca dane, które zostaną przekazane do wątku "klienta"
struct thread_data_t 
{
    int max_number_of_clients;

    // mutex do przypisywania gniazd do tablicy gniazd połączonych
    pthread_mutex_t client_socketfd_lock;
    int *client_socketfd;
    
    // mutex do przypisywania odpowiedniej liczby podłączonych klientów w danej chwili
    pthread_mutex_t number_of_clients_lock;
    int number_of_clients;

    // mutex do przypisywania odpowiednich numerów gniazd do odpowiednich wątków
    pthread_mutex_t last_connected_lock;
    int last_connected;         
};

// funkcja wypisująca zawartość tablicy typu int
void print_array_content(int *arr, int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", *(arr+i));
    printf("\n\n");
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
    pthread_detach(pthread_self());
    struct thread_data_t *t_data_ptr = (struct thread_data_t *)t_data;

    // assign and unlock last_connected
    int client_socket =  t_data_ptr->last_connected;
    pthread_mutex_unlock(&t_data_ptr->last_connected_lock);

    char buf[100];
    int read_result = 1;
    int write_result;

    printf("Obecnie połączone gniazda:\n");
    print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);      
    
    // odczytaj wiadomość od klienta obsługiwanego przez ten wątek
    while ( read_result > 0 )
    {
        read_result = read(client_socket, buf, sizeof(buf));
        if ( read_result == -1 )
        {
            printf("Błąd przy próbie odczytu z gniazda %d\n", client_socket);
            exit(-1);
        } 
        // obsłuż utratę połączenia z klientem
        else if ( read_result == 0)
        {
            pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
            clear_array_cell(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients, client_socket);
            pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

            pthread_mutex_lock(&t_data_ptr->number_of_clients_lock);
            t_data_ptr->number_of_clients--;
            pthread_mutex_unlock(&t_data_ptr->number_of_clients_lock);

            printf("Połączenie z gniazdem %d zostało zakończone\nObecne połączone gniazda:\n", client_socket);
            print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
        }
        
        // wyślij odczytaną wiadomość do wszystkich podłączonych klientów 
        // (poza klientem obsługiwanym przez ten wątek)
        pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
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
        pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

        // wyczyść bufer
        memset(buf, 0, 100);
    }    
    pthread_exit(NULL);
}


// funkcja obsługująca połączenie z nowym klientem
void handleConnection(int connection_socket_descriptor, struct thread_data_t *t_data_ptr) 
{
    printf("Nowe połączenie. Gniazdo klienta: %d\n", connection_socket_descriptor);

    // sprawdzenie, czy jest wolne miejsce w współdzielonej tablicy z numerami połączonych gniazd
    pthread_mutex_lock(&t_data_ptr->client_socketfd_lock);
    int index = find_empty_cell(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
    if (index == -1)
    {
        printf("Limit połączeń został przekroczony.\nObecnie połączone gniazda:\n");
        print_array_content(t_data_ptr->client_socketfd, t_data_ptr->max_number_of_clients);
        pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);
    } 
    else 
    {
        t_data_ptr->client_socketfd[index] = connection_socket_descriptor;    
        pthread_mutex_unlock(&t_data_ptr->client_socketfd_lock);

        pthread_mutex_lock(&t_data_ptr->number_of_clients_lock);
        t_data_ptr->number_of_clients++;
        pthread_mutex_unlock(&t_data_ptr->number_of_clients_lock);

        pthread_mutex_lock(&t_data_ptr->last_connected_lock);
        t_data_ptr->last_connected = connection_socket_descriptor;
        // unlock after last_connected is assigned to a variable in the thread

        // wynik funkcji tworzącej wątek
        int create_result = 0;

        // uchwyt na wątek
        pthread_t thread1;

        // utworzenie nowego wątku dla obsługi klienta
        // wątek wykonuje polecenia zawarte w funkcji <ThreadBehavior()> 
        create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)t_data_ptr);
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
    for( int i = 0; i < max_num_of_clients; i++)
    {
        t_data_ptr->client_socketfd[i] = 0;
    }
}

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

    // Zainicjuj mutexy
    pthread_mutex_t *locks[3] = {
        &(t_data_ptr->client_socketfd_lock),
        &(t_data_ptr->number_of_clients_lock), 
        &(t_data_ptr->last_connected_lock)};
    
    for (int i = 0; i < 3; i++)
        if (pthread_mutex_init(locks[i], NULL) != 0)
        {
            printf("\n mutex init failed\n");
            return 1;
        }
    
    // Inicjalizacja adresu serwera
    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    // Utworzenie gniazda do połączenia z serwerem
    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_descriptor < 0)
    {
        fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
        exit(1);
    }
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));
    printf("socket\n");

    // Dowiązanie adresu serwera do stworzonego gniazda
    bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    if (bind_result < 0)
    {
        fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n", argv[0]);
        exit(1);
    } 
    printf("bind\n");

    // włączenie nasłuchiwania na utworzonym gnieździe
    listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
    if (listen_result < 0) {
        fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
        exit(1);
    } 
    printf("listen\n");
   
    // w nieskończonej pętli: akceptuj wszystkie przychodzące połączenia
    // po skutecznym ustaleniu połączenia z klientem, wykonuj dalsze instrukcje
    // zawarte w <handleConnection()>
    while(1)
    {
        connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if (connection_socket_descriptor < 0)
        {
            fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
            exit(1);
        }
        
        printf("accept\n"); 
        handleConnection(connection_socket_descriptor, t_data_ptr);
    }

    // zamknięcie gniazda 
    close(server_socket_descriptor);

    // usuń mutexy
    for (int i = 0; i < 3; i++)
        pthread_mutex_destroy(locks[i]);    

    // uwalnianie pamięci
    free(t_data_ptr->client_socketfd);
    free(t_data_ptr);

    return(0);
}
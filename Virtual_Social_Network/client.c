#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 12345
#define BUFFER_SIZE 1024

int sock;
int running = 1;
void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (running) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            running = 0;
            break;
        }
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    pthread_t recv_thread;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("[Client] Eroare la crearea socket-ului client");
        exit(EXIT_FAILURE);
    }
    sock = client_socket;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("[Client] Eroare la conectare");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("[Client] Comenzi disponibile:\n");
printf("  Autentificare <nume> <tip> <public/privat>\n");
printf("  SetareProfil <public/privat>\n");
printf("  VizualizareProfil <nume>\n");
printf("  VizualizarePostariPublice\n");
printf("  AdaugarePrieten <nume_prieten> <tip_prietenie>\n");
printf("  AdaugareStire <destinatar> <text_stire>\n");
printf("  AdaugarePostare <public/privat> <text_postare>\n");
printf("  MesajPrivat <destinatar> <text_mesaj>\n");
printf("  Deconectare\n");

    fflush(stdout);
    // thread-ul pentru a primi notificări
    if (pthread_create(&recv_thread, NULL, receive_messages, NULL) != 0) {
        perror("[Client] Eroare la crearea thread-ului de recepție");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    while (running) {
       // printf("Introdu comanda: ");
        //fflush(stdout);
        memset(buffer, 0, BUFFER_SIZE);
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            break; 
        }    
        if (strstr(buffer, "Server: Deconectare") != NULL) {
            printf("[Client] Conexiunea a fost închisă de server.\n");
            break;
        }
        send(client_socket, buffer, strlen(buffer), 0);
    }
    pthread_join(recv_thread, NULL);
    close(client_socket);
    return 0;
}

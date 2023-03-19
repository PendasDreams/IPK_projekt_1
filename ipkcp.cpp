/*
 * @author xnovos14
 * @name   Denis Novosad
 */


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>


#define BUFSIZE 1024
#define TCP_MODE 1
#define UDP_MODE 2

static volatile int keeprunning = 1;
int client_socket, port_number, bytestx, bytesrx;
socklen_t serverlen;
const char *server_hostname;
struct hostent *server;
struct sockaddr_in server_address;
char buf[BUFSIZE];
int opt;
int mode = 0;


// funkce na zachyceni klavesy ctrl+C
void Handler(int signaling){
    printf("\n\nclosing conneciton\n");
    keeprunning = 0;
    close(client_socket);
    exit(0);
}

// funkce na vypis chyby pri spatne zadanycha argumentech + ukonceni programu
int print_error_parsing_argument(char* argv[]){
    fprintf(stderr, "usage: %s ipkcpc -h <host> -p <port> -m <mode>\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main (int argc, char * argv[]) {

signal(SIGINT, Handler);
 
    /* 1. test vstupnich parametru: */
    if (argc != 7) {
       print_error_parsing_argument(argv);
    }

    while ((opt = getopt(argc, argv, "h:p:m:")) != -1) {

        switch (opt){
        case 'h':
                server_hostname = optarg;
                break;
        case 'p': 
                port_number = atoi(optarg);
                break;
        case 'm':
                if(strcmp(optarg, "udp") == 0){
                  mode = UDP_MODE;
                  break;
                }
                else if(strcmp(optarg, "tcp") == 0){
                  mode = TCP_MODE;
                  break;
                }
                else{
                  printf("protokol byl zadán špatně\n");
                  print_error_parsing_argument(argv);
                }
                break;  
        default:
            print_error_parsing_argument(argv);
        }
    }

    /* 2. ziskani adresy serveru pomoci DNS */
    
    if ((server = gethostbyname(server_hostname)) == NULL) {
        fprintf(stderr,"ERROR: no such host as %s\n", server_hostname);
        exit(EXIT_FAILURE);
    }

    /* 3. nalezeni IP adresy serveru a inicializace struktury server_address */
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(port_number);

    /* tiskne informace o vzdalenem soketu */ 
    printf("INFO: Server socket: %s : %d \n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));
    
    // komunikace se serverem prostrednictvim UDP
    if(mode == UDP_MODE){
    
        /* Vytvoreni soketu */
        if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
        {
            perror("ERROR: socket");
            exit(EXIT_FAILURE);
        }

        printf("YOU CAN START COMUNICATION!\n");

        // cyklus na naciania a nasledne odesilani zprav serveru
        while (keeprunning) {
            /* nacteni zpravy od uzivatele */
            bzero(buf, BUFSIZE);
            fgets(buf, BUFSIZE, stdin);

            // overeni delky stringu aby nebyl vetsi nez buffer
            if(strlen(buf) > BUFSIZE){
                perror("ERROR: too long input string");
                exit(EXIT_FAILURE);
            }

            // delka vstupniho retezce muze byt 1024 znaku
            int lenght_of_input_string = (strlen(buf) - 1);

            // pole pro hexadecimalni hodnoty
            unsigned char tmp_buf[lenght_of_input_string + 2];

            printf(" ");

            // vlozeni opcodu 
            tmp_buf[0] = 0x00;
            // vlozeni delky posilaneho retezce
            tmp_buf[1] = lenght_of_input_string ;

            // vlozeni hexadecimalnich hodnot do bufferu
            for(int i = 2; i < lenght_of_input_string + 2; i++ ){
                tmp_buf[i] = buf[i-2];
            }

            /* odeslani zpravy na server */
            serverlen = sizeof(server_address);
            bytestx = sendto(client_socket, tmp_buf, lenght_of_input_string + 2, 0, (struct sockaddr *) &server_address, serverlen);
            if (bytestx < 0) 
            perror("ERROR: sendto");
            
            /* prijeti odpovedi a jeji vypsani */
            bytesrx = recvfrom(client_socket, tmp_buf, BUFSIZE, 0, (struct sockaddr *) &server_address, &serverlen);
            if (bytesrx < 0) 
                perror("ERROR: recvfrom");

            // vypis kdyz zprava prisla s operacnim kodem ze vse probehlo v poradku
            if(tmp_buf[1] == 0){
                printf("OK:");
                for(int i = 3; i < tmp_buf[2]+3; i++){
                    printf("%c", tmp_buf[i]);
                }
                printf("\n");        
            }
        
           // vypis kdyz zprava prisla s operacnim kodem ze nastala chyba
            if(tmp_buf[1] == 1){
                perror("ERR FROM SERVER:<something went wrong, try check your syntax and lenght of your message>\n");
            }
        }         
    }

    // komunikace se serverem prostrednictvim TCP
    else if (mode == TCP_MODE){

        /* Vytvoreni soketu */
        if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
        {
            perror("ERROR: socket");
            exit(EXIT_FAILURE);
        }
        
        /* nacteni zpravy od uzivatele */
        bzero(buf, BUFSIZE);
        // pripojeni se k serveru prostrednictvim TCP
        if (connect(client_socket, (const struct sockaddr *) &server_address, sizeof(server_address)) != 0)
        {
            perror("ERROR: connect");
            exit(EXIT_FAILURE);        
        }

        printf("YOU CAN START COMUNICATION!\n");

        // cyklus na naciania a nasledne odesilani zprav serveru
        while(keeprunning){

            // vynuloavni a nacteni do bufferu
            bzero(buf, BUFSIZE);
            fgets(buf, BUFSIZE, stdin);


            // overeni delky stringu aby nebyl vetsi nez buffer
            if(sizeof(buf) > BUFSIZE){
                perror("ERROR: too long input string");
                exit(EXIT_FAILURE);
            }

            /* odeslani zpravy na server */
            bytestx = send(client_socket, buf, strlen(buf), 0);
            if (bytestx < 0){
                perror("ERROR in sendto");
            }
                
            /* prijeti odpovedi a jeji vypsani */
            bzero(buf, BUFSIZE);
            bytesrx = recv(client_socket, buf, BUFSIZE, 0);
            if (bytesrx < 0){
                perror("ERROR in recvfrom");
            }
            printf("%s", buf);
            
            //po odeslani zpravy BYE je ocekavana zprava BYE ktera prijde ze serveru zpet
            if (strcmp(buf, "BYE\n") == 0){
                    close(client_socket);
                    exit(EXIT_SUCCESS);
            }
        }   
    }

    else{
        perror("ERROR: SOME ERROR OCURED");
		exit(EXIT_FAILURE);
    }
    return 0;


    
}

/*
 * IPK.2015L
 *
 * Demonstration of trivial TCP communication.
 *
 * Ondrej Rysavy (rysavy@fit.vutbr.cz)
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFSIZE 1024
#define TCP_MODE 1
#define UDP_MODE 2


int main (int argc, char * argv[]) {
	int client_socket, port_number, bytestx, bytesrx;
    socklen_t serverlen;
    const char *server_hostname;
    struct hostent *server;
    struct sockaddr_in server_address;
    char buf[BUFSIZE];
    int opt;
    int mode = 0;
    int p = -1;
    int h = -1;
    int m = -1;
   
   int print_error_parsing_argument(){
      fprintf(stderr, "usage: %s ipkcpc -h <host> -p <port> -m <mode>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

     
    /* 1. test vstupnich parametru: */

    if (argc != 7) {
       print_error_parsing_argument();
    }

    while ((opt = getopt(argc, argv, "h:p:m:")) != -1) {

        switch (opt){
        case 'h':
                h = (int)atol(optarg);
                server_hostname = optarg;
                break;
        case 'p': 
                p = (int)atol(optarg);
                port_number = atoi(optarg);
                break;
        case 'm':
                m = (int)atol(optarg);
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
                  print_error_parsing_argument();
                }
                break;  
        default:
            print_error_parsing_argument();
        }
    }

    if(p == -1){
      printf("argument -p je povinný");
      print_error_parsing_argument();
    }
    if(h == -1){
      printf("argument -h je povinný");
      print_error_parsing_argument();
    }
    if(m == -1){
      printf("argument -m je povinný");
      print_error_parsing_argument();
    }


    // TODO ověření server hostname a portnumber
    

    //protocol selection

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //                                  UDP 

    if(strcmp(argv[3] ,"udp")== 0)
    {
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
      
      /* Vytvoreni soketu */
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
      perror("ERROR: socket");
      exit(EXIT_FAILURE);
    }
        
      /* nacteni zpravy od uzivatele */
      bzero(buf, BUFSIZE);
      printf("Please enter msg: ");
      fgets(buf, BUFSIZE, stdin);
      
      if (connect(client_socket, (const struct sockaddr *) &server_address, sizeof(server_address)) != 0)
      {
      perror("ERROR: connect");
      exit(EXIT_FAILURE);        
      }

      /* odeslani zpravy na server */
      bytestx = send(client_socket, buf, strlen(buf), 0);
      if (bytestx < 0) 
        perror("ERROR in sendto");
      
      /* prijeti odpovedi a jeji vypsani */
      bytesrx = recv(client_socket, buf, BUFSIZE, 0);
      if (bytesrx < 0) 
        perror("ERROR in recvfrom");
        
      printf("Echo from server: %s", buf);
          
      close(client_socket);
      return 0;
    }


    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //                                  TCP 


    

}
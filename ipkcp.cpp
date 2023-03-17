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
#include <stdbool.h>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
std::ostringstream oss;




#define BUFSIZE 1024
#define TCP_MODE 1
#define UDP_MODE 2

   
   int print_error_parsing_argument(char* argv[]){
      fprintf(stderr, "usage: %s ipkcpc -h <host> -p <port> -m <mode>\n", argv[0]);
      exit(EXIT_FAILURE);
   }


int HexToDec(string n) { return stoi(n, 0, 16); }



int main (int argc, char * argv[]) {
	int client_socket, port_number, bytestx, bytesrx;
    socklen_t serverlen;
    const char *server_hostname;
    struct hostent *server;
    struct sockaddr_in server_address;
    char buf[BUFSIZE];
    char tmp_buf[2];
    char tmp_buf_msg[BUFSIZE];
    int opt;
    int mode = 0;
    int p = -1;
    int h = -1;
    int m = -1;






    /* 1. test vstupnich parametru: */

    if (argc != 7) {
       print_error_parsing_argument(argv);
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
                  print_error_parsing_argument(argv);
                }
                break;  
        default:
            print_error_parsing_argument(argv);
        }
    }

    if(p == -1){
      printf("argument -p je povinný");
      print_error_parsing_argument(argv);
    }
    if(h == -1){
      printf("argument -h je povinný");
      print_error_parsing_argument(argv);
    }
    if(m == -1){
      printf("argument -m je povinný");
      print_error_parsing_argument(argv);
    }


    // TODO ověření server hostname a portnumber


    //protocol selection

    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //                                  UDP 

    if(mode == UDP_MODE)
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

    bool finish_massage = false;
    int count_subs = 0;


      bzero(buf, BUFSIZE);      
      printf("Please enter msg: ");

      // //read line by line and put it to buffer
      // while(finish_massage != true)
      // {




      //
      fgets(buf, BUFSIZE - 3, stdin);

      int a = strlen(buf) + 1;
      char c = a +'0';

      printf("buffe :%d\n", a );


      for(int i = strlen(buf); i >= 0 ; i--){
        buf[i+2] = buf[i];
      }


      buf[0] ='0';
      buf[1] = c;


        printf(" this is tahat strign: %s \n",buf);
      




        strcat(tmp_buf,buf);




      



      
      if (connect(client_socket, (const struct sockaddr *) &server_address, sizeof(server_address)) != 0)
      {
      perror("ERROR: connect");
      exit(EXIT_FAILURE);        
      }

      /* odeslani zpravy na server */
      bytestx = send(client_socket,tmp_buf, BUFSIZE, 0);
      if (bytestx < 0) 
        perror("ERROR in sendto");


      printf("tmp buff velikost %ld :",strlen(buf));
      bzero(buf, BUFSIZE);      

      
      
      /* prijeti odpovedi a jeji vypsani */
      bytesrx = recv(client_socket, buf, BUFSIZE, 0);
      if (bytesrx < 0) 
        perror("ERROR in recvfrom");
        


      
     


      printf("Echo from server: %s \n", buf);

      int opcode = buf[0];

      printf("BUFFER 1: %c \n", buf[0]);

      std::string tmpstrings  = std::to_string(opcode);

      HexToDec(tmpstrings);
      printf("BUFFER 1: %d \n", opcode);

          
      close(client_socket);
      return 0;
    }

  
  


    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //                                  TCP 


    if(mode == TCP_MODE)
    {
    
    
    
    }

     return 0;

}
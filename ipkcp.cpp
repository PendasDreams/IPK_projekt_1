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
#include <string>
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
#include <bits/stdc++.h>
#include <bitset>
#include <math.h>
using namespace std;
std::ostringstream oss;




#define BUFSIZE 1024
#define TCP_MODE 1
#define UDP_MODE 2

   
   int print_error_parsing_argument(char* argv[]){
      fprintf(stderr, "usage: %s ipkcpc -h <host> -p <port> -m <mode>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

int changeEvenBits(int n)
{
    // To store sum of bits
    // at even positions.
    int to_subtract = 0;
 
    // To store bits to shift
    int m = 0;
 
    // One by one put all even
    // bits to end
    for (int x = n; x; x >>= 2) {
        // If current last bit
        // is set, add it to ans
        if (x & 1)
            to_subtract += (1 << m);
 
        // Next shift position
        m += 2;
    }
 
    return n - to_subtract;
}



char convertToBinary(unsigned int n)
{
    int i = 0;
    char binary_a [9];

    if (n / 2 != 0) {
        convertToBinary(n / 2);
        i++;
    }
    int str_1 = n % 2;
    char nuller[1] = {str_1 +'0'};
    strcat(binary_a, nuller);
    i++;

    if(i >= 8){
    
    char bin_final = strtol(binary_a, 0, 2);

    return bin_final;
    

    }
}

void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i ),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}


int main (int argc, char * argv[]) {
	int client_socket, port_number, bytestx, bytesrx;
    socklen_t serverlen;
    const char *server_hostname;
    struct hostent *server;
    struct sockaddr_in server_address;
    char buf[BUFSIZE];
    char tmp_buf[2];
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


    //protocol selectionbin_final

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

    // -4 je rezerva po posunuti hexa = dva bajty
    fgets(buf, BUFSIZE -4 , stdin);
    int lenght_of_input_string = (strlen(buf) * 2) + 1;


      
    printf("buffer pred shiftem o 2 do prava :%s\n", buf);

    for(int i = strlen(buf); i >=0; i--){
      buf[i+2] = buf[i];
  }
    
    buf[0] = 0 + '0';
    buf[1] = lenght_of_input_string + '0';

    int len = strlen(buf);
    char hex_str[(len*2)+1];

    string2hexString(buf, hex_str);

    printf("ascii_str: %s\n", buf);
    printf("hex_str: %s\n", hex_str);
    printf("buffer po shiftu o 2 do prava :%s\n", buf);
    printf("buffer po pridani opcodes :%s\n", buf);

    bzero(buf, BUFSIZE);  


    printf("Bit hodnota operacniho kodu a payloadu: %X / %X\n\n",hex_str[0], hex_str[1]);

    printf("Bit hodnota operacniho kodu a payloadu: %X / %X\n\n",hex_str[3], hex_str[4]);

    printf("bubber ready >>> %s\n", buf);

  
      if (connect(client_socket, (const struct sockaddr *) &server_address, sizeof(server_address)) != 0)
      {
        perror("ERROR: connect");
        exit(EXIT_FAILURE);        
      }

      /* odeslani zpravy na server */
      bytestx = send(client_socket,buf, BUFSIZE, 0);
      if (bytestx < 0) 
        perror("ERROR in sendto");

      
      bzero(buf, BUFSIZE);      

       
      /* prijeti odpovedi a jeji vypsani */
      bytesrx = recv(client_socket, buf, BUFSIZE, 0);
      if (bytesrx < 0) 
        perror("ERROR in recvfrom");
      

      printf("Echo from server: %s \n", buf);

      int opcode = buf[0];

      printf("Prvni char prijmute zpravy 0: %d \n", opcode);
      
      int opcode1 = buf[1];

      printf("Druhy char prijmute zpravy 1: %d \n", opcode1);

      int opcode2 = buf[2];

      printf("Treti char prijmute zpravy 2: %d \n", opcode2);
          
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

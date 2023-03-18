/*
 * IPK.2015L
 *
 * Demonstration of trivial UDP communication.
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


#define BUFSIZE 1024

int main (int argc, const char * argv[]) {
	int client_socket, port_number, bytestx, bytesrx;
    socklen_t serverlen;
    const char *server_hostname;
    struct hostent *server;
    struct sockaddr_in server_address;
    char buf[BUFSIZE];
    
     
    /* 1. test vstupnich parametru: */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(EXIT_FAILURE);
    }
    server_hostname = argv[1];
    port_number = atoi(argv[2]);
    
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
	if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
	{
		perror("ERROR: socket");
		exit(EXIT_FAILURE);
	}
	    
    /* nacteni zpravy od uzivatele */
    bzero(buf, BUFSIZE);
    printf("Please enter msg: ");

    fgets(buf, BUFSIZE, stdin);
    int lenght_of_input_string = (strlen(buf) - 1);

    unsigned char tmp_buf[lenght_of_input_string + 2];


    tmp_buf[0] = 0x00;
    tmp_buf[1] = lenght_of_input_string ;
    char buffer_na_check[lenght_of_input_string + 2];


    for(int i = 2; i < lenght_of_input_string + 2; i++ ){
        tmp_buf[i] = buf[i-2];
        buffer_na_check[i] = buf[i-2];
    }

    printf("delka stringu= %d\n", lenght_of_input_string);

    for(int i = 0; i < lenght_of_input_string + 2; i++){
        printf("char from buf[%d]: %x\n", i, tmp_buf[i]);
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

    for(int i = 0; i < 5; i++){
        printf("Echo from server(hex)  : %x\n", tmp_buf[i]);
        printf("Echo from server(int)  : %d\n", tmp_buf[i]);
        printf("Echo from server(char) : %c\n", tmp_buf[i]);
    }


    


    if(tmp_buf[1] == 0){
        printf("OK:");
            for(int i = 3; i < tmp_buf[2]+3; i++){
                printf("%c", tmp_buf[i]);
            }
        
    }
    
    if(tmp_buf[1] == 1){
        printf("ERR:<something went wrong>\n");
    }




    

    
    
    return 0;
}

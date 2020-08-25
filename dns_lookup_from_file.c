#include<stdio.h>
#include<netdb.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

#define BUFFER 100

char *dns_lookup(char *name){

    char *a;
    a = name ;
    struct hostent *host_info ;
    struct in_addr *address ;
    char *ip ;
    if((host_info=gethostbyname(a)) == NULL){
        printf("error in resolving host\n %s" , name);
        return NULL ;
    }
    address = (struct in_addr *)host_info->h_addr_list[0] ;
    ip = (char *)malloc(strlen(inet_ntoa(*address))*sizeof(char));

    ip = inet_ntoa(*address);

    return ip ;
}

int main(int argc ,int *argv[]){
    if(argc != 2){
        fprintf(stderr,"<USAGE> %s <text file containg url>\n",argv[0]);
        exit(-1);
    }
    char *file_name , address[BUFFER] , *ip;
    FILE *fp ;

    file_name = (char *)argv[1];
    if((fp =fopen(file_name,"r"))== NULL){
        fprintf(stderr,"failed to open the file\n");
        return -1 ;
    } 

    while(fgets(address,BUFFER,fp)!=NULL){
        address[strcspn(address, "\n")] = 0;
        if((ip = dns_lookup(address))!= NULL)
            printf("ADDRESS[%s]--->%s\n",address,ip);
    }

    return 0;
}
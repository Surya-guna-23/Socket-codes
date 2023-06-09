#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc , char *argv[])
{
	if(argc<2)
	{
	 fprintf(stderr,"port no not provided,program terminated\n");
	 exit(1);
 	}
	int sockfd,newsockfd,portno,n;
	char buffer[255];
	
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clien;
	
	sockfd =socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd<0)
	{
	 error("error opening socket.");
	}

 	bzero((char * ) &serv_addr , sizeof(serv_addr));
	portno= atoi(argv[1]);

	serv_addr.sin_family =AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr ,sizeof(serv_addr))<0)
		error ("binding failed");

	listen(sockfd,5);
	clien=sizeof(cli_addr);

	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clien);
	if(newsockfd < 0)
	error("error on accept");

	FILE *fp;
        int ch =0;
	fp=fopen("samp_received1.txt","a");

	int words;
	read(newsockfd,&words,sizeof(int));
	//printf("words %d",words);
	while(ch != words)
	{
		read(newsockfd,buffer,255);
		fprintf(fp,"%s ",buffer);
		ch++;
        }
	printf("the file has been reciecved successfully");
	close(newsockfd);
	close(sockfd);
	return 0;


}

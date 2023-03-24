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

	int num1, num2, ans, choice;
S:	n=write(newsockfd,"enter no 1:",strlen("enter no 1:"));
	if(n<0)
	error("error writing to socket");
	read(newsockfd,&num1,sizeof(int));
	printf("client-number 1:%d\n",num1);

	n=write(newsockfd,"enter no 2:",strlen("enter no 2:"));
	if(n<0)
	error("error writing to socket");
	read(newsockfd,&num2,sizeof(int));
	printf("client-number 2:%d\n",num2);

	n=write(newsockfd,"enter no your choice: \n 1.addition\n2.subtraction\n3.multiplication\n4.division\n5.exit\n",strlen("enter no your choice: \n 1.addition\n2.subtraction\n3.multiplication\n4.division\n5.exit\n"));
	if(n<0)
	error("error writing to socket");
	read(newsockfd,&choice,sizeof(int));
	printf("client-number 2:%d\n",choice);
	
	switch(choice)
	{

	case 1:
		ans=num1+num2;
		break;
	case 2:
		ans=num1-num2;
		break;
	case 3:
		ans=num1*num2;
		break;
	case 4:
		ans=num1/num2;
		break;
	case 5:
		goto Q;
		break;
	}

	write(newsockfd,&ans,sizeof(int));

	if(choice != 5)
		goto S;


Q:	close(newsockfd);
	close(sockfd);
	return 0;


}

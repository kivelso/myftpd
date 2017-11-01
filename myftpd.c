
#include  <string.h>     /* strlen(), strcmp() etc */
#include  <errno.h>      /* extern int errno, EINTR, perror() */
#include  <sys/types.h>  /* pid_t, u_long, u_short */
#include  <sys/socket.h> /* struct sockaddr, socket(), etc */
#include  <netinet/in.h> /* struct sockaddr_in, htons(), htonl(), */
                         /* and INADDR_ANY */

#include <time.h>

#define   SERV_TCP_PORT   40004           /* server port no */
#define   BUFSIZE         (1024*256)
#define   LOGFILE	  "log.txt"
#define MODE 0666 

//whenever this function is called it creates a log in the log file
//char* buf - the string that should describe the log
//struct soccaddr *clientAddr - clients socket to get its IP address
//uses time.h and LOGFILE and MODE aswell as all the other crap

void log(char* buf,int socketFD){


	//initiate time
	time_t t = time(NULL);

	//get ip from socket
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	int res = getpeername(socketFD, (struct sockaddr *)&addr, &addr_size);
	char *clientIP = inet_ntoa(addr.sin_addr);
	

	int fd, len;

	//connect to file	
	if ((fd = open ("LOGFILE", O_RDWR | O_CREAT |O_TRUNC, MODE)) ==  - 1)
	{
		printf("Error: unable to open or create log file\n");
		exit(1);
	}

	//create log entry
	char* log;
	sprintf(log, " %s: IP: %s. %s\n",asctime(localtime(&t)),clientIP,buf);
	
	len = strlen(log);

	//write in entry
	if(write(fd,log,len) != len){

		printf("Error: cannot write %i bytes\n", len);
		exit(1);
	}


	close(fd);
	
	
}


void directoryList(int fd, char* dir){
	//confirm directory is correct from when changed
	//execute ls command and save in string
	//send directory to client
}

void changeDirectory(int fd, char *dir){
	//change directory of process to its proffered
	//get new directory in a string
	//send a confirmation and new directory to client
}

void getFile(int fd, char *dir, char *fileName){
	//check directory and change if neccessary.
	//check if file exists
	//upload file to client
	//log fle if correct
}

void putFile(){
	//check directory and change if neccessary.
	//save filename
	//gather data and save it into a file
	//send client if successful or not
	
}



void daemon_init(void)
{
    //Requirement - daemon server

    pid_t   pid;

    if ( (pid = fork()) < 0){
         perror("fork");
         exit(1);
    } else if (pid != 0)
            exit(0);        /* parent goes bye-bye */

    /* child continues */
    setsid();               /* become session leader */
    chdir("/");             /* change working directory */
    umask(0);               /* clear our file mode creation mask */
    return;
}


void serve_a_client(int sd){

//put in serving stuff

int nr, nw, i=0;
    char buf[BUFSIZE];


     /* read data from client */
     if ((nr = read(sd, buf, sizeof(buf))) <= 0)
         exit(0);   /* connection broken down */

}


main()
{

    /* turn the program into a daemon */
     daemon_init();

     int sd, nsd, n, cli_addrlen;  pid_t pid;
     struct sockaddr_in ser_addr, cli_addr;

     /* set up listening socket sd */
     if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
           perror("server:socket"); exit(1);
     }

     /* build server Internet socket address */
     bzero((char *)&ser_addr, sizeof(ser_addr));
     ser_addr.sin_family = AF_INET;
     ser_addr.sin_port = htons(SERV_TCP_PORT);
     ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     /* note: accept client request sent to any one of the
        network interface(s) on this host.
     */

     /* bind server address to socket sd */
     if (bind(sd, (struct sockaddr *) &ser_addr, sizeof(ser_addr))<0){
           perror("server bind"); exit(1);
     }

     /* become a listening socket */
     listen(sd, 5);


     while(1){

            /* wait to accept a client request for connection */
          cli_addrlen = sizeof(cli_addr);
          nsd = accept(sd, (struct sockaddr *) &cli_addr, &cli_addrlen);

          //Requirment - multiple server connections

          if ((pid=fork()) <0) {
              perror("fork"); exit(1);
          } else if (pid > 0) {
              close(nsd);
              continue; /* parent to wait for next client */
          }

            /* now in child, serve the current client */
          close(sd); serve_a_client(nsd);

     }
}


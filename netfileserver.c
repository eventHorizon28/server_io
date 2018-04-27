#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<ctype.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<unistd.h>

#define PORT 34567
#define INT_STR_LEN 8


pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

void nopen(int sfd)
{
	int i, fd = -1, h_errno = -1;
	char param_length[INT_STR_LEN];
	char * open_path;
//cjamge the length of flags_str string
	char flags_str[2];
	char fd_str[INT_STR_LEN];
	char errno_str[INT_STR_LEN];

	read(sfd, param_length, INT_STR_LEN);

	for(i = 0; i < INT_STR_LEN; i++)
	{
		if(!isdigit(param_length[i]))
		{
			param_length[i] = '\0';
			break;
		}
	}

	open_path = (char*)malloc((atoi(param_length)+1)*sizeof(char));
	read(sfd, open_path, atoi(param_length));
	read(sfd, flags_str, 1);
	flags_str[1] = '\0';
	
	if(O_RDWR == atoi(flags_str))
		fd = open(open_path, O_RDWR);
	else if(O_RDONLY == atoi(flags_str))
		fd = open(open_path, O_RDONLY);
	else
		fd = open(open_path, O_WRONLY);

	if(fd == -1)
	{
		h_errno = errno;
		write(sfd, "fail", 4);
		sprintf(errno_str, "%d", h_errno);

		switch(strlen(errno_str))
		{
			case 0:
				printf("no string passed");
				return;
			case 1:
				sprintf(errno_str, "%d-------", h_errno);
				break;
			case 2:
				sprintf(errno_str, "%d------", h_errno);
				break;
			case 3:
				sprintf(errno_str, "%d-----", h_errno);
				break;
			case 4:
				sprintf(errno_str, "%d----", h_errno);
				break;
			case 5:
				sprintf(errno_str, "%d---", h_errno);
				break;
			case 6:
				sprintf(errno_str, "%d--", h_errno);
				break;
			case 7:
				sprintf(errno_str, "%d-", h_errno);
				break;
			case 8:
				break;
		}

		write(sfd, errno_str, INT_STR_LEN);
	}
	else
	{
		write(sfd, "pass", 4);

		sprintf(fd_str, "%d", fd);

		switch(strlen(fd_str))
		{
			case 0:
				printf("no string passed");
				return;
			case 1:
				sprintf(fd_str, "%d-------", fd);
				break;
			case 2:
				sprintf(fd_str, "%d------", fd);
				break;
			case 3:
				sprintf(fd_str, "%d-----", fd);
				break;
			case 4:
				sprintf(fd_str, "%d----", fd);
				break;
			case 5:
				sprintf(fd_str, "%d---", fd);
				break;
			case 6:
				sprintf(fd_str, "%d--", fd);
				break;
			case 7:
				sprintf(fd_str, "%d-", fd);
				break;
			case 8:
				break;
		}

		write(sfd, fd_str, INT_STR_LEN);
	}

	free(open_path);
}

int nread(int sfd)
{
	int i;
	char bytes_str[INT_STR_LEN];
	char netfd_str[INT_STR_LEN];
	int bytes_read;
	char bytes_read_str[INT_STR_LEN];
	char* read_buffer;
	int h_errno;
	char errno_str[INT_STR_LEN];
	int netfd;

	read(sfd, netfd_str, INT_STR_LEN);
	read(sfd, bytes_str, INT_STR_LEN);
	
	for(i = 0; i < INT_STR_LEN; i++)
	{
		if(!isdigit(netfd_str[i]))
		{
			netfd_str[i] = '\0';
			break;
		}
	}
	for(i = 0; i < INT_STR_LEN; i++)
	{
		if(!isdigit(bytes_str[i]))
		{
			bytes_str[i] = '\0';
			break;
		}
	}

	//MIGHT HAVE TO TAKE CARE OF NULL TERMINATION
	read_buffer = (char*)malloc(atoi(bytes_str)*sizeof(char));
	netfd = atoi(netfd_str);
	bytes_read = read(netfd, read_buffer, atoi(bytes_str));
	if(bytes_read == -1)
	{
		printf("Read error: %s, fd = %d\n", strerror(errno), atoi(netfd_str));
		h_errno = errno;
		write(sfd, "fail", 4);
		sprintf(errno_str, "%d", h_errno);

		switch(strlen(errno_str))
		{
			case 0:
				printf("no string passed");
				return;
			case 1:
				sprintf(errno_str, "%d-------", h_errno);
				break;
			case 2:
				sprintf(errno_str, "%d------", h_errno);
				break;
			case 3:
				sprintf(errno_str, "%d-----", h_errno);
				break;
			case 4:
				sprintf(errno_str, "%d----", h_errno);
				break;
			case 5:
				sprintf(errno_str, "%d---", h_errno);
				break;
			case 6:
				sprintf(errno_str, "%d--", h_errno);
				break;
			case 7:
				sprintf(errno_str, "%d-", h_errno);
				break;
			case 8:
				break;
		}

		write(sfd, errno_str, INT_STR_LEN);
	}
	else
	{
		write(sfd, "pass", 4);

		sprintf(bytes_read_str, "%d", bytes_read);

		switch(strlen(bytes_read_str))
		{
			case 0:
				printf("no string passed");
				return;
			case 1:
				sprintf(bytes_read_str, "%d-------", bytes_read);
				break;
			case 2:
				sprintf(bytes_read_str, "%d------", bytes_read);
				break;
			case 3:
				sprintf(bytes_read_str, "%d-----", bytes_read);
				break;
			case 4:
				sprintf(bytes_read_str, "%d----", bytes_read);
				break;
			case 5:
				sprintf(bytes_read_str, "%d---", bytes_read);
				break;
			case 6:
				sprintf(bytes_read_str, "%d--", bytes_read);
				break;
			case 7:
				sprintf(bytes_read_str, "%d-", bytes_read);
				break;
			case 8:
				break;
		}

		write(sfd, bytes_read_str, INT_STR_LEN);
		write(sfd, read_buffer, bytes_read);
	}

}

void * worker_thread(void * arg)
{
	int sfd = (int)(long)arg;
	int readval = 0;
	char operation[6];

	printf("STARTED\n");
	
	//start of critical section due to read fuction lock it
	//m isglobal used to init mutex
	pthread_mutex_lock(&mute);

	readval = read(sfd, operation, 5);		
	operation[5] = '\0';

	while(readval>0)
	{
		if(strcmp(operation, "open-") == 0)
		{
			nopen(sfd);
			operation[0] = '\0';
			operation[4] = '\0';
			operation[5] = '\0';
		}
		else if(strcmp(operation, "read-") == 0)
		{
			nread(sfd);
			operation[0] = '\0';
			operation[4] = '\0';
			operation[5]='\0';
		}
		/*else if(strcmp(operation, "write") == 0)
			nwrite();
		else if(strcmp(operation, "close") == 0)
			nclose();*/
		else
			break;

		readval = read(sfd, operation, 5);
		printf("readval = %d\n", readval);
	}

/*	read(new_socket, param_length, 5);

	i = 0;
	while(i<5)
	{
		if(!isdigit(param_length[i]))
		{
			param_length[i] = '\0';
			break;
		}
		i++;
	}

	printf("helloSSSSSS %s %d\n", param_length, atoi(param_length));
	buffer = (char*)malloc((atoi(param_length)+1)*sizeof(char));
	read(new_socket, buffer, atoi(param_length));
	printf("%s\n", buffer);
*/
	pthread_mutex_unlock(&mute);
	return NULL;
}

int main(int argc, char** argv)
{
	int new_socket, sfd;
	struct sockaddr_in address;
	int opt = 1, num_clients = 0;
	int addrlen = sizeof(address);
	pthread_t tid;

	char operation[6];

	sfd = -1;

	if((new_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket creation error\n");
		return -1;
	}

	if(setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
	{
		printf("setsocketopt error, errno %s\n", strerror(errno));
		return 0;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if(bind(new_socket, (struct sockaddr *)&address, sizeof(address)) == -1)
	{
		printf("bind error, %s\n", strerror(errno));
		return -1;
	}

	if(listen(new_socket, 3) == -1)
	{
		printf("listen error\n");
		return -1;
	}

//WHAT WOULD HAPPEN TO THE "SFD" IF THERE ARE MULTIPLE CALLS TO THE SERVER?
	sfd = accept(new_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);

		if(sfd == -1)
		{
			printf("accept failure\n");
			return -1;
		}
	printf("connection established\n");
	
 	read(sfd, operation, 5);
	operation[5] = '\0';

	int i = 0;
	while(i<2)
	{
		if(strcmp(operation, "open-") == 0)
		{
			nopen(sfd);
			operation[0] = '\0';
			operation[4] = '\0';
			read(sfd, operation, 5);
			operation[5] = '\0';
	
		}
		else if(strcmp(operation, "read-") == 0)
		{
			nread(sfd);
			operation[0] = '\0';
			operation[4] = '\0';
			read(sfd, operation, 5);
			operation[5] = '\0';
		}
		i++;
	}
/*
	int rc;
	
	while(1)
	{
		sfd = accept(new_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	printf("connection established\n");
	
		if(sfd == -1)
		{
			printf("accept failure\n");
			return -1;
		}
		//when they accept a client increment the counter
		num_clients++;
		
		int k=0;
		if(k<num_clients)
		{
			rc=pthread_create(&tid, NULL, worker_thread, (void *)(long)sfd);

			//printf("%d\n",rc);
			//	pthread_join(tid,NULL);
			//	printf("joinedd\n");
			if(rc)
			{
				printf("ERROR; return code from pthread_create() is %d\n", rc);
				return(-1);

			}
			pthread_detach(tid);

			num_clients--;
		}
		//if flag is == to something make swicth then send it 
		//printf("%d\n",rc);
		k++;
	}
*/
	return 0;
}

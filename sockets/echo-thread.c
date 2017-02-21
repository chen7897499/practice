/* echo-thread.c
 *
 * Copyright (c) 2000 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

/*****************************************************************************/
/*** echo-thread.c                                                         ***/
/***                                                                       ***/
/*** An echo server using threads.                                         ***/
/*****************************************************************************/

//https://www.cs.utah.edu/~swalton/listings/sockets/programs/part2/chap7/echo-thread.c

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <pthread.h>

void PANIC(char* msg);
#define PANIC(msg)  { perror(msg); exit(-1); }

struct arg_struct {
  int arg1;
  int arg2;
};

/*--------------------------------------------------------------------*/
/*--- Child - echo servlet                                         ---*/
/*--------------------------------------------------------------------*/
void* Child(void* arg)
{   char line[100];
    int bytes_read;
    int client = ((struct arg_struct  *)arg)->arg1;
    /* close(((struct arg_struct  *)arg)->arg2); */

    
    while((bytes_read = recv(client, line, sizeof(line), 0)) > 0 ){
        send(client, line, bytes_read, 0);
    }
    close(client);
    return arg;
}

/*--------------------------------------------------------------------*/
/*--- main - setup server and await connections (no need to clean  ---*/
/*--- up after terminated children.                                ---*/
/*--------------------------------------------------------------------*/
int main(void)
{   int sd;
    struct sockaddr_in addr;

    if ( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
        PANIC("Socket");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
        PANIC("Bind");
    if ( listen(sd, 20) != 0 )
        PANIC("Listen");
    while (1)
    {   int client, addr_size = sizeof(addr);
        pthread_t child;

        if((client = accept(sd, (struct sockaddr*)&addr, &addr_size)) < 0){
          perror("");
        }
        printf("Connected: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

        struct arg_struct args;
        args.arg1 = client;
        args.arg2 = sd;
        if ( pthread_create(&child, NULL, Child, (void *)&args) != 0 )
            perror("Thread creation");
        else
            pthread_detach(child);  /* disassociate from parent */
    }
    return 0;
}


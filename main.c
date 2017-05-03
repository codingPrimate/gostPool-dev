#include "main.h"
#include "socket.h"
#include "base64.h"


static char * HOST;
static int PORT;
static char * USR;
static char * PSWRD;
/*
Parse
*/
void parse(int argCount,char**arguments)
{
 if(argCount < 5) return error("./programm rpcAddr rpcPort rpcUser rpcPass");
 HOST = strdup(arguments[1]);
 PORT = atoi(arguments[2]);
 USR = strdup(arguments[3]);
 PSWRD = strdup(arguments[4]);
}
/*
End parse
*/

/*
for method
*/
char * method(char*method)
{
char * tmp = (char*)calloc(sizeof(char),MINSIZE);
sprintf(tmp,"%s:%s",USR,PSWRD);
char * token = b64_encode(tmp);
//token = 
sprintf(tmp,
"POST / HTTP/1.1\r\n"
"Host: %s:%d\r\n"
"Authorization: Basic %s\r\n"
"Accept: */*\r\n"
"content-type: text/plain;\r\n"
"Content-Length: 67\r\n"
"\r\n"
"%s\r\n"
,HOST,PORT,token,method);
return tmp;
}
/*
end for method
*/


int main(int argCount,char**arguments)
{ 
 parse(argCount,arguments);
 int Coin = InitClient( HOST, PORT );
 char * buffer;
 buffer = (char*)malloc( sizeof(char) * MINSIZE);

 char * meth = method("{\"jsonrpc\": \"1.0\", \"id\":\"test\", \"method\": \"getinfo\", \"params\": [] }");

 writeTo(Coin,meth);

 readFrom(Coin,buffer);
 printf("%s\n",buffer);

 free(meth);
 free(buffer);
 close(Coin);
 return 1;
}
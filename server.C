/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time
#include <iostream>

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK1.H"

#define PWDLAENGE 4
#define ALPLAENGE 4


class myServer : public TCPserver{
    private:
    TASK1::BlackBoxSafe *bs;
    int counter;

    public:
    myServer(int port, int msgSize);// : TCPserver(port, msgSize);
    string myResponse(string input);
    void newPwd();
    bool checkPwd(string input);
};

myServer::myServer(int port, int msgSize) : TCPserver(port, msgSize)
    {
        bs = new TASK1::BlackBoxSafe (PWDLAENGE,ALPLAENGE);
        counter = 0;
    }

bool myServer::checkPwd(string input){
    if((bs->input(input)).compare(0,13,"ACCESS DENIED")== 0)
    {
        return false;
    }
    else {
        return true;
    }
};

void myServer::newPwd(){
    delete bs;
    bs = new TASK1::BlackBoxSafe (PWDLAENGE,ALPLAENGE);
    return;
}

string myServer::myResponse(string input){
    counter ++;

        if(checkPwd(input) == false)
        {
            cout << " -----------------------" << endl;
            return string("ACCESS DENIED");
        }
        else{
            cout << " -----------------------" << endl;
            cout << "total trys: " << counter << endl;
            counter = 0;
            return string("ACCESS ACCEPTED");
        }
    }

int main(){
	srand(time(nullptr));
	myServer srv(2030,25);
	srv.run();
}

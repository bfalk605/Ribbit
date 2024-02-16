/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

#include "TASK1.H"
#include "SHA256.H"

#define PWDLAENGE 4
#define ALPLAENGE 8
#define DURCHLAUF 10

using namespace std;

class myClient : public TCPclient{
    public:
    myClient() : TCPclient(){};
    string randompwd(int lengthpwd, int lengthsymb);

};


string myClient::randompwd(int lengthpwd,int lengthsymb){

    string pwd;

    for(int i =0; i < lengthpwd; i++)
    {
        int rdmIdx = rand() %lengthsymb;
        pwd += TASK1::SYMBOLS[rdmIdx];
    }

    return pwd;
}


int main() {
	srand(time(NULL));
	myClient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);

	cout << "PWDLAENGE: " << PWDLAENGE << endl;
	cout << "ALPLAENGE: " << ALPLAENGE << endl;

	for(int i=0; i<DURCHLAUF; i++)
        {
            msg = "NEWPWD";
            c.sendData(msg);
            msg = c.receive(32);

            bool goOn=1;
            int counter=0;

            // send and receive data
            while(goOn){
                counter++;
                msg = string(c.randompwd(PWDLAENGE,ALPLAENGE));

                c.sendData(msg);
                msg = c.receive(32);

                if(msg == "ACCESS ACCEPTED")
                {
                    //cout << "Durchlauf: " << (i+1) <<" --- amount tries: " << endl;
                    cout << counter << endl;
                    counter = 0;
                    goOn = 0;
                }
        }
	}
	msg = "BYEBYE";
    c.sendData(msg);
    return 0;
}



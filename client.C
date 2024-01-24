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

#define PWDLAENGE 4
#define ALPLAENGE 8
#define DURCHLAUF 10

using namespace std;


string randompwd(int lengthpwd,int lengthsymb){

    const string characters = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
    string pwd;

    for(int i =0; i < lengthpwd; i++)
    {
        int rdmIdx = rand() %lengthsymb;
        pwd += characters[rdmIdx];
    }

    return pwd;

}

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2030);

	for(int i=0; i<DURCHLAUF; i++)
        {
            msg = "NEWPWD";
            //cout << "client sends:" << msg << endl;
            c.sendData(msg);
            msg = c.receive(32);
            //cout << "got response:" << msg << endl;

            bool goOn=1;
            int counter=0;

            // send and receive data
            while(goOn){
                counter++;
                msg = string(randompwd(PWDLAENGE,ALPLAENGE));

                //cout << "client sends:" << msg << endl;
                c.sendData(msg);

                msg = c.receive(32);
                //cout << "got response:" << msg << endl;

                if(msg == "ACCESS ACCEPTED")
                {
                    cout << "Durchlauf: " << (i+1) <<" --- amount tries: " << counter << endl;
                    //cout << "ACCESS ACCEPTED" << msg << endl;
                    //msg = string("BYEBYE");
                    //c.sendData(msg);
                    counter = 0;
                    goOn = 0;
                }
        }
	}
	msg = "BYEBYE";
    //cout << "client sends:" << msg << endl;
    c.sendData(msg);
    msg = c.receive(32);
    //cout << "got response:" << msg << endl;
}



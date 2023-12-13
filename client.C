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

//#include "TASK1.C"
//#include "TASK1.H"

using namespace std;


string randompwd(int lengthpwd){

    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string pwd;

    for(int i =0; i < lengthpwd; i++)
    {
        int rdmIdx = rand() % lengthpwd;
        pwd += characters[rdmIdx];
    }

    return pwd;

}

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

    int lengthpwd = 3;

	//connect to host
	c.conn(host , 2030);

	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
	/*
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		*/

        msg = string(randompwd(lengthpwd));

		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);

	}
}



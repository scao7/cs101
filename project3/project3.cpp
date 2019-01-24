#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
class Customer {
	public:
  	int id;
 	int arrival;
 	int duration;
 	int server;
 	int start;
 	int finish;
 	int wait;
  	Customer *next;
  	Customer(int id, int arrival, int duration);
};

class CustomerList {
public:
	int count;
	int count_served;
 	Customer *start;
  	CustomerList();
  	void add_customer(int id, int arrival, int duration);
};

Customer::Customer(int id, int arrival, int duration): 
	id(id), arrival(arrival), duration(duration), server(-1), start(-1),
      	finish(-1), wait(0), next(NULL) {}

CustomerList::CustomerList() : count(0), count_served(0), start(NULL) {}


void CustomerList::add_customer(int id, int arrival, int duration) {
	if (!start) {
    	start = new Customer(id, arrival, duration);
	} 
	else {
		Customer *cus = start;
   		while (cus->next) {
   	   	cus = cus->next;
   		}
   		cus->next = new Customer(id, arrival, duration);
 	}
  ++count;
}
enum CRITERIA { MIN_DURA, MAX_DURA, MIN_WAIT, MAX_WAIT, DURA_GT_5, DURA_LT_5 };
void release_servers(CustomerList *cuslst, bool servers[], int n_servers, int time);
Customer *find_by(CustomerList *cuslst, int time, CRITERIA c);
int option_0(CustomerList *cuslst, bool servers[], int n_servers);
int option_1(CustomerList *cuslst, bool servers[], int n_servers);
int option_2_4_6(CustomerList *cuslst, bool servers[], int n_servers, CRITERIA c);
int option_3_5_7(CustomerList *cuslst, bool servers[], int n_servers,CRITERIA c);
int option_8_9(CustomerList *cuslst, bool servers[], int n_servers, CRITERIA c);

int main(int argc, char *argv[]) {
 	 // ---- validate arguments ----

 	if (argc != 3) {
	// number of arguments doesn't equal 3
   	cerr << "Please set command line correct"<<endl;
    	return 1;
  	}	

 	 int n_servers = atoi(argv[1]);

 	 int option = atoi(argv[2]);
	// number of servers can't suit for the 8 and 9 option 
 	 if (option > 7 && n_servers == 1) {
   		 cerr << "number of servers can't suit for the 8 and 9 option"<<endl;
   	 return 1;
  }

  // ---- create customer list from stdin ----

  	CustomerList cuslst;
 	int id;
 	int arrival;
  	int duration;
  	while (cin >> id >> arrival >> duration) {
    	cuslst.add_customer(id, arrival, duration);
  	}

  	if (cuslst.count == 0) {
    	cerr << "no customers found\n";
    	return 1;
  	}

  // ---- create servers ----

  	bool servers[n_servers];
  	for (int i = 0; i < n_servers; ++i) {
    	servers[i] = false;
  	}

  // ---- simulate with different options ----

  	int lastest_finished;

  	switch (option) {
  	case 0:
    	lastest_finished = option_0(&cuslst, servers, n_servers);
    	break;
  	case 1:
    	lastest_finished = option_1(&cuslst, servers, n_servers);
    	break;
  	case 2:
    	lastest_finished = option_2_4_6(&cuslst, servers, n_servers, MIN_DURA);
    	break;
  	case 3:
    	lastest_finished = option_3_5_7(&cuslst, servers, n_servers, MIN_DURA);
    	break;
  	case 4:
    	lastest_finished = option_2_4_6(&cuslst, servers, n_servers, MAX_DURA);
    	break;
  	case 5:
    	lastest_finished = option_3_5_7(&cuslst, servers, n_servers, MAX_DURA);
    	break;
  	case 6:
    	lastest_finished = option_2_4_6(&cuslst, servers, n_servers, MAX_WAIT);
    	break;
  	case 7:
    	lastest_finished = option_3_5_7(&cuslst, servers, n_servers, MAX_DURA);
    	break;
  	case 8:
    	lastest_finished = option_8_9(&cuslst, servers, n_servers, DURA_GT_5);
    	break;
  	case 9:
    	lastest_finished = option_8_9(&cuslst, servers, n_servers, DURA_LT_5);
    	break;
  	}

  // ---- print results ----

  	cout << "Option " << option << ":\n\n";
  	cout << "Server Customer Start Finish Wait\n";

  	int total_wait = 0;
  	int longest_wait = 0;
  	Customer *cus = cuslst.start;
  	while (cus) {
   	 	printf("%4d    %4d   %4d   %4d  %4d\n", cus->server, cus->id, cus->start,cus->finish, cus->wait);
   	 	total_wait += cus->wait;
   	 	if (cus->wait > longest_wait) {
     	 	longest_wait = cus->wait;
   	 	}
   	 	cus = cus->next;
 	}
	double avg_wait = (double)total_wait / cuslst.count;

 	printf( "\nTotal Wait = %d\nAverage Wait = %f\nLongest Wait = %d\nLatest Finish " "= %d\n",
      	total_wait, avg_wait, longest_wait, lastest_finished);

  	return 0;
}

void release_servers(CustomerList *cuslst, bool servers[], int n_servers,int time) {
  	Customer *cus = cuslst->start;
  	while (cus) {
    	if (cus->server != -1 && cus->start + cus->duration == time) {
      	// finishing
      	cuslst->count_served++;
      	cus->finish = time;
      // release server
      	servers[cus->server] = false;
    	}
    	cus = cus->next;
  	}
}	

Customer *find_by(CustomerList *cuslst, int time, CRITERIA c) {
  	Customer *cus = cuslst->start;
 	Customer *cus_target = NULL;
  	int val = -1;

  	switch (c) {
  	case MIN_DURA:
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        		if (val == -1) {
          		val = cus->duration;
          		cus_target = cus;
        		} 
			else if (val > cus->duration) {
          		val = cus->duration;
          		cus_target = cus;
        		}
      		}
      	cus = cus->next;
    	}
    	break;
  	case MAX_DURA:
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        		if (val == -1) {
          		val = cus->duration;
          		cus_target = cus;
        		} 
			else if (val < cus->duration) {
          		val = cus->duration;
          		cus_target = cus;
        		}
      		}
      	cus = cus->next;
    	}	
    	break;
  	case MIN_WAIT:
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        		if (val == -1) {
          		val = cus->wait;
          		cus_target = cus;
        		} 
			else if (val > cus->wait) {
          		val = cus->wait;
          		cus_target = cus;
        		}
      		}	
      	cus = cus->next;
    	}
    	break;
  	case MAX_WAIT:
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        		if (val == -1) {
          			val = cus->wait;
          			cus_target = cus;
        		} 
			else if (val < cus->wait) {
          		val = cus->wait;
          		cus_target = cus;
        		}
      		}
      		cus = cus->next;
    	}
    	break;
  	case DURA_GT_5:
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        		if (cus->duration > 5) {
          		cus_target = cus;
          		break;
        		}
      		}
      		cus = cus->next;
    	}	
    	break;
  	case DURA_LT_5:
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        		if (cus->duration < 5) {
          		cus_target = cus;
          		break;
        		}
      		}
      		cus = cus->next;
    	}
    	break;
  	}

  	return cus_target;
}

int option_0(CustomerList *cuslst, bool servers[], int n_servers) {
  	int time = 0;

  	while (cuslst->count > cuslst->count_served) {
    	// release servers
    		release_servers(cuslst, servers, n_servers, time);
    // try serving customers
    		Customer *cus = cuslst->start;
    		while (cus) {
      			if (cus->server == -1 && cus->arrival <= time) {
        // arrived and waiting
        			bool served = false;
        			for (int i = 0; i < n_servers; ++i) {
          				if (!servers[i]) {
            // server available for customer
            // starting
            				servers[i] = true; // occupy server
            				cus->server = i;
            				cus->start = time;
            				served = true;
            				break;
          				}
        			}	
        			if (!served) {
          // waiting
          			++cus->wait;
        			}
      			}
      			cus = cus->next;
    		}

    		time++;
  	}	

  return time - 1;
}

int option_1(CustomerList *cuslst, bool servers[], int n_servers) {

  	int time = 0;
  	int turn = 0;

  	while (cuslst->count > cuslst->count_served) {
    // release servers
    	release_servers(cuslst, servers, n_servers, time);
    // try serving customers
    	Customer *cus = cuslst->start;
    	while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        // arrived and waiting
        		if (!servers[turn]) {
          // server available for customer
          // starting
          		servers[turn] = true; // occupy server
          		cus->server = turn;
          		cus->start = time;
          		turn = (turn + 1) % n_servers;
        		} 
			else {
          // waiting
          			++cus->wait;
        		}
      		}
      		cus = cus->next;
    	}

    		time++;
  	}

  	return time - 1;
}

int option_2_4_6(CustomerList *cuslst, bool servers[], int n_servers,
                 CRITERIA c) {

  	int time = 0;

  	while (cuslst->count > cuslst->count_served) {
    // release servers
    	release_servers(cuslst, servers, n_servers, time);
    // find targeted customer
    	Customer *cus_target = find_by(cuslst, time, c);
    // try serving customers
    	Customer *cus = cuslst->start;
    	while (cus) {
      	if (cus->server == -1 && cus->arrival <= time) {
        // arrived and waiting
        	bool served = false;
        	if (cus_target == cus) {
          	for (int i = 0; i < n_servers; ++i) {
            	if (!servers[i]) {
              // server available for targeted customer
              // starting
              	servers[i] = true; // occupy server
              	cus->server = i;
              	cus->start = time;
              	served = true;
              	break;
            	}
          	}
        	}	
        	if (!served) {
          // waiting
          	cus->wait++;
        	}
      	}
      	cus = cus->next;
    	}

    	time++;
  	}

  	return time - 1;
}

int option_3_5_7(CustomerList *cuslst, bool servers[], int n_servers,
                 CRITERIA c) {

  	int time = 0;
  	int turn = 0;

  	while (cuslst->count > cuslst->count_served) {
    // release servers
    		release_servers(cuslst, servers, n_servers, time);
    // find targeted customer
    		Customer *cus_target = find_by(cuslst, time, c);
    // try serving customers
    		Customer *cus = cuslst->start;
    		while (cus) {
      		if (cus->server == -1 && cus->arrival <= time) {
        // arrived and waiting
        		if (!servers[turn] && cus_target == cus) {
          // server available for targeted customer
          // starting
          		servers[turn] = true; // occupy server
          		cus->server = turn;
          		cus->start = time;
          		turn = (turn + 1) % n_servers;
        		} 
			else {
          // waiting
          		cus->wait++;
        		}
      		}
      		cus = cus->next;
    		}

    		time++;
  	}	

  	return time - 1;
}

int option_8_9(CustomerList *cuslst, bool servers[], int n_servers,
               CRITERIA c) {

  	int time = 0;

  	while (cuslst->count > cuslst->count_served) {
    // release servers
    	release_servers(cuslst, servers, n_servers, time);
    // find targeted customer
    	Customer *cus_target = find_by(cuslst, time, c);
    // try serving customers
    	Customer *cus = cuslst->start;
    	while (cus) {
      	if (cus->server == -1 && cus->arrival <= time) {
        // arrived and waiting
        	bool served = false;
        	if (!servers[0] && cus_target == cus) {
          // server #0 available for targeted customer
          // starting
          	servers[0] = true; // occupy server
          	cus->server = 0;
          	cus->start = time;
          	served = true;
        	}
		else {
          	for (int i = 1; i < n_servers; ++i) {
            		if (!servers[i] && cus_target != cus) {
              // other servers available for non-targeted customer
              // starting
              		servers[i] = true; // occupy server
              		cus->server = i;
              		cus->start = time;
              		served = true;
              		break;
            		}
          	}	
        	}	
        	if (!served) {
          // waiting
          	cus->wait++;
        	}
      	}
      		cus = cus->next;
    	}

    	time++;
  }

  	return time - 1;
}






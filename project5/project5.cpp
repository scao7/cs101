#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;
class Data {
public:
	int count;             // number of integers in data
  	int n_dims;            // number of dimensions
  	int *data;             // data
  	int *dims;             // dimensions
  	int *zero_pos;         // position of zero
  	int dist;              // total distance
  	string hash;      // hashed value
  	vector<int> hist; // move history

  	Data(void);          // default constructor
  	Data(const Data &d); // copy constructor
  	~Data(void);         // destructor

  	void read(void); // read data from stdin

  	string calc_hash(void) const; // calculate hashed value
  	void fill_pos(int *pos,int index) const; // convert 1-dim index to n-dim position
  	int index_of(int *pos) const;   // convert n-dim position to 1-dim index
  	int calc_dist(void) const;      // calculate total distance
  	void print_data(void) const;    // print data (debug purpose)

  	void move(int dim, int dist); // make a move

  	Data &operator=(const Data &d);      // assignment operator
  	bool operator<(const Data &d) const; // less-than operator
};
/////////////////////////////////////////

Data::Data(void)
   	: count(0), n_dims(0), data(NULL), dims(NULL), zero_pos(NULL), dist(0),
     	hash("") {}

Data::Data(const Data &d)
    	: count(d.count), n_dims(d.n_dims), data(new int[d.count]),
      	dims(new int[d.n_dims]), zero_pos(new int[d.n_dims]), dist(d.dist),
      	hash(d.hash), hist(d.hist) {
  	memcpy(data, d.data, count * sizeof(int));
  	memcpy(dims, d.dims, n_dims * sizeof(int));
  	memcpy(zero_pos, d.zero_pos, n_dims * sizeof(int));
}

Data::~Data(void) {
  	if (data) {
    		delete[] data;
    		delete[] dims;
    		delete[] zero_pos;
  	}
}

void Data::read(void) {
  	if (data) {
    		delete[] data;
    		delete[] dims;
    		delete[] zero_pos;
  	}
  	cin >> n_dims; // read number of dimensions
  	dims = new int[n_dims];
  	count = 1;
  	for (int i = 0; i < n_dims; i++) { // read dimensions
    		cin >> dims[i];
    		count *= dims[i];
  	}
  	data = new int[count];
  	zero_pos = new int[n_dims];
  	for (int i = 0; i < count;) { // read data
    		int x = 0;
    		if (cin >> x) {
      			data[i] = x;
      		if (x == 0) {
        		fill_pos(zero_pos, i);
      		}	
      		++i;
    		} 
		else {
      			cin.clear();
      			cin.ignore(1);
    		}
  	}
  	dist = calc_dist(); // calculate the total distance
  	hash = calc_hash(); // calculate the hashed value
}

string Data::calc_hash(void) const {
  	ostringstream oss;
  	for (int i = 0; i < count; i++) {
    		oss << data[i] << '-';
  	}	
  	return oss.str();
}

void Data::fill_pos(int *pos, int index) const {
  	int *dims_dup = new int[n_dims];
  	memcpy(dims_dup, dims, n_dims * sizeof(int));
  	for (int i = 1; i < n_dims; i++) {
    		for (int j = i + 1; j < n_dims; j++) {
      			dims_dup[i] *= dims[j];
    		}
  	}
  	for (int i = 1; i < n_dims; i++) {
    		pos[i - 1] = index / dims_dup[i];
    		index %= dims_dup[i];
  	}
  	pos[n_dims - 1] = index;
}

int Data::index_of(int *pos) const {
  	int *pos_dup = new int[n_dims];
  	memcpy(pos_dup, pos, n_dims * sizeof(int));

  	for (int i = 0; i < n_dims - 1; i++) {
    		for (int j = i + 1; j < n_dims; j++) {
      			pos_dup[i] *= dims[j];
    		}
  	}

  	int index = 0;
  	for (int i = 0; i < n_dims; i++) {
    		index += pos_dup[i];
  	}
  	delete[] pos_dup;

  	return index;
}

int Data::calc_dist(void) const {
  	int dist = 0;
  	for (int i = 0; i < count; i++) {
    		if (data[i] != 0) {
      			dist += abs(i - data[i]);
    		}
  	}
  	return dist;
}

void Data::print_data(void) const {
  	cout << "data: ";
  	for (int i = 0; i < count; i++) {
    	cout << data[i] << ' ';
  	}
  	cout << endl;
  	cout << "zero: ";
  	for (int i = 0; i < n_dims; i++) {
    		cout << zero_pos[i] << ' ';
  	}
  	cout << endl;
  	cout << "dist: ";
  	cout << dist;
  	cout << endl;
}

void Data::move(int dim, int dist) {
  	hist.push_back(dim);  // record dimension
  	hist.push_back(dist); // record distance

  	// normalize position
  	int *pos = new int[n_dims];
 	memcpy(pos, zero_pos, n_dims * sizeof(int));
  	pos[dim] += dist;
  	while (pos[dim] < 0) {
    		pos[dim] += dims[dim];
  	}
  	pos[dim] %= dims[dim];

  	// for (int k = 0; k < n_dims; ++k) {
  	//   cout << zero_pos[k] << " oooo " << dims[k] << endl;
  	// }

  	int i = index_of(zero_pos);
  	int j = index_of(pos);

  	// cout << i << " xxx " << j << endl;

  	// calculate delta distance
  	int delta_dist = (abs(data[j] - i)) - (abs(data[j] - j));

  	// swap
  	int x = data[i];
  	data[i] = data[j];
  	data[j] = x;

  	memcpy(zero_pos, pos, n_dims * sizeof(int));

  	delete[] pos;

  	// alter total distance
  	this->dist += delta_dist;
  	// re-calculate hashed value
  	hash = calc_hash();
}

Data &Data::operator=(const Data &d) {
  	if (this == &d) { // self assignment
    		return *this;
  	}
  	if (data) {
    		delete[] data;
    		delete[] dims;
    		delete[] zero_pos;
  	}
  	count = d.count;
  	n_dims = d.n_dims;
  	data = new int[count];
  	dims = new int[n_dims];
  	zero_pos = new int[n_dims];
  	memcpy(data, d.data, count * sizeof(int));
  	memcpy(dims, d.dims, n_dims * sizeof(int));
  	memcpy(zero_pos, d.zero_pos, n_dims * sizeof(int));
  	dist = d.dist;
  	hash = d.hash;
  	hist = d.hist;

  	return *this;
}

bool Data::operator<(const Data &d) const {
  	// used by priority queue
  	// less dist, higher priority
  	return dist > d.dist;
}
/////////////////////////////////////////
/* driver */

int main(void) {

  	Data d;                  // the first data object;
  	set<string> visited;     // set to contain visited hashed value
  	priority_queue<Data> pq; // priority queue to contain data object

  	d.read();               // fill it in
  	pq.push(d);             // push the first data object into queue
  	visited.insert(d.hash); // record its hashed value

  	int n_dims = d.n_dims;
  	int *dims = new int[n_dims];

  	memcpy(dims, d.dims, n_dims * sizeof(int));

  	while (!pq.empty()) { // when the queue is not empty

    	Data _d_ = pq.top(); // get the most promising data object

    	pq.pop(); // pop it out

//	    _d_.print_data(); // debug

    	if (_d_.dist == 0) { // distance is zero means it's done!
      	// print move history
      	vector<int>::iterator it;
      	int i;
      	for (it = _d_.hist.begin(), i = 1; it != _d_.hist.end(); it++, i++) {
        	if (i == 2) {
          		i = 0;
          		cout << *it << endl;
        	} 
		else {
          	cout << *it << ' ';
        	}
      	}
      	break;
    	}

    // iterate all dimensions
    for (int dim = 0; dim < n_dims; dim++) {

      	if (dims[dim] < 2) {
        	continue;
      	}

      	// distance = 1
      	Data _d0_ = _d_;   // copy data object
     	_d0_.move(dim, 1); // make a move
      	if (visited.find(_d0_.hash) == visited.end()) {
        	// hashed value not found in set
        	// add new data object to queue
        	pq.push(_d0_);
        	visited.insert(_d0_.hash); // record its hashed value
      	}

      	if (dims[dim] < 3) {
        	continue;
      	}

      // distance = -1
      	Data _d1_ = _d_;    // copy data object
      	_d1_.move(dim, -1); // make a move
      	if (visited.find(_d1_.hash) == visited.end()) {
        	// hashed value not found in set
        	// add new data object to queue
        	pq.push(_d1_);
        	visited.insert(_d1_.hash); // record its hashed value
      	}
    }
  }

  delete[] dims;

  return 0;
}

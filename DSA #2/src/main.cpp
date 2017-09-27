// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
void insertion_sort(list<Data *> &);
bool comp_T1(Data *a, Data *b);
bool comp_T1a(Data *a, Data *b);
bool comp_T3(Data *a, Data *b);
bool comp_T4(Data *a, Data *b);
Data *arr[1010000]; //arr of 1,010,000 elements

Data *buckets [100000][30];        //buckets sort preparation
int num_filled[100000];
int a,b,c,d,e,sum;//used for bucket sort
string temp;


void sortDataList(list<Data *> &l) {
    list<Data *>::iterator iterator = l.begin();
    int size = l.size();

// determine which T case and change char to integers
    // T1 SORT
    if (size <= 110000){
        cout << "Taking T1.txt " << endl;
        for (iterator = l.begin(); iterator != l.end(); iterator++) {
            temp = (*iterator)->data;
            a = b= c= d = e = sum = 0;

            if (temp[20] == '.') {
                a = temp[0] - 48;
                b = temp[1] - 48;
                c = temp[2] - 48;
                d = temp[3] - 48;
                e = temp[4] - 48;
            }
            else if(temp[19] == '.') {
                b = temp[0] - 48;
                c = temp[1] - 48;
                d = temp[2] - 48;
                e = temp[3] - 48;
            }
            else if(temp[18] == '.') {
                c = temp[0] - 48;
                d = temp[1] - 48;
                e = temp[2] - 48;
            }
            else if(temp[17] == '.') {
                d = temp[0] - 48;
                e = temp[1] - 48;
            }
            else if(temp[16] == '.') {
                e = temp[0] - 48;
            }
            sum = 10000*a + 1000*b + 100*c + 10*d + e;
            buckets[sum][num_filled[sum]] = *iterator;
            num_filled[sum]++;
        }

        for (int i = 0; i<100000; i++) {
            sort( buckets[i], buckets[i] + num_filled[i], comp_T1 );
        }
        
        iterator = l.begin();
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j< num_filled[i]; j++) {
                *iterator = buckets[i][j];
                iterator++;
            }
        }
    } //T1 case
    
    
    
    else if ((*iterator)->data.length() < 8){
        cout << "Taking T3.txt " << endl;
        int temp2;
        for (iterator = l.begin(); iterator != l.end(); iterator++) {
            temp = (*iterator)->data;
            temp2 = temp.length();
            a = b = c = d = e = sum = 0;

            if (temp[3] == '.') {
                a = temp[0] - 48;
                b = temp[1] - 48;
                c = temp[2] - 48;
                d = temp[4] - 48;
                if(temp2 > 5)
                    e = temp[5] - 48;
            }
            else if(temp[2] == '.') {
                b = temp[0] - 48;
                c = temp[1] - 48;
                d = temp[3] - 48;
                if(temp2 > 4)
                    e = temp[4] - 48;
            }
            else {
                c = temp[0] - 48;
                d = temp[2] - 48;
                if(temp2 > 3)
                    e = temp[3] - 48;
            }

            sum = 10000*a + 1000*b + 100*c + 10*d + e;
            buckets[sum][num_filled[sum]] = *iterator;
            num_filled[sum]++;
        }
        
        for (int i = 0; i<100000; i++) {
            sort( buckets[i], buckets[i] + num_filled[i], comp_T3 );
        }
        
        iterator = l.begin();
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j< num_filled[i]; j++) {
                *iterator = buckets[i][j];
                iterator++;
            }
        }
    }
    
    
    else if ( (*l.begin())->data.substr(0,8) == (*(++l.begin()))->data.substr(0,8) ){
        cout << "Taking T4.txt " << endl;
        insertion_sort(l);
    }

    
    else {
        cout << "Taking T2.txt " << endl;
        for (iterator = l.begin(); iterator != l.end(); iterator++) {
            temp = (*iterator)->data;
            a = b = c = d = e = sum = 0;

            if (temp[20] == '.') {
                a = temp[0] - 48;
                b = temp[1] - 48;
                c = temp[2] - 48;
                d = temp[3] - 48;
                e = temp[4] - 48;
            }
            else if(temp[19] == '.') {
                b = temp[0] - 48;
                c = temp[1] - 48;
                d = temp[2] - 48;
                e = temp[3] - 48;
            }
            else if(temp[18] == '.') {
                c = temp[0] - 48;
                d = temp[1] - 48;
                e = temp[2] - 48;
            }
            else if(temp[17] == '.') {
                d = temp[0] - 48;
                e = temp[1] - 48;
            }
            else if(temp[16] == '.') {
                e = temp[0] - 48;
            }
            sum = 10000*a + 1000*b + 100*c + 10*d + e;
            buckets[sum][num_filled[sum]] = *iterator;
            num_filled[sum]++;
        }

        sort( buckets[0], buckets[0] + num_filled[0], comp_T1a );
        for (int i = 1; i<100000; i++) {
            sort( buckets[i], buckets[i] + num_filled[i], comp_T1 );
        }
        
        iterator = l.begin();
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j< num_filled[i]; j++) {
                *iterator = buckets[i][j];
                iterator++;
            }
        }
    }
}

//Comparison functions for sort()  
bool comp_T1(Data *a, Data *b){
    return (a->data.compare(b->data) < 0);
}
bool comp_T1a(Data *a, Data *b){
    int a_dec = 15;
    int b_dec = 15;
    while ( a->data[a_dec] != '.' ){
        a_dec--;
    }
    while ( b->data[b_dec] != '.' ){
        b_dec--;
    }
    if (a_dec != b_dec)
        return (a_dec - b_dec < 0);
    else
        return (a->data.compare(b->data) < 0);
}

bool comp_T3(Data *a, Data *b){
    return (a->data.compare(b->data) < 0);
}

bool comp_T4(Data *a, Data *b){
    return (a->data.compare(b->data) < 0);
}


// Insertion sort for T4
void insertion_sort(list<Data *> &l){
    int i = 0,j=1;
    list<Data *>::iterator iterator;
    for (iterator = l.begin(); iterator != l.end(); ++iterator){
        arr[i++] = *iterator;
    }
    int q = l.size();
    for (int i = 1; i < q ; i++){
        j = 1;
        while ( (i - j >= 0) && comp_T4(arr[i],arr[i-j]) ){
            j++;
        }
        if (j > 1){
            Data *temp = arr[i];
            int k = j;
            for (; j > 1; j--){
                arr[i + j - k] = arr[i + j - k - 1];
            }
            arr[i - k + 1] = temp;
        }
    }
    i = 0;
    for (iterator = l.begin(); iterator != l.end(); ++iterator){
        *iterator = arr[i++];
    }
    return;
}
















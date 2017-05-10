#include <iostream>
#include "md5.h"
#include "Blowfish.h"
#include "utf8.h"
#include <ctime>


using namespace std;


class encryp_decrypt{
private:
    char key[100];
    vector<char> phase,keys, values;
    char keysdata[1000];
    char temps[10000];
    void rnd()
    {
        srand(time(NULL));
        int temp;
        for(int i = 0; i<100;i++)
        {
            temp = rand()% 126 + 33;
            key[i] = (char)temp;
        }
    }

    vector<char> manupulatoe(vector<char> &keyvalue,vector<char> &encvalue){
        vector<char> mainvector;
        int i=0;
        for(i=0;i < keyvalue.size();i++){
            mainvector.push_back(keyvalue[i]);
        }
        for(i=0;i < encvalue.size();i++){
            mainvector.push_back(encvalue[i]);
        }
        return mainvector;
    }

    vector<char> chartovector(char *chararray)
    {
        vector<char> v;
        if(chararray == NULL)
        {
            exit(0);
        }
        for(int i = 0; chararray[i]!='\0';i++)
        {
            v.push_back(chararray[i]);
        }

        return v;
    }
    void vectortochar(char *chararray, vector<char> &v) {
        for (int i = 0; i < v.size(); i++) {
            chararray[i] = v[i];
        }

    }


    void display(vector<char> &v)
    {
        for(int i = 0; i < v.size(); i++)
        {
            cout << v[i];
        }
//        cout << "\n" << endl;
    }
    vector<char> keyfetcher(vector <char> &v){
        vector<char> key;
        int i=0;
        for(i=0;i<100;i++){
            key.push_back(v[i]);
        }
        return key;
    }
    vector<char> phasefetcher(vector<char> &v){
        vector<char> phase;
        for(int i=100;i<v.size();i++){
            phase.push_back(v[i]);
        }
        return phase;
    }
    void checktype(char *temp, int size){
        int i;
//        cout<<endl;
//        cout<<size;
//        cout<<endl;
        for(i=0;i< size;i++){
            cout << (int)temp[i] ;
            if(i!=size-1){
                cout<< ",";
            }
        }
        cout << endl;
    }

    vector<string> explode(const string& str, const char& ch) {
        string next;
        vector<string> result;

        // For each character in the string
        for (string::const_iterator it = str.begin(); it != str.end(); it++) {
            // If we've hit the terminal character
            if (*it == ch) {
                // If we have some characters accumulated
                if (!next.empty()) {
                    // Add them to the result vector
                    result.push_back(next);
                    next.clear();
                }
            } else {
                // Accumulate the next character into the sequence
                next += *it;
            }
        }
        if (!next.empty())
            result.push_back(next);
        return result;
    }

    char * thecovertor(string st){
        vector<string> sts = explode(st,',');
        int temp[10000];

        for (int i = 0; i < sts.size(); i++) {
            temp[i] = stoi(sts[i]);
            temps[i] = (char)temp[i];
//            cout<<temps[i]<<" "<<temp[i];

        }
        return temps;
    }


public:
    void encryptfunction(char *value) {
        rnd();
        if (value == NULL) {
            exit(1);
        }
        int i;
        keys = chartovector(key);
        Blowfish b(keys);
        phase = chartovector(value);
        values = b.Encrypt(phase);
        vector<char> newdata;
        vectortochar(keysdata,values);
        values=manupulatoe(keys,values);
        vectortochar(keysdata,values);
        string str(md5(keysdata));
        cout<<values.size();
        cout<<str<<" ";
        checktype(keysdata,values.size());
    }

    void decryptfucntion(char *md5hash, string encodephase) {
        if((md5hash == NULL)){
            cout<<"no value";
            exit(1);
        }
        char *temps = thecovertor(encodephase);
//        exit(1);
        cout<<encodephase<<endl;
        string s2(md5hash);
        string s1(md5(temps));
        cout<<s1 <<" "<<s2<<endl;
        vector<char> enc_vec;
        enc_vec = chartovector(temps);
        keys = keyfetcher(enc_vec);
        phase = phasefetcher(enc_vec);
        cout<<keys.size()<<" "<<phase.size()<<endl;
        Blowfish b(keys);
        vector<char> origanldata;
        origanldata = b.Decrypt(phase);
        display(origanldata);
        cout<<endl;
        if(s1.compare(s2)==0){
            // main decryption in cpp
            vector<char> enc_vec;
            enc_vec = chartovector(temps);
            keys = keyfetcher(enc_vec);
            phase = phasefetcher(enc_vec);
            cout<<keys.size()<<" "<<phase.size()<<endl;
            Blowfish b(keys);
            vector<char> origanldata;
            origanldata = b.Decrypt(phase);
            display(origanldata);
            cout<<endl;
        }
    }

};

int main ( int argc, char *argv[] )
{
    encryp_decrypt e;
    if(argc == 2){
        e.encryptfunction(argv[1]);
    } else if(argc==3){
        string s(argv[1]);
        e.decryptfucntion(argv[2],s);
    } else{
        cout<<argv[0]<<" <value to encrypt>"<<endl;
        cout<<argv[0]<<" <value to decrypt>"<<" <md5 hash>"<<endl;

    }


    return 0;
}

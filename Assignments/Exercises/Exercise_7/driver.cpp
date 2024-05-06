#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long mod_inverse(long a, long m) {
    a = a % m;
    for (long x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

long calculate_d(long p, long q, long e) {
    long n = p * q;
    long phi = (p - 1) * (q - 1);
    long d = mod_inverse(e, phi);
    return d;
}

//i^e (mod n)
long powm( long i, long e, long n ) {
	long r = 1;
	for ( long j = 0; j<e; ++j ) r = (r*i)%n;
	return r;
}


int main(){
    for(int FILENUM = 0; FILENUM < 6; FILENUM++){
        try{
            ifstream inFile("Exercise7_" + to_string(FILENUM) + "_to_student.txt");
            ofstream outFile("Exercise7_Misyutin_" + to_string(FILENUM) + "_answers.txt");
            string word;
            string studentName;
            long p;
            long q;
            long e;
            long encryptedMessage;
            long n;
            long d;
            long phiN;

            while(inFile >> word){
                if (word == "studentName") {
                    inFile >> studentName;
                }
                else if (word == "p"){
                    inFile >> word;
                    p = stoi(word);
                }
                else if (word == "q"){
                    inFile >> word;
                    q = stoi(word);
                }
                else if(word == "e"){
                    inFile >> word;
                    e = stoi(word);
                }
                else if(word == "r"){
                    inFile >> word;
                    encryptedMessage = stoi(word);
                }
            }

            n = p*q;
            phiN = (p-1)*(q-1);
            d = calculate_d(p, q, e);

            long plaintextNumber = powm(encryptedMessage, d, n);

            outFile << "studentName " << studentName << endl;
            outFile << "p " << p << endl;
            outFile << "q " << q << endl;
            outFile << "e " << e << endl;
            outFile << "d " << d << endl;
            outFile << "n " << n << endl;
            outFile << "r " << encryptedMessage << endl;
            outFile << "plainNumber=" << char(plaintextNumber) << endl;
            outFile << "s " << plaintextNumber << " OK" << endl;
        }
        catch(exception e){
            cout << e.what();
        }
    }

}

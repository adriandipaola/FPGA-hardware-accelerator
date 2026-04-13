#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

/*

Generator for LUT that counts consecutive 1s in a number. 

*/


const int N = 6; //num bits in vector
const int NV = (int) pow(2, N); 
const int m = 3; //num bits in result

//consecutive ones in b
int conOne(int b) {
    int n_one = 0;
    int max_co = 0;

    for (int i = 0; i <= N; i++) {
        if (b & 0x1) {
            n_one++;
        } else {
            //0 reached in LSB; set the max consecutive 1s if a greater one is reached
            //and reset current consecutive 1s count
            if (n_one > max_co) {
                max_co = n_one;
            }
            n_one = 0;
        }
        b = b >> 1;
    }
    return max_co;
}

std::vector<int> e_hex(std::vector<int> b, int mask) {
    std::vector<int> vect(NV/4); 
    //form hex value for 4 selected bits
    for (int i = NV - 1; i >= 0; i--) {
        if ((b[i] & mask) != 0) {
            vect[i / 4] += (int) pow(2, i % 4);
        }
    }
    return vect;
}

int main() {
    std::vector<int> vect(NV);
    for (int i = 0; i < NV; i++) {
        vect[i] = conOne(i);
    }

    //opening file
    std::ofstream outFile("../hls_outputs/con_ones.txt");
    if (!outFile.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    //generating m constants and saving them in the file
    std::vector<int> CO_vect;
    for (int i = 0; i < m; i++) {
        outFile << "localparam logic [" << std::dec << NV - 1 << ":0] bit" << i << " = " << NV << "'h";
        CO_vect = e_hex(vect, (int) pow(2, i));
        for (int i = NV / 4 - 1; i >= 0; i--) {
            outFile << std::hex << CO_vect[i];
        }
        outFile << ";\n";

    }

    return 0;
}
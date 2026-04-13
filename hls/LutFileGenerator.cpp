#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>



const int N = 6; //num bits in the vector
const int NV = (int) std::pow(2, N); // num different N-bit binary numbers'
const int ny = 3; //num bits in the calculated Hamming weight


int HW_b(int b) {
    int HW = 0;
    for (int i = 0; i < N; i++) {
        HW += (1 & b); //increment if ones digit is 1
        b = b >> 1; //right shift 1
    }
    return HW;
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
    int b; 
    std::vector<int> vect; //vector of constants for LUTs
    std::vector<int> HW_vect(NV);
    for (b = 0; b < NV; b++) {
        HW_vect[b] = HW_b(b);
    }
    //opening file
    std::ofstream outFile("../hls_outputs/constants.txt");
    if (!outFile.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    //generating ny constants and saving them in the file
    for (int i = 0; i < ny; i++) {
        outFile << "localparam logic [" << std::dec << NV - 1 << ":0] bit" << i << " = " << NV << "'h";
        vect = e_hex(HW_vect, (int) pow(2, i));
        for (int i = NV / 4 - 1; i >= 0; i--) {
            outFile << std::hex << vect[i];
        }
        outFile << ";\n";

    }
    outFile.close();
    
    return 0;
}
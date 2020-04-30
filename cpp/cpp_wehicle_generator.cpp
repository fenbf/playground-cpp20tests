/*
sample code, just to start, it's run with the following commands:

g++ -std=c++1z -O2 -Wall $1 -lstdc++fs
./a.out $2 $3 $4 $5
*/


#include <string> 
#include <cstring> 
#include <iostream>
#include <vector>  
#include <fstream>
#include <random>
#include <algorithm>


char partsFileName[128] = "wehicle_parts.txt";

std::vector<std::string> allParts;

class SpaceShip {
public:
    static void GenerateShip(SpaceShip *pOutShip);

    void Print() {
        std::cout << "A ship with ";
        std::cout << _engine << ", ";
        std::cout << _fuselage << ", ";
        std::cout << _cabin << ", ";
        if (!_large_wings.empty())
            std::cout << _large_wings << ", ";
        if (!_small_wings.empty())
            std::cout << _small_wings << ", ";
        std::cout << _armor << ", ";
        std::cout << "weapons: ";
        for (int i = 0; i < 4; ++i)
            if (!_weapons[i].empty())
                std::cout << _weapons[i] << ", ";
    }
private:
    std::string _engine;
    std::string _fuselage;
    std::string _cabin;
    std::string _large_wings; // optional
    std::string _small_wings;  // optional
    std::string _armor;
    std::string _weapons[4]; // max weapon count is 4
};

void SpaceShip::GenerateShip(SpaceShip *pOutShip) {
    std::vector<std::string> engineParts;
    std::vector<std::string> fuselageParts;
    std::vector<std::string> cabinParts;
    std::vector<std::string> wingsParts;
    std::vector<std::string> armorParts;
    std::vector<std::string> weaponParts;
    
    for (const auto& str : allParts) {
        std::cout << str << '\n';
        
        if (str.rfind("engine") != std::string::npos)
            engineParts.push_back(str);
        else if (str.rfind("fuselage") != std::string::npos)
            fuselageParts.push_back(str);
        else if (str.rfind("cabin") != std::string::npos)
            cabinParts.push_back(str);
        else if (str.rfind("wings") != std::string::npos)
            wingsParts.push_back(str);
        else if (str.rfind("armor") != std::string::npos)
            armorParts.push_back(str);
        else if (str.rfind("weapon") != std::string::npos)
            weaponParts.push_back(str);
    }
    
    std::cout << "engines: " << engineParts.size() << '\n';
    std::cout << "fuselages: " << fuselageParts.size() << '\n';
    std::cout << "cabinParts: " << cabinParts.size() << '\n';
    std::cout << "wingsParts: " << wingsParts.size() << '\n';
    std::cout << "armorParts: " << armorParts.size() << '\n';
    std::cout << "weaponParts: " << weaponParts.size() << '\n';
    
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(engineParts.begin(), engineParts.end(), g);
    std::shuffle(fuselageParts.begin(), fuselageParts.end(), g);
    std::shuffle(cabinParts.begin(), cabinParts.end(), g);
    std::shuffle(wingsParts.begin(), wingsParts.end(), g);
    std::shuffle(armorParts.begin(), armorParts.end(), g);
    std::shuffle(weaponParts.begin(), weaponParts.end(), g);
    
    // select parts:
    pOutShip->_engine = engineParts[0];
    pOutShip->_fuselage = fuselageParts[0];
    pOutShip->_cabin = cabinParts[0];
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
        strcpy(partsFileName, argv[1]);
    }    
    
    std::cout << "parts loaded from: " << partsFileName << '\n';
    
    std::ifstream file(partsFileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            allParts.push_back(line);
        }
        file.close();
    }     
    
    SpaceShip sp;
    SpaceShip::GenerateShip(&sp);
    sp.Print();
}
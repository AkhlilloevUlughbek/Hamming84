#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include "hamming.h"

// Function to split a binary string into 4-bit blocks
std::vector<uint8_t> MakeVector(const std::string& binary) {
    std::string input = binary;
    std::cout << "Binary representation: " << input << std::endl;

    std::vector<uint8_t> bytes;

    while (input.size() % 4 != 0) {
        input = "0" + input; // Padding with zeros to make length a multiple of 4
    }

    std::cout << "Split into blocks of 4 bits:" << std::endl;
    for (size_t i = 0; i < input.size(); i += 4) {
        std::string block = input.substr(i, 4);
        uint8_t value = static_cast<uint8_t>(std::stoi(block, nullptr, 2));
        std::cout << (i / 4 + 1) << ". " << std::bitset<4>(value) << std::endl;
        bytes.push_back(value);
    }

    return bytes;
}

// Function to display available commands
void ShowCommands() {
    std::cout << "Available commands:" << std::endl;
    std::cout << " 1. Create vector." << std::endl;
    std::cout << " 2. Encode vector." << std::endl;
    std::cout << " 3. Decode vector." << std::endl;
    std::cout << " 4. Make an error in encoded vector." << std::endl;
    std::cout << " 5. Enter new binary number." << std::endl;
    std::cout << " 6. Exit program." << std::endl;
}

int main() {
    std::string binary;
    std::cout << "Enter a binary number (arbitrary length): ";
    std::cin >> binary;

    std::vector<uint8_t> bytes, encodedBytes, decodedBytes;
    bool vectorCreated = false, encoded = false;

    ShowCommands();

    while (true) {
        int command;
        std::cout << "Choose a command: ";
        std::cin >> command;

        switch (command) {
        case 1:
            bytes = MakeVector(binary);
            vectorCreated = true;
            break;
        case 2:
            if (vectorCreated) {
                encodedBytes = Hamming_8_4::Encode(bytes);
                std::cout << "Encoded vector:" << std::endl;
                for (size_t i = 0; i < encodedBytes.size(); ++i) {
                    std::cout << (i + 1) << ". " << std::bitset<8>(encodedBytes[i]) << std::endl;
                }
                encoded = true;
            } else {
                std::cout << "Error: Create a vector first." << std::endl;
            }
            break;
        case 3:
            if (encoded) {
                decodedBytes = Hamming_8_4::Decode(encodedBytes);
                if (!decodedBytes.empty()) {
                    std::cout << "Decoded binary result:" << std::endl;
                    for (uint8_t byte : decodedBytes) {
                        std::cout << std::bitset<4>(byte);
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "Data cannot be corrected." << std::endl;
                }
            } else {
                std::cout << "Error: Encode the vector first." << std::endl;
            }
            break;
        case 4:
            if (encoded) {
                int itemIndex, bitPosition;
                std::cout << "Enter the vector index (1 to " << encodedBytes.size() << "): ";
                std::cin >> itemIndex;
                std::cout << "Enter the bit position (1 to 8): ";
                std::cin >> bitPosition;

                if (itemIndex >= 1 && itemIndex <= encodedBytes.size() && bitPosition >= 1 && bitPosition <= 8) {
                    encodedBytes[itemIndex - 1] ^= (1 << (bitPosition - 1));
                    std::cout << "Bit inverted successfully. Updated vector:" << std::endl;
                    for (size_t i = 0; i < encodedBytes.size(); ++i) {
                        std::cout << (i + 1) << ". " << std::bitset<8>(encodedBytes[i]) << std::endl;
                    }
                } else {
                    std::cout << "Error: Invalid index or bit position." << std::endl;
                }
            } else {
                std::cout << "Error: Encode the vector first." << std::endl;
            }
            break;
        case 5:
            std::cout << "Enter a new binary number: ";
            std::cin >> binary;
            vectorCreated = encoded = false;
            break;
        case 6:
            std::cout << "Exiting program..." << std::endl;
            return 0;
        default:
            std::cout << "Error: Invalid command." << std::endl;
        }

        std::cout << std::endl;
        ShowCommands();
    }
}

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

#include "lib/nlohmann/json.hpp"

using json = nlohmann::json;

json decode_bencoded_value(const std::string& encoded_value) {
    if (std::isdigit(encoded_value[0])) {
        // Example: "5:hello" -> "hello"
        size_t colon_index = encoded_value.find(':');
        if (colon_index != std::string::npos) {
            std::string number_string = encoded_value.substr(0, colon_index);
            int64_t number = std::atoll(number_string.c_str());
            std::string str = encoded_value.substr(colon_index + 1, number);
            return json(str);
        } else {
            throw std::runtime_error("Invalid encoded value: " + encoded_value);
        }
    }
    else if(encoded_value[0]=='i' && encoded_value[encoded_value.length()-1]=='e')
    {
        //minimum size will be 3 for the integer bencoded value
        size_t encoded_value_size=encoded_value.size();
        if(encoded_value_size>=3)
        {
            std::string extracted_value=encoded_value.substr(1,encoded_value_size-2);
            //now that we have extracted the value from the string we will check if the extracted value is consistent
            for(int i=0;i<extracted_value.size();i++)
            {
                if(!std::isdigit(extracted_value[i]) && !(extracted_value[i]=='-'))
                {
                    throw std::runtime_error("Invalid Integer Value in encoded string: "+encoded_value);
                }
            }
            int64_t integer_value=std::atoll(extracted_value.c_str());
            return(json(integer_value));

        }
        else{
            throw std::runtime_error("Invalid encoded value: " + encoded_value);

        
        }

    }
    else{
        throw std::runtime_error("Type not handeled yet");
    }
}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " decode <encoded_value>" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "decode") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " decode <encoded_value>" << std::endl;
            return 1;
        }
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        std::cerr << "Logs from your program will appear here!" << std::endl;

        // Uncomment this block to pass the first stage
         std::string encoded_value = argv[2];
         json decoded_value = decode_bencoded_value(encoded_value);
        std::cout << decoded_value.dump() << std::endl;
    } else {
        std::cerr << "unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}

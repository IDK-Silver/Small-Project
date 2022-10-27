//
// Created by idk on 2022/10/27.
//
#include <iostream>
#include <iomanip>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <string>

std::string SHA256HashString(const std::string& input_string)
{
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[ CryptoPP::SHA256::DIGESTSIZE ];
    hash.CalculateDigest( digest, (CryptoPP::byte*) input_string.c_str(), input_string.length() );
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach( new CryptoPP::StringSink( output ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();
    return output;
}

/* the function to print the line
 * like blank_line(10) -> "----------"
 */
void blank_line(unsigned int width)
{
    std::string line(width, '-');
    std::cout << line << std::endl;
}

int main()
{
    std::string input_name;                 /* storage the username      */
    unsigned int range = 0;                 /* storage the try max value */
    unsigned int need_num = 0;              /* storage need 0 num        */
    unsigned int max_string_size;           /* the sha string length     */


    /* get the input name   */
    std::cout << std::setw(15) << std::setiosflags(std::ios::left) << "input name" << ": ";
    std::cin >> input_name;

    /* get the range        */
    std::cout << std::setw(15) << std::setiosflags(std::ios::left) << "try range" << ": ";
    std::cin >> range;

    /* get the need num     */
    std::cout <<std::setw(15) << std::setiosflags(std::ios::left) << "need 0 num" << ": ";
    std::cin >> need_num;

    /* cal the max string size */
    max_string_size = int(std::string(input_name + std::to_string(range)).size()) + 1;

    /* display message  */
    blank_line(max_string_size + 64 + 3);
    std::cout << "|" << std::setw(max_string_size) << std::string("Name") << "|" << std::setw(64) << "SHA256" << "|" << "\n";
    blank_line(max_string_size + 64 + 3);


    /* find the ans (the sha zero num == need)
     * the range is the user input (range)
     */
    for (int index = 0; index < range; index++)
    {
        std::string add_string;                 /* storage the add num string */

        /* add num to input_name      */
        add_string = input_name;
        add_string += std::to_string(index);

        /* run sha */
        std::string sha_string = SHA256HashString(add_string);

        int timer = 0;                          /* record 0 time */
        for (auto iter : sha_string)
        {
            if (timer == need_num)
            {
                std::cout << "|" << std::setw(max_string_size) << std::setiosflags(std::ios::left) << add_string << "|" << sha_string << "|" << std::endl;
                blank_line(max_string_size + 64 + 3);
            }

            if (iter == '0')
            {
                timer++;
                continue;
            }
            break;
        }

    }

    std::cout << "Press any key to continue.";
    std::cin.ignore();
    std::cin.get();
    return 0;
}

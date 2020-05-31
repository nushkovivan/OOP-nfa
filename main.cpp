/**
 * @file main.cpp
 * @details Contains the functionality that give the user the chance to work with NFAs.
 */

#include <iostream>
#include<cstdio>
#include<sstream>
#include<fstream>
#include"NFA.h"

/**
 * @details Gives the users the chance to operate with NFAs. Some of the operations supported are: union/concatenation
 * of two NFAs, positive shell of a NFA, check whether NFA is deterministic / it's language is empty, or if a NFA recognizes
 * a given word. It can also read and write NFAs to/from files.
 * @return - 0 - a success status.
 */
int main() {

    std::cout<<"                          Basic file options:                                "<<std::endl;
    std::cout<<"               open | close | save | saveAs | help | exit                    "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"                         NFA options supported:                               "<<std::endl;
    std::cout<<"list | print | save | empty | deterministic | recognize | union | concat | un "<<std::endl;
    std::cout<<std::endl;

    std::string input, inputWord;
    //reads user input
    while(getline(std::cin, input)) {
        //stores the input line in stream
        std::stringstream inputStream(input);
        //reads word from the stream and stores it in the inputWord
        inputStream >> inputWord;

        //if the first word of the user input is "open"
        if(inputWord == "open") {
            //reads another element from the input
            inputStream >> inputWord;
            //opens the file from the user input
            std::fstream file(inputWord, std::ios::in | std::ios::out | std::ios::app);
            if (!file) {
                std::cout << "Couldn't open file!" << std::endl;
                exit(1);
            }

            //opens one temporary file
            std::fstream fileTemp("temp.txt", std::ios::in | std::ios::out | std::ios::trunc);
            if (!fileTemp) {
                std::cout << "Couldn't open file!" << std::endl;
                exit(1);
            }

            //gets every line from the file opened by the user and writes it in temporary file and prints it
            std::string fileLine;
            while (getline(file, fileLine)) {
                fileTemp << fileLine << std::endl;
                std::cout<<fileLine<<std::endl;
            }

            std::cout<<std::endl;
            std::string specialInput, specialWord;
            //while file is opened user can make some operations on it by entering commands
            while(getline(std::cin, specialInput)){
                //stores the input in another stream and reads the first word of it
                std::stringstream specialStream(specialInput);
                specialStream>>specialWord;

                //if the user input is "list" - gets every temporary file line and if it starts with "<" prints it
                //it's used to print all the identifiers of the NFA from file
                if(specialWord ==  "list"){
                    fileTemp.clear();
                    //sets the get  pointer at the beginning of the file
                    fileTemp.seekg(0, std::ios::beg);

                    std::string line;
                    while(getline(fileTemp, line)){
                        if(line[0] == '<')
                            std::cout<<line<<std::endl;
                    }
                    std::cout<<std::endl;
                }

                //if the user input is "save" - saves the changes to the file that user inputed by reading the temporary
                //file line by line and writing it in the inputed file
                if(specialWord == "save"){
                    file.close();
                    fileTemp.clear();
                    fileTemp.seekp(0, std::ios::beg);

                    std::fstream fileN(inputWord, std::ios::out | std::ios::trunc);
                    if(!fileN){
                        std::cout<<"Couldn't open file!"<<std::endl;
                        exit(1);
                    }

                    std::string line;
                    while(getline(fileTemp, line)){
                        fileN<<line<<std::endl;
                    }

                    std::remove("temp.txt");
                    file.close();

                    std::cout<<"File saved!"<<std::endl;
                    std::cout<<std::endl;
                    break;
                }

                //if the user input is "saveAs" - saves the changes to a new file which name the user inputs
                if(specialWord == "saveAs"){
                    fileTemp.clear();
                    fileTemp.seekg(0, std::ios::beg);
                    specialStream>>specialWord;
                    std::ofstream newFile(specialWord, std::ios::out);
                    if(!newFile){
                        std::cout<<"Couldn't open file!"<<std::endl;
                        exit(1);
                    }

                    std::string line;
                    while(getline(fileTemp, line)){
                        newFile<<line<<std::endl;
                    }

                    remove("temp.txt");
                    file.close();
                    newFile.close();

                    std::cout<<"File saved!"<<std::endl;
                    std::cout<<std::endl;
                    break;
                }

                //if the user input is "close" - closes the file
                if(specialWord == "close"){
                    file.close();
                    fileTemp.close();
                    std::cout<<"File "<<inputWord<<" closed!"<<std::endl;
                    std::cout<<std::endl;
                    break;
                }

                //if the user input is "addNFA' - gives the user the chance to input a new NFA and writes it in the temporary file
                if(specialWord == "addNFA"){
                    NFA nfa;
                    nfa.input();
                    nfa.writeToFile("temp.txt");
                    std::cin.ignore();
                    std::cout<<"NFA successfully added!"<<std::endl;
                    std::cout<<std::endl;
                }

                //if the user input is "print" - prints the NFA (which identifier user also entered) to the screen
                if(specialWord == "print"){
                    int found;
                    specialStream>>found;
                    NFA nfa;
                    nfa.setID(found);
                    nfa.readFromFile(found);
                    nfa.print();
                }

                //if the user input is "union" - gets the two identifiers that the user inputed, finds the NFAs with this
                //identifiers in the file and makes their union, then prints the result
                if(specialWord == "union"){
                    int id1, id2;
                    specialStream>>id1;
                    specialStream>>id2;

                    NFA one, two, three;
                    one.readFromFile(id1);
                    two.readFromFile(id2);

                    three.Union(one, two);
                    three.print();
                }

                //if the user input is "concatenation" - gets the two identifiers that the user inputed finds the NFAs with this
                //identifiers in the file and makes their concatenation, then prints the result
                if(specialWord == "concatenation"){
                    int id1, id2;
                    specialStream>>id1;
                    specialStream>>id2;

                    NFA one, two, three;
                    one.readFromFile(id1);
                    two.readFromFile(id2);

                    three.Concat(one, two);
                    three.print();
                }

                //if the user input is "positive" - gets the identifier that the user inputed, finds the NFA with this
                //identifier in the file and makes its positive shell, then prints the result
                if(specialWord == "positive"){
                    int id1;
                    specialStream>>id1;

                    NFA one, two;
                    one.readFromFile(id1);
                    two.Positive(one);
                    two.print();
                }

                //if the user input is "deterministic" - gets the identifier that the user inputed, finds the NFA with this
                //identifier in the file and checks if it's deterministic, then prints the result
                if(specialWord == "deterministic"){
                    int id1;
                    specialStream>>id1;

                    NFA one;
                    one.readFromFile(id1);
                    if(one.isDeterministic())
                        std::cout<<"Yes"<<std::endl;
                    else
                        std::cout<<"No"<<std::endl;
                }

                //if the user input is "empty" - gets the identifier that the user inputed, finds the NFA with this
                //identifier in the file and checks if its language is empty, then prints the result
                if(specialWord == "empty"){
                    int id1;
                    specialStream>>id1;

                    NFA one;
                    one.readFromFile(id1);
                    if(one.isEmptyLanguage())
                        std::cout<<"Yes"<<std::endl;
                    else
                        std::cout<<"No"<<std::endl;
                }

                //if the user input is "recognize" - gets the identifier that the user inputed, finds the NFA with this
                //identifier in the file and checks if it recognizes the word from the user input, then prints the result

                if(specialWord ==  "recognize"){
                    int id;
                    specialStream>>id;

                    NFA one;
                    one.readFromFile(id);

                    char word[10];
                    specialStream>>word;

                    if(one.recognise(word))
                        std::cout<<"Yes"<<std::endl;
                    else
                        std::cout<<"No"<<std::endl;
                }
            }
        }

        //if the user input is "help" - prints help table
        else if(inputWord == "help"){
            std::cout<<"            The following commands are supported: "<<std::endl;
            std::cout<<" //////////////////////////////////////////////////////////////////////// "<<std::endl;
            std::cout<<"|| open <file>            ||    opens <file>                            ||"<<std::endl;
            std::cout<<"|| close                  ||    closes currently opened file            ||"<<std::endl;
            std::cout<<"|| save                   ||    saves the currently open file           ||"<<std::endl;
            std::cout<<"|| saveAs <file>          ||    saves the currently open file in <file> ||"<<std::endl;
            std::cout<<"|| help                   ||    prints this information                 ||"<<std::endl;
            std::cout<<"|| exit                   ||    exits the program                       ||"<<std::endl;
            std::cout<<"|| list                   ||    shows all NFA id from file              ||"<<std::endl;
            std::cout<<"|| addNFA                 ||    input NFA and add it to open file       ||"<<std::endl;
            std::cout<<"|| print <id>             ||    prints all NFA transitions              ||"<<std::endl;
            std::cout<<"|| empty <id>             ||    checks if NFA language is empty         ||"<<std::endl;
            std::cout<<"|| deterministic <id>     ||    checks if NFA is deterministic          ||"<<std::endl;
            std::cout<<"|| recognize <id> <word>  ||    checks if NFA recognizes word           ||"<<std::endl;
            std::cout<<"|| union <id1> <id2>      ||    union of two NFA                        ||"<<std::endl;
            std::cout<<"|| concat <id1> <id2>     ||    concatenate two NFA                     ||"<<std::endl;
            std::cout<<"|| positive <id>          ||    positive shell of NFA                   ||"<<std::endl;
            std::cout<<" //////////////////////////////////////////////////////////////////////// "<<std::endl;
            std::cout<<std::endl;
        }

        //if the user input is "exit" - exits the program
        else if(inputWord == "exit"){
            std::cout<<"Are you sure you want to exit system? (y/n)"<<std::endl;
            char choice;
            std::cin>>choice;
            if(choice == 'y'){
                std::cout<<"Successfully exited the system!"<<std::endl;
                exit(0);
            }

            std::cin.ignore();
        }

        std::cout<<std::endl;
    }

    return 0;
}

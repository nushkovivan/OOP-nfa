/**
 * @file NFA.cpp
 * @details Contains half of the NFA's functions definitions.
 */

#include<iostream>
#include<cstring>
#include<cassert>
#include<fstream>
#include <sstream>
#include"NFA.h"

int NFA:: autoCounter = 1;

 /**
  * @brief Creates copy of an existing object.
  *
  * @param other - reference to an object of type NFA;
  */
void NFA::Copy(const NFA& other){
    ID = autoCounter++;

    // sets current states number and maximum states number as those of other
    currentStatesNum = other.currentStatesNum;
    maxStatesNum = other.maxStatesNum;

     // sets current transitions number and maximum transitions number as those of other
    currentTransitionsNum = other.currentTransitionsNum;
    maxTransitionsNum = other.maxTransitionsNum;

    //the initial state is the other initial state
    initialState = other.initialState;

    //creates new states array and puts in it the elements of the other states array
    states = new State[maxStatesNum];
    assert(states != nullptr);

    for (int i = 0; i < currentStatesNum; i++)
        states[i] = other.states[i];

     //creates new transitions array and puts in it the elements of the other transitions array
    transitions = new Transition[maxTransitionsNum];
    assert(transitions != nullptr);

    for (int i = 0; i < currentTransitionsNum; i++)
        transitions[i] = other.transitions[i];

}

/**
 * @details Deallocate memory and does other cleanup for a NFA object and its class members when the object is destroyed.
 */
void NFA::Erase(){
    delete [] states;
    delete [] transitions;
}

/**
 * @brief Constructor
 * @details Default constructor, defined in a way that it can accept user-provided values as well. It's used to initialize a newly created NFA.
 *
 * @param statesC - dynamically allocated array of type State;
 * @param maxStatesNum - maximum number of states, 10 by default;
 * @param currentStatesNum - current number of states, 0 by default;
 * @param statesC - dynamically allocated array of type Transition;
 * @param maxStatesNum - maximum number of transitions, 10 by default;
 * @param currentStatesNum - current number of transitions, 0 by default;
 * */
NFA::NFA(State* statesC, int maxStatesNum, int currentStatesNum, Transition* transitionsC, int maxTransitionsNum, int currentTransitionsNum){
    ID = autoCounter++;

    this->maxStatesNum = maxStatesNum;
    this->currentStatesNum = currentStatesNum;

    states = new State[maxStatesNum];
    assert(states != nullptr);

    for(int i = 0; i < currentStatesNum; i++)
        states[i] = statesC[i];

    this->maxTransitionsNum = maxTransitionsNum;
    this->currentTransitionsNum = currentTransitionsNum;

    transitions = new Transition[maxTransitionsNum];
    assert(transitions != nullptr);

    for(int i = 0; i < currentTransitionsNum; i++)
        transitions[i] = transitionsC[i];

}

/**
 * @brief Copy constructor
 * @details Creates copy of an existing object.
 * @param other - reference to an object of type NFA
 * @see Copy(const NFA&)
 */
NFA::NFA(const NFA& other){
    Copy(other);
}

/**
 * @brief Assignment operator.
 * @details Used to copy values from one Transition to another already existing Transition.
 *
 * @param other - reference to an object of type NFA whose values we use;
 * @return the value of the NFA specified by the left operand after the assignment.
 * @see Copy(const NFA&) Erase()
 */
NFA& NFA::operator=(const NFA& other){
    if (this != &other){
        Erase();
        Copy(other);
    }
    return *this;
}

/**
 * @brief Destructor.
 * @details Release any resources allocated by the object of type NFA.
 * @see Erase()
 */
NFA::~NFA(){
    Erase();
}

/**
 * @details Used to get the NFA's identifier.
 * @return the NFA identifier.
 */
int NFA::getID() const{
    return ID;
}

/**
 * @details Sets the identifier of the NFA.
 * @param identifier - the identifier we want to assign to the NFA;
 */
void NFA::setID(int identifier){
    ID = identifier;
}

/**
 * @details used to get the states of the NFA.
 * @return an array with the states of the NFA.
 */
State* NFA::getStates() const{
    return states;
}

/**
 * @return the current number of states of the NFA .
 */
int NFA::getCurrentStatesNum() const{
    return currentStatesNum;
}

/**
 * @return the maximum number of state of the NFA.
 */
int NFA::getMaxStatesNum() const{
    return maxStatesNum;
}

/**
 * @details used to get the transitions of the NFA.
 * @return an array with the transitions of the NFA.
 */
Transition* NFA::getTransitions() const{
    return transitions;
}

/**
 * @return the current number of transitions of the NFA.
 */
int NFA::getCurrentTransitionsNum() const{
    return currentTransitionsNum;
}

/**
 * @return the maximum number of transitions of the NFA.
 */
int NFA::getMaxTransitionsNum() const{
    return maxTransitionsNum;
}

/**
 * @details Used to get the initial state of the NFA.
 * @return the initial state of the NFA.
 */
State NFA::getInitialState() const{
    return initialState;
}

/**
 * @details makes the given argument the initial state of the NFA.
 * @param state - reference to an object of type State;
 */
void NFA::setInitialState(const State& state){
    initialState = state;
}

/**
 * @details Adds the state given as an argument to the states array of the NFA.
 *
 * @param state - reference to an object of type State;
 * @note If the current number of states is equal to the maximum number of states the program should increase the maximum
 * number of states first.
 */
void NFA::addState(const State& state){
    //checks if the maximum number of states is reached
    if (currentStatesNum == maxStatesNum){
        //increases the maximum number of states
        ++maxStatesNum;
        //dynamically allocates new array of states and stores the NFA states in it, then deallocates the memory used for
        //our states array and appropriates the buffer to states
        State* buffer = new State[maxStatesNum];
        for (int i = 0; i<currentStatesNum; i++){
            buffer[i] = states[i];
        }
        delete[] states;
        states = buffer;
    }
    //adds the new state at the end of the array
    states[currentStatesNum++] = state;
}

/**
 * @details Adds the transition given as argument to the transitions array of the NFA.
 *
 * @param transition - reference to an object of type Transition;
 * @note If the current number of transitions is equal to the maximum number of transitions the program should increases the maximum
 * number of transitions first.
*/
void NFA::addTransition(const Transition& transition){
    //checks if the maximum number of transitions is reached
    if (currentTransitionsNum == maxTransitionsNum) {
        //increases the maximum number of transitions
        ++maxTransitionsNum;
        //dynamically allocates new array of transitions and stores the NFA transitions in it, then deallocates the memory
        // used for our transitions array and appropriates the buffer to transitions
        Transition* buffer = new Transition[maxTransitionsNum];
        for (int i = 0; i < currentTransitionsNum; i++) {
            buffer[i] = transitions[i];
        }

        delete[] transitions;
        transitions = buffer;
    }
    //adds the new transition at the end of the array
    transitions[currentTransitionsNum++] = transition;
}

/**
 * @details Makes a given State final.
 * @param state - reference to an object of type State;
 */
void NFA::setFinalState(const State& state){
    for(int i = 0; i < currentStatesNum; i++) {
        if (states[i].name == state.name)
            states[i].isFinal = true;
    }
}

/**
 * @brief Prints the alphabet of the NFA.
 */
void NFA::getAlphabet() const{
    int size = getCurrentTransitionsNum();
    //dynamically allocates array of chars to store the alphabet
    char* alphabet = new char[size];
    int numOfA = 0;
    bool isThere = false;

    //the first element of the array is the first transition's literal
    alphabet[numOfA] = transitions[0].literal;

    //check if the literal has already been reached so that it can miss it
    for(int i = 1; i < currentTransitionsNum; i++){
        for(int j = 0; j <= strlen(alphabet); j++){
            if(transitions[i].literal == alphabet[j])
                isThere = true;
        }
        //if the literal hasn't been reached before the program adds it in the alphabet array
        if(!isThere)
            alphabet[++numOfA] = transitions[i].literal;
    }

    //prints the alphabet
    for(int i = 0; i <= numOfA; i++)
        std::cout<<alphabet[i]<<" ";

    //deallocates the memory used for the alphabet array
    delete [] alphabet;
}

/**
 * @details Let's the user to input NFA.
 * @note When a State is entered, its name is entered first and then whether it's final(0/1).
 */
void NFA::input(){
    //enters the nuber of states
    std::cout<<"Please, enter the number of states:";
    int numStates;
    std::cin>>numStates;

    //enters the states(name, isFinal), and adds the state to the states array of the NFA
    std::cout<<"States:"<<std::endl;
    for(int i = 0; i < numStates; i++){
        State state;
        std::cout<<"State name:";
        std::cin>>state.name;
        std::cout<<"Is final:";
        std::cin>>state.isFinal;
        addState(state);
    }

    std::cout<<std::endl;

    //enter the number of transitions
    std::cout<<"Please, enter the number of transitions:";
    int numTransitions;
    std::cin>>numTransitions;

    //enters the transitions(from, to, literal), and adds the transition to the transitions array of the NFA
    std::cout<<"Transitions (from / to / literal):"<<std::endl;
    for(int i =0;i<numTransitions;i++){
        Transition trans;
        std::cin >> trans.from;
        std::cin >> trans.to;
        std::cin >> trans.literal;

        addTransition(trans);
    }

    //enters the initial state of the NFA
    std::cout<<std::endl;
    std::cout<<"Please, enter the initial state: ";
    int tmpInitial;
    std::cin>> tmpInitial;
    setInitialState(tmpInitial);

    std::cout<<std::endl;
}

/**
 * @brief Prints the NFA to the console.
 */
void NFA::print() const {
    //prints the identifier of the NFA
    std::cout<<"< "<<ID<<" >"<<std::endl;

    //prints the states of the NFA
    std::cout <<"Q = { ";
    for (int i = 0; i < currentStatesNum; i++)
        std::cout << states[i].name << " ";
    std::cout << "}"<<std::endl;

    //prints the alphabet of the NFA
    std::cout<<"Σ = { ";
    getAlphabet();
    std::cout << "}"<<std::endl;

    //prints the initial state of the NFA
    std::cout<<"s = { " << initialState.name << " }"<<std::endl;

    //prints the final states of the NFA
    std::cout<<"F = { ";
    for (int i = 0; i < currentStatesNum; i++){
        if (states[i].isFinal)
            std::cout << states[i].name << " ";
    }
    std::cout<<"} "<<std::endl;

    //prints the transitions of the NFA in format (from, literal, to)
    std::cout<<"δ : ";
    for(int i = 0; i< currentTransitionsNum; i++)
        std::cout<<"δ("<<transitions[i].from<<","<<transitions[i].literal<<","<<transitions[i].to<<")  ";

    autoCounter--;
    std::cout<<std::endl;
    std::cout<<std::endl;
}

/**
 * @brief Adds NFA to file.
 * @param name - the name of the file in which we wil add the NFA;
 */
void NFA::writeToFile(char* name){
    //opens file "name" for writing in it
    std::ofstream file(name, std::ios::out|std::ios::app|std::ios::ate);
    if(!file){
        std::cout<<"File couldn't open!"<<std::endl;
        exit(1);
    }

    file<<std::endl;

    //writes the identifier of the NFA in the file
    file<<"< "<<ID<<" >"<<std::endl;

    //writes NFA's states in the file
    file<< "Q = { ";
    for (int i = 0; i < currentStatesNum; i++)
        file<< states[i].name << " ";
    file<< "}"<<std::endl;

    //writes NFA's alphabet in the file
    file<<"Σ = { ";
    int size = currentTransitionsNum;
    //dynamically allocating array of chars to store the alphabet
    char* alphabet = new char[size];
    int numOfA = 0;
    bool isThere = false;

    //the first element of the array is the first transition's literal
    alphabet[numOfA] = transitions[0].literal;

    //check if the literal has already been reached so that it can miss it
    for(int i = 1; i < currentTransitionsNum; i++){
        for(int j = 0; j <= strlen(alphabet); j++){
            if(transitions[i].literal == alphabet[j])
                isThere = true;
        }
        //if the literal hasn't been reached before the program adds it in the alphabet array
        if(!isThere)
            alphabet[++numOfA] = transitions[i].literal;
    }

    for(int i = 0; i <= numOfA; i++)
        file<<" "<<alphabet[i]<<" ";

    delete [] alphabet;
    file<< "}"<<std::endl;

    //writes NFA's initial state in the file
    file<<"s = { " << initialState.name << " }"<<std::endl;

    //writes NFA's final states in file
    file<<"F = { ";
    for (int i = 0; i < currentStatesNum; i++){
        if (states[i].isFinal)
            file<< states[i].name << " ";
    }
    file<<"}"<<std::endl;

    //writes NFA's transitions in the file - format(from, literal, to)
    file<<"δ : ";
    for(int i = 0; i< currentTransitionsNum; i++)
        file<<"δ( "<<transitions[i].from<<" , "<<transitions[i].literal<<" , "<<transitions[i].to<<" )  ";

    file<<std::endl;
    file<<std::endl;
}

/**
 * @details Used to search NFA through file.
 * @param id - identifier of the NFA we are searching;
 */
void NFA::readFromFile(int id){
    //opens file "tmp.txt" for reading
    std::ifstream file("temp.txt", std::ios::in);
    if(!file){
        std::cout<<"Couldn't open file!"<<std::endl;
        exit(1);
    }

    std::string line;
    //reading file line by line
    while(getline(file, line)) {
        //checks if the first sign of the line is '<' so it means it is an identifier
        if (line[0] == '<') {
            //stores the line in stream and reads it element by element
            std::stringstream streamFile(line);
            int found;
            std::string wordHelp;
            streamFile >> wordHelp >> found;

            //if it is the identifier we are searching
            if (found == id) {
                //reads another line from the file and stores it in another stream to read it element by element
                getline(file, line);
                std::stringstream stream(line);
                std::string element;
                int found;

                //gets all the states names from the line and adds them to the states array
                while (!stream.eof()) {
                    stream >> element;
                    if (std::stringstream(element) >> found) {
                        State state;
                        state.name = found;
                        addState(state);
                    }
                }

                //reads two new lines (to reach the initial state line) and puts it in stream
                getline(file, line);
                getline(file, line);
                std::stringstream stream1(line);
                //reads the stream element by element to reach the initial state name
                while (!stream1.eof()) {
                    stream1 >> element;
                    if (std::stringstream(element) >> found) {
                        State state;
                        state.name = found;
                        initialState = state;
                    }
                }

                //reads the line with the final states and stores it in stream to get it element by element
                getline(file, line);
                std::stringstream stream2(line);
                //while reading from the stream if the data is a state name makes it a final state
                while (!stream2.eof()) {
                    stream2 >> element;
                    if (std::stringstream(element) >> found) {
                        State state;
                        state.name = found;
                        setFinalState(state);
                    }
                }

                //gets the line with the transitions and stores it in stream
                getline(file, line);
                Transition transition;
                std::stringstream stream3(line);
                //while reading from the stream gets the transitions and adds them to the transitions array of the NFA
                while (!stream3.eof()) {
                    stream3 >> element;
                    if (std::stringstream(element) >> found) {
                        transition.from = found;

                        stream3 >> element;
                        stream3 >> element;
                        transition.literal = element[0];

                        stream3 >> element;
                        stream3 >> element;
                        if (std::stringstream(element) >> found) {
                            transition.to = found;
                            addTransition(transition);
                        }
                        stream3 >> element;
                    }
                }
            }
        }
    }
}

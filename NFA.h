/**
 * \headerfile NFA.h
 * @details Contains all the NFA's functions declarations.
 */

#ifndef NFA_NFA_H
#define NFA_NFA_H

/**
 * @struct State
 * @brief Used to present NFA states.
 * @details Every NFA state has name(integer) and can be final/not final.
*/
struct State{
    int name;/**< - the name of the state;*/
    bool isFinal;/**< - shows if the state is final;*/

    /**
     * @brief Default constructor
     * @details Defined in a way that it can accept user-provided values as well. It's used to initialize a newly
     * created State.
     *
     * @param name - the name of the state, 0 by default;
     * @param isFinal - indicates if the state is final, false by default;
     */
    State(int name = 0, bool isFinal = false){
        this->name = name;
        this->isFinal = isFinal;
    }

    /**
     * @brief Assignment operator
     * @details Used to copy values from one State to another already existing State.
     *
     * @param other - reference to an object of type State whose values we use;
     * @return the value of the State specified by the left operand after the assignment.
     */
    State& operator=(const State& other){
        if(this != &other){
            this->name = other.name;
            this->isFinal = other.isFinal;
        }
        return *this;
    }
};

/**
 * @struct Transition
 * @brief Used to present NFA transitions.
 * @details Every NFA transition has two states and literal to make the transition from one State to another.
 */
struct Transition{
    int from;/**< - the from-state name;*/
    int to;/**< - the to-state name;*/
    char literal;/**< - the literal that we use to pass;*/

    /**
     * @brief Default constructor
     * @details Defined in a way that it can accept user-provided values as well. It's used to initialize a newly
     * created Transition.
     *
     * @param from - the name of the from-state, 0 by default;
     * @param to - the name of the to-state, 0 by default;
     * @param literal - the name of the literal that we use to make a transition, ^ by default;
     */
    Transition(int from = 0, int to = 0, char literal = '^'){
        this->from = from;
        this->to = to;
        this->literal = literal;
    }

    /**
     * @brief Assignment operator.
     * @details Used to copy values from one Transition to another already existing Transition.
     *
     * @param other - reference to an object of type Transition whose values we use;
     * @return the value of the Transition specified by the left operand after the assignment.
     */
    Transition& operator=(const Transition& other){
        if (this != &other) {
            from = other.from;
            to = other.to;
            literal = other.literal;
        }
        return *this;
    }
};

/**
 * @class NFA
 * @brief Non-deterministic finite automation with ε-transitions.
 * @details Class for declaring NFA. Supports basic operations with NFA such as union, concatenation, positive shell,
 * word recognition, deterministic check, reading from file and writing to file.
 */
class NFA{
private:
    static int autoCounter;/**< - used to generate ID's. Increases it's value with every new created NFA.*/
    int ID;/**< - special identifier for the NFA;*/

    State* states;/**< - dynamically allocated array of states to store the NFA states; @see State*/
    int currentStatesNum;/**< - current number of states that the NFA has;.*/
    int maxStatesNum;/**< - maximum number of states that the NFA can have;*/
    Transition* transitions;/**< - dynamically allocated array of transitions to store the NFA transitions; @see Transition*/
    int currentTransitionsNum;/**< - current number of transitions that the NFA has;*/
    int maxTransitionsNum;/**< - maximum number of transitions that the NFA can have;*/
    State initialState;/**< - the initial state of the NFA;*/

    void Copy(const NFA&);
    void Erase();

public:
    NFA(State* = nullptr, int = 10, int = 0, Transition* = nullptr, int = 10, int = 0);
    NFA(const NFA&);
    NFA& operator=(const NFA&);
    ~NFA();

    int getID() const;
    State* getStates() const;
    int getCurrentStatesNum() const;
    int getMaxStatesNum() const;
    Transition* getTransitions() const;
    int getCurrentTransitionsNum() const;
    int getMaxTransitionsNum() const;
    State getInitialState() const;

    void setInitialState(const State&);
    void addState(const State&);
    void addTransition(const Transition&);
    void setFinalState(const State&);
    void setID(int);

    void input();
    void getAlphabet() const;
    void print() const;
    void writeToFile(char* name);
    void readFromFile(int id);

    void epsilonClosureADD();
    bool isDeterministic() const;
    bool isEmptyLanguage() const;
    void Union(const NFA&, const NFA&);
    void Concat(const NFA&, const NFA&);
    void Positive(const NFA&);

    int help(int, char, Transition*) const;
    bool recognise(char*);
};

#endif

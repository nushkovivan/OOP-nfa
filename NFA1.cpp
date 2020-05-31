/**
 * \@file NFA1.cpp
 * @details Contains half of the NFA's functions definitions.
 */

#include<iostream>
#include<cstring>
#include"NFA.h"

/**
 * @brief Adds all the epsilon transitions to the NFA.
 */
void NFA::epsilonClosureADD() {
    for (int i = 0; i < currentTransitionsNum; i++) {
        if (transitions[i].literal == '^') {
            for (int j = 0; j < currentTransitionsNum; j++) {
                if (transitions[j].from == transitions[i].to) {
                    Transition newTrans(transitions[i].from, transitions[j].to, transitions[j].literal);
                    addTransition(newTrans);
                }
            }
        }
    }
}

/**
 * @brief Checks whether the NFA is deterministic.
 * @details The NFA is deterministic if there is at most one transition from a given state for each letter of the NFA alphabet.
 * @return true if the NFA is deterministic and false if otherwise.
 */
bool NFA::isDeterministic() const{
    for(int i = 0; i < currentTransitionsNum - 1; ++i){
        for(int j = i + 1; j < currentTransitionsNum; ++j){
            if(transitions[i].from == transitions[j].from){
                if(transitions[i].literal == transitions[j].literal && transitions[i].to != transitions[j].to){
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Checks if the NFA's language is empty(NFA has no transitions).
 * @return true is NFA is empty and false if not.
 */
bool NFA::isEmptyLanguage() const{
    return currentTransitionsNum == 0;
}

/**
 * @brief Union of two NFA.
 * @details makes union of two NFA
 * @param one - reference to an object of type NFA
 * @param two - reference to an object of type NFA
 */
void NFA::Union(const NFA& one, const NFA& two) {
    //sets the initial state and adds it to the states array
    State state(0, false);
    setInitialState(state);
    addState(state);

    //adds all the states, except the initial states of the two NFA to the union NFA states array
    for(int i = 0; i < one.getCurrentStatesNum(); i++){
        if(one.states[i].name != one.initialState.name)
            addState(one.states[i]);
    }

    for(int j = 0; j < two.getCurrentStatesNum(); j++){
        if(two.states[j].name != two.initialState.name)
            addState(two.states[j]);
    }

    //adds transitions from the new initial state to all the states that were in connection with the initial states of
    //the two NFAs (with the same letters)
    for(int i = 0; i < one.getCurrentTransitionsNum(); i++){
        if(one.transitions[i].from == one.getInitialState().name){
            Transition transition(initialState.name, one.transitions[i].to, one.transitions[i].literal);
            addTransition(transition);
        }
    }

    for(int j = 0; j < two.getCurrentTransitionsNum(); j++){
        if(two.transitions[j].from == two.getInitialState().name){
            Transition transition(initialState.name, two.transitions[j].to, two.transitions[j].literal);
            addTransition(transition);
        }
    }


    //adds all the transitions, except these which are from the initial states of the two NFA, to the union NFA transitions array
    for(int i = 0; i < one.getCurrentTransitionsNum(); i++){
        if(one.transitions[i].from == one.getInitialState().name && one.transitions[i].to == one.getInitialState().name){
            Transition transition(initialState.name, initialState.name, one.transitions[i].literal);
            addTransition(transition);
        }
        if(one.transitions[i].from != one.getInitialState().name)
            addTransition(one.transitions[i]);
    }

    for(int j = 0; j < two.getCurrentTransitionsNum(); j++){
        if(two.transitions[j].from == two.getInitialState().name && two.transitions[j].to == two.getInitialState().name){
            Transition transition(initialState.name, initialState.name, two.transitions[j].literal);
            addTransition(transition);
        }
        if(two.transitions[j].from != two.getInitialState().name)
            addTransition(two.transitions[j]);
    }

    //if one of the initial states of the NFAs is final then the new initial state is final too
    if(one.getInitialState().isFinal || two.getInitialState().isFinal)
        initialState.isFinal = true;

}

/**
 * @details concatenates two NFA.
 * @param one - reference to an object of type NFA;
 * @param two - reference to an object of type NFA;
 */
void NFA::Concat(const NFA& one, const NFA& two){
    //the initial state of the concatenation NFA is the initial state of the first NFA
    setInitialState(one.getInitialState());

    //adds all the states from the first NFA to the concatenation NFA's states array
    for(int i = 0; i < one.getCurrentStatesNum(); i++){
        addState(one.states[i]);
    }

    for(int j = 0; j < two.getCurrentStatesNum(); j++){
        if(two.states[j].name != two.initialState.name)
            addState(two.states[j]);
    }

    //adds all the states from the first NFA to the concatenation NFA's states array(except these which are from the initial state)
    for(int i = 0; i < one.getCurrentTransitionsNum(); i++){
        addTransition(one.transitions[i]);
    }

    //adds transitions from the first NFA final states to all the states that are in transition(to) with the initial state
    //of the second NFA
    for(int i = 0; i < one.getCurrentStatesNum(); i++){
        if(one.states[i].isFinal){
            for(int j = 0; j < two.getCurrentTransitionsNum(); j++){
                if(two.transitions[j].from == two.initialState.name){
                    Transition transition(one.states[i].name, two.transitions[j].to, two.transitions[j].literal);
                    addTransition(transition);
                }
            }
        }
    }

    //adds all the transitions of the second NFA to the concatenations NFA's transitions array
    for(int j = 0; j < two.getCurrentTransitionsNum(); j++){
        addTransition(two.transitions[j]);
    }

    //if the initial state of the second NFA is final than all the final states from the first NFA are final in the
    //concatenation NFA as well
    if(!two.getInitialState().isFinal){
        for(int i = 0; i < one.getCurrentStatesNum(); i++){
            states[i].isFinal = false;
        }
    }

}

/**
 * @brief Positive shell of NFA.
 * @param one - reference to an object of type NFA;
 */
void NFA::Positive(const NFA& one){
    int number = 0;
    //the initial state of the NFA is the initial state of the one NFA
    setInitialState(one.getInitialState());

    //adds all the states from the one NFA to the states array of the positive shell NFA
    for(int i = 0; i < one.getCurrentStatesNum(); i++){
        addState(one.states[i]);
    }

    //adds all the transitions from the one NFA to the transitions array of the positive shell NFA and counts them
    for(int i = 0; i < one.getCurrentTransitionsNum(); i++){
        addTransition(one.transitions[i]);
        number++;
    }

    //adds transition from all the final states of the one NFA to all the states that are in transition(to) with the
    //initial state and counts them
    for(int i = 0; i < one.getCurrentStatesNum(); i++){
        if(one.states[i].isFinal){
            for(int j = 0; j < one.getCurrentTransitionsNum(); j++){
                if(one.transitions[j].from == one.initialState.name){
                    Transition transition(one.states[i].name, one.transitions[j].to, one.transitions[j].literal);
                    addTransition(transition);
                    number++;
                }
            }
        }
    }

    currentTransitionsNum = number;
}

/**
 * @details Help function to check were transition goes to
 *
 * @param from - the from state of a transition;
 * @param literal - a literal used to pass in transition;
 * @param helpTransitions - dynamically allocated array of transitions;
 * @return - the first transition to-elemet that has from-element = "from" and literal = "literal"
 */
int NFA::help(int from, char literal, Transition* helpTransitions) const {
    int newTo = 777;
    for(int i=0;i<currentTransitionsNum;++i){
        if(helpTransitions[i].from == from && literal == helpTransitions[i].literal){
            newTo = helpTransitions[i].to;
            break;
        }
    }
    return newTo;
}

/**
 * @brief Checks if the NFA recognizes word.
 *
 * @param word - the word we are trying to recognize;
 * @return true if the NFA recognizes the word and false otherwise.
 * @see help(int from, char literal, Transition* helpTransitions) const
 */
bool NFA::recognise(char* word){
    Transition* wordTransitions= new Transition[currentTransitionsNum];
    for(int i=0;i<=strlen(word); ++i){
        if(i==0){
            //if the is no transition from the initial state with the first letter of the word returns false
            int to = help(initialState.name,word[i],transitions);
            if(to=='+')
                return false;

            //sets wordsTransition first element
            wordTransitions[i].from = initialState.name;
            wordTransitions[i].to = to;
            wordTransitions[i].literal = word[i];
        }

        //if we've read the whole word
        else if(i==strlen(word)){
            for(int j=0;j<currentStatesNum;j++){
                //check is the last element of the wordTransitions array is a transition which to-state is final
                if(wordTransitions[i-1].to == states[j].name && states[j].isFinal)
                    return true;
            }
            return false;

        }else{
            wordTransitions[i].from = wordTransitions[i-1].to;
            wordTransitions[i].literal = word[i];
            int tmp = help(wordTransitions[i].from, wordTransitions[i].literal, transitions);
            if(tmp != 777){
                wordTransitions[i].to = tmp;
            }else{
                int tmp2 = 777;
                i--;
                for(int j=0;j<currentTransitionsNum;j++){
                    if(transitions[j].from == wordTransitions[i].from && wordTransitions[i].literal == transitions[j].literal &&
                       transitions[j].to != wordTransitions[i].to){
                        tmp2 = transitions[j].to;
                        break;
                    }
                }
                if(tmp2 == 777){
                    return false;
                }
                else{
                    wordTransitions[i].to = tmp2;
                }
            }
        }
    }
}


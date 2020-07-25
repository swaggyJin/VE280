#include <iostream>
#include "dlist.h"
#include <sstream>
using namespace std;
class mismatched_parenthese{
};

class not_enough_operands{
};

class divide_by_zero{
};

class too_many_operands{
};

template<class T>
class stack {
private:
    Dlist<T> current_stack;

public:
    void push(T op) {
        T *new_op = new T;
        *new_op = op;
        current_stack.insertFront(new_op);
    }

    T pop() {
        T *medium = current_stack.removeFront();
        T result = *medium;
        delete medium;
        return result;
    }

    T top() {
        T *medium = current_stack.removeFront();
        T result = *medium;
        current_stack.insertFront(medium);
        return result;
    }

    bool empty() {
        return current_stack.isEmpty();
    }
};

bool is_Num(const string& str) {
    stringstream sin(str);
    double d;
    return !!(sin >> d);
};

bool is_num_operator(const string& medium){
    return medium=="+" || medium=="-" || medium=="*"  ||medium=="/";
}

bool is_left_parenthesis(const string& medium){
    return medium=="(" ;
}

bool is_right_parenthesis(const string& medium){
    return medium==")" ;
}
void empty_check(bool is_empty){
    if(is_empty){
        not_enough_operands b;
        throw b;
    }
}

int main() {
    try {
        stack<string> operator_stack;
        string medium;
        getline(cin,medium);
        stringstream whole_line(medium);
        stringstream output;
        while (whole_line>>medium) {
            //cout<<"Reading: "<<i<<" "<<medium<<endl;
            //i++;
            if(is_Num(medium)){
                output<<medium<<" ";
            }
            else if(is_num_operator(medium)){
                bool flag1= false;
                if(!operator_stack.empty()){
                    if(operator_stack.top()!="("){
                        if(is_num_operator(operator_stack.top())){
                            if(operator_stack.top()=="*"||operator_stack.top()=="/"){
                                flag1= true;
                            }else{
                                if(medium=="+"||medium=="-"){
                                    flag1= true;
                                }
                            }
                        }
                    }
                }
                while(flag1){
                    output<<operator_stack.pop()<<" ";
                    flag1= false;
                    if(!operator_stack.empty()){
                        if(operator_stack.top()!="("){
                            if(is_num_operator(operator_stack.top())){
                                if(medium=="+"||medium=="-"){
                                    flag1= true;
                                }
                            }
                        }
                    }
                    //cout<<"flag1: "<<flag1<<endl;
                }
                operator_stack.push(medium);
            }
            else if(is_left_parenthesis(medium)){
                operator_stack.push(medium);
            }
            else if(is_right_parenthesis(medium)){
                while(!is_left_parenthesis(operator_stack.top())){
                    output<<operator_stack.pop()<<" ";
                    if(operator_stack.empty()){
                        mismatched_parenthese a;
                        throw a;
                    }
                }
                if(is_left_parenthesis(operator_stack.top())){
                    operator_stack.pop();
                }
            }
        }
        //cout<<"!!"<<endl;
        while (!operator_stack.empty()){
            if(is_left_parenthesis(operator_stack.top())||is_right_parenthesis(operator_stack.top())){
                mismatched_parenthese a;
                throw a;
            }
            output<<operator_stack.pop()<<" ";
        }
        cout<<output.str()<<endl;
        stack<int> calculated_val;
        int medium_result;
        while(output>>medium){
            if(is_Num(medium)){
                calculated_val.push(stoi(medium));
            }else if(medium=="+"){
                empty_check(calculated_val.empty());
                medium_result=calculated_val.pop();
                empty_check(calculated_val.empty());
                medium_result=calculated_val.pop()+medium_result;
                calculated_val.push(medium_result);
            }else if(medium=="-"){
                empty_check(calculated_val.empty());
                medium_result=calculated_val.pop();
                empty_check(calculated_val.empty());
                medium_result=calculated_val.pop()-medium_result;
                calculated_val.push(medium_result);
            }else if(medium=="*"){
                empty_check(calculated_val.empty());
                medium_result=calculated_val.pop();
                empty_check(calculated_val.empty());
                medium_result=medium_result*calculated_val.pop();
                calculated_val.push(medium_result);
            }else if(medium=="/"){
                empty_check(calculated_val.empty());
                if(calculated_val.top()==0){
                    divide_by_zero c;
                    throw c;
                }
                medium_result=calculated_val.pop();
                empty_check(calculated_val.empty());
                //cout<<calculated_val.top()<<endl;
                medium_result=calculated_val.pop()/medium_result;
                calculated_val.push(medium_result);
            }else{
            }
            //cout<<calculated_val.top()<<endl;
        }
        int final_result=calculated_val.pop();
        if(!calculated_val.empty()){
            too_many_operands d;
            throw d;
        }
        cout<<final_result<<endl;
    }
    catch (mismatched_parenthese) {
        cout << "ERROR: Parenthesis mismatch" << endl;
    }
    catch(not_enough_operands){
        cout << "ERROR: Not enough operands" << endl;
    }
    catch (divide_by_zero) {
        cout << "ERROR: Divide by zero" << endl;
    }
    catch (too_many_operands) {
        cout << "ERROR: Too many operands" << endl;
    }
    return 0;
    //( ( ( ( 2 + 3 ) / ( 5 ) ) + 2 * ( 4 - 2 ) ) - 4 ) + 1
}



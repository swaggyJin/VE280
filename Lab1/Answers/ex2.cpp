/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    int judger[3]; unsigned int i;
    for (i=0;i<3;i++) {
        judger[i]=0;
    }
    for (i=0;i<50;i++) {
        if (password[i]=='\0'){ break ;}
        else{}
        if (password[i]=='a'||password[i]=='b'||password[i]=='c'||password[i]=='d'||password[i]=='e'
            ||password[i]=='f'||password[i]=='g'||password[i]=='h'||password[i]=='i'||password[i]=='j'
            ||password[i]=='k'||password[i]=='l'||password[i]=='m'||password[i]=='n'||password[i]=='o'
            ||password[i]=='p'||password[i]=='q'||password[i]=='r'||password[i]=='s'||password[i]=='t'
            ||password[i]=='u'||password[i]=='v'||password[i]=='w'||password[i]=='x'||password[i]=='y'
            ||password[i]=='z') {
            judger[0]++;
        }
        else if (password[i]=='0'||password[i]=='1'||password[i]=='2'||password[i]=='3'||password[i]=='4'
                 ||password[i]=='5'||password[i]=='6'||password[i]=='7'||password[i]=='8'||password[i]=='9'){
            judger[1]++;
        }
        else {
            judger[2]++;
        }
    }
    if (judger[0]==0||judger[1]==0||judger[2]==0){ return false;}
    else { return true;}
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}

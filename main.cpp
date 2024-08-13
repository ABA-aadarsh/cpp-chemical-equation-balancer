#include <cctype>
#include <cstdlib>
#include<iostream>
#include <iterator>
#include <set>
#include <string>
#include<vector>
#include<map>
#include"./linearsolver.hpp"
using namespace std;
set<string> uniqueElements (string const & expr){
    set<string> elements = {};
    string buff="";
    char c;
    for(int i=0; i<expr.length(); i++){
        buff="";
        c = expr[i];
        if(isalpha(c) && isupper(c)){
            buff+=c;
            i++;
            if(i == expr.length()) break;
            c = expr[i];
            while(isalpha(c) && islower(c)){
                buff += c;
                i++;
                if(i>=expr.length()) break;
                c = expr[i];
            }
            elements.insert(buff);
            i-=1;
        }else{
            continue;
        }
    }
    if(buff!=""){
        elements.insert(buff);
    }
    return elements;
}
int uniqueElementsCount (string & expr){
    set<string> elements = {};
    string buff="";
    char c;
    for(int i=0; i<expr.length(); i++){
        buff="";
        if(isalpha(expr[i]) && isupper(expr[i])){
            buff+=expr[i];
            i++;
            if(i == expr.length()) break;
            c = expr[i];
            while(isalpha(c) && islower(c)){
                buff += c;
                i++;
                if(i>=expr.length()) break;
                c = expr[i];
            }
            elements.insert(buff);
            i-=1;
        }else{
            continue;
        }
    }
    return elements.size();
}
int compoundsCount (string & expr){
    int c =0;
    for(int i=0; i<expr.length(); i++){
        if(isspace(expr[i]) || expr[i]=='+'){
            c++;
        }
    }
    c++;
    return c;
}
void compoundsList (string & expr, vector<string>& compoundsL){
    string buff;
    char ch;
    for(int i=0; i<expr.length(); i++){
        ch = expr[i];
        if(buff.empty() && isalpha(ch) && isupper(ch)){
            buff+=ch;
        }else if(!buff.empty() && (isalpha(ch) || isdigit(ch))){
            buff+=ch;
        }else{
            if(!buff.empty()){
                compoundsL.push_back(buff);
                buff="";
            }
        }
    }
    if(!buff.empty()){
        compoundsL.push_back(buff);
    }
}
void elementMapInitialise(set<string> &elementSet, map<string, int> &elementMap) {
    int i = 0;
    for (auto setItr = elementSet.begin(); setItr != elementSet.end(); setItr++) {
        elementMap[*setItr] = i;
        i++;
    }
}
void compoundTuple(string const & compd, int arr[], map<string, int> & elementMap){
    set<string> el = uniqueElements(compd);
    int i, j;
    string buff;
    for(auto itr=el.begin(), citr=el.begin(); itr!=el.end(); itr++){
        i = compd.find(*itr) + (*itr).length();
        if(isalpha(compd[i])|| i==compd.length()){
            arr[elementMap[*itr]] = 1;
            continue;
        }
        citr = next(itr);
        if(citr!=el.end()) {
            j = compd.find(*citr);
            buff = compd.substr(i,j-1);
            arr[elementMap[*itr]] = stoi(buff);
        }else{
            buff = compd.substr(i, compd.length()-1);
            arr[elementMap[*itr]] = stoi(buff);
        }
    }
}
int main() {
    int expr_separator, n;
    string expr_s, reactant_s, product_s;
    set<string> elementSet;
    map<string, int> elementMap;
    vector<string> reactants_list, product_list;

    cout << "Enter Chemical Equation\n";
    getline(cin, expr_s);
    expr_separator = expr_s.find("->");
    if (expr_separator == -1) {
        cerr << "\nInvalid expression. Expression must be of following "
                "type.\n[Reactants]->[Products]";
        return EXIT_FAILURE;
    }
    reactant_s = expr_s.substr(0, expr_separator);
    product_s = expr_s.substr(expr_separator + 2);

    // if (uniqueElementsCount(reactant_s) != uniqueElementsCount(product_s)) {
    //     cerr << "\nInvalid expression. No of different elements on reactant does "
    //             "not match with that in product side\n";
    //     return EXIT_FAILURE;
    // }
    elementSet = uniqueElements(reactant_s);
    n = elementSet.size();
    elementMapInitialise(elementSet, elementMap);


    compoundsList(reactant_s, reactants_list);
    compoundsList(product_s, product_list);

    int c = reactants_list.size()+product_list.size();
    // float table [n][c];
    float ** table;
    table = new float*[n];
    for(int i=0; i<n; i++){
        table[i] = new float[c];
    }
    int tableItr =0;
    int temp[n];
    // for(auto x=elementMap.begin(); x!=elementMap.end(); x++){
    //     cout << x->first<< " : " << x->second << endl;
    // }
    for(int i=0; i<reactants_list.size(); i++){
        for(int j=0; j<n; j++){temp[j]=0;}
        compoundTuple(reactants_list[i], temp, elementMap);
        for(int j=0; j<n; j++){
            table[j][tableItr]=temp[j];
        }
        tableItr++;
    }
    for(int i=0; i<product_list.size(); i++){
        for(int j=0; j<n; j++){temp[j]=0;}
        compoundTuple(product_list[i], temp, elementMap);
        for(int j=0; j<n; j++){
            table[j][tableItr]=-temp[j];
        }
        tableItr++;
    }
    // cout << "Table n="<<n<<"\n";
    // for(int i =0; i<n; i++){
    //     for(int j=0; j<reactants_list.size()+product_list.size(); j++){
    //         cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    float *soln = new float[c];
    solver(table, soln, n, c);
    int counter  = 0;
    for(int i =0; i<reactants_list.size(); i++){
        cout << "("<<soln[counter] << ") " << reactants_list[i];
        counter++;
        if(i==reactants_list.size()-1) continue;
        cout << " + ";
    }
    cout << " -> ";
    for(int i =0; i<product_list.size(); i++){
        cout << "("<<  soln[counter] << ") " << product_list[i];
        counter++;
        if(i==product_list.size()-1) continue;
        cout << " + ";
    }
    cout << '\n';
    delete []soln;
    for (int i = 0; i < n; ++i) {
        delete[] table[i];
    }
    delete []table;
    return EXIT_SUCCESS;
}

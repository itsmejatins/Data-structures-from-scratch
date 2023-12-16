//
//  ManualBigInteger.cpp
//  DSAP Assignment 1
//
//  Created by Jatin Sharma on 25/08/22.
//  Copyright © 2022 Jatin Sharma. All rights reserved.
// leading zeroes have been taken care of. Ignore comments warning regarding this.

#include <iostream>
#include <math.h>
using namespace std;

class ManualBigInteger
{
private:
    bool isOperator(char c)
    {
        return ((c == '+') || (c == '-') || (c == 'x') );
    }
    
    bool equalTo(string &m, string &n)
    {
        removeLeadingZeroes(m);
        removeLeadingZeroes(n);
        
        if(m.size() != n.size())
            return false;
        else
        {
            int x{};
            while(x < m.size())
            {
                int d1 = m[x] - '0';
                int d2 = n[x] - '0';
                if(d1 != d2)
                    return false;
                else
                    x++;
            }
        }
        return true;
    }
    
    void removeLeadingZeroes(string &m)
    {
        string trimmedResult{}; // result with removed leading zeroes
        int strInd = 0;
        while(m[strInd] == '0') strInd++;
        while(strInd < m.size())
            trimmedResult += m[strInd++];
        
        trimmedResult = (trimmedResult =="") ? "0" : trimmedResult;
        m = trimmedResult;
    }
    
    bool lessThan(string &m, string &n)
    {
        
        removeLeadingZeroes(m);
        removeLeadingZeroes(n);
        
        if(m.size() < n.size())
            return true;
        else if(m.size() > n.size())
            return false;
        else
        {
            int x{};
            while(x < m.size())
            {
                int d1 = m[x] - '0';
                int d2 = n[x] - '0';
                if(d1 < d2)
                    return true;
                else if(d1 > d2)
                {
                    return false;
                }
                else
                    x++;
            }
        }
        
        return false;
    }

    
public:
    
    string addition(string &m, string &n)
    {
        if(m.size() == 0 || m == "0")
        {
            return n;
        }
        
        if(n.size() == 0 || n == "0")
        {
            return m;
        }
        
        string result{};
        int carry{0}; // carry can be either 1 or 0.
        int i = static_cast<int>(m.size()-1), j = static_cast<int>(n.size()-1);
        
        while(i >= 0 || j >= 0)
        {
            int d1 = (i>=0)? (m[i] - '0') : 0; // stoi(to_string(m[i])) did not work
            int d2 = (j>=0)? (n[j] - '0') : 0;
            int temp_add = d1 + d2 + carry;
            int d_final = (temp_add > 9)?(temp_add - 10): temp_add;
            carry = (temp_add > 9) ? 1 : 0;
            result = to_string(d_final) + result;
            i--; j--;
            
        }
        if(carry == 1)
        {
            result = to_string(1) + result;
        }
        
        return result;
    }
    
    // m > n is compulsory, function returns on failure of this condition.
    string subtraction(string &m, string &n)
    {
        if(lessThan(m, n))
            return "Error - Cannot handle negative numbers, please provide m > n";
        
        if(n.size() == 0)
        {
            removeLeadingZeroes(m);
            return m;
        }
        
        if(m.size() == 0 || n.size() == 0)
        {
            return "";
        }
        
        removeLeadingZeroes(m);
        removeLeadingZeroes(n);
        
        
        string result{};
        int carry{0}; // carry can be either -1 or 0.
        int i = static_cast<int>(m.size()-1), j = static_cast<int>(n.size()-1);
        // cannot use size_t because size_t x = 0, x-1 = <a large number> instead of -1. Therefore if condition fails.
        
        while(i >= 0)
        {
            int d1 = m[i] - '0'; // no need to check i>=0 because m >= n always. So j can become negative, but i wont
            int d2 = (j>=0)? (n[j] - '0') : 0;
            
            int temp_sub = d1 - d2 + carry;
            int d_final = (temp_sub < 0) ? (10 + temp_sub) : temp_sub;
            carry = (temp_sub < 0) ? -1 : 0;
            result = to_string(d_final) + result;
            i--; j--;
        }
        
        string trimmedResult{}; // result with removed leading zeroes
        int strInd = 0;
        while(result[strInd] == '0') strInd++;
        while(strInd < result.size())
            trimmedResult += result[strInd++];
        return (trimmedResult =="") ? "0" : trimmedResult;
    }
    
    // Takes about 8 seconds for producing a 6291 digits output. Inputs were s1 = 1200! and s2 = 1180! ... !=factorial
    string multiplication(string &m, string &n)
    {
        if(m.size() == 0 || n.size() == 0)
            return "";
        
        removeLeadingZeroes(m);
        removeLeadingZeroes(n);
        
        
        if(m == "1")
            return n;
        if(n == "1")
            return m;
        
        // ensuring that m is the larger number
        if(m.size() < n.size())
        {
            swap(m, n);
        }
        
        string result{};
        int carry = 0; // carry can take any value from [0, 8]
        for(int j = static_cast<int>(n.size() -1) ; j >= 0 ; j--)
        {
            carry = 0;
            string temp_final_product {};
            for(int i = static_cast<int>(m.size() -1) ; i >= 0; i--) // Note that if you take size_t here, then i will never be equal to 0
            {
                int d1 = m[i] - '0';
                int d2 = n[j] - '0';
                
                int temp_product = d1 * d2 + carry;
                int d_final = (temp_product > 9) ? (temp_product % 10) : (temp_product);
                carry = (temp_product > 9) ? (temp_product / 10) : 0;
                temp_final_product = to_string(d_final) + temp_final_product;
            }
            // if last multiplication produced a carry
            if(carry > 0)
            {
                temp_final_product = to_string(carry) + temp_final_product;
            }
            for(int i = 0; i < static_cast<int>(n.size() -1) - j; i++)
            {
                temp_final_product+="0";
            }
            result = addition(result, temp_final_product);
        }
        
        return result;
    }
    

    // Takes about 17 seconds to produce an output of 6231 digits. Input = 2345234 ^ 978
    string exponentiation(string &base, unsigned long long exponent)
    {
        removeLeadingZeroes(base);
        // writing identities for exponentitation
        if(base == " 1")
            return "1";
        if(base == "0")
            return "0";
        
        if(exponent == 0)
        {
            return "1";
        }
        if(exponent == 1)
        {
            return base;
        }
        
        
        if(exponent % 2 == 0)
        {
            string new_base = multiplication(base, base);
            return exponentiation(new_base, exponent/2);
        }
        else
        {
            string temp1 = base;
            string temp2 = exponentiation(base, exponent - 1);
            return multiplication(temp1, temp2);
        }
        
    }
    
    // factorial of 1200 contains 3176 digits. Therefore int will work as an argument.
    // Also this function produces output quickly for input = 1200.
    string factorial(int n)
    {
        string result{"1"};
        
        for(int i = 1; i <=n ; i++)
        {
            string str = to_string(i);
            result = multiplication(str, result);
        }
        return result;
    }
    
    string operate(string &operand1, string &operand2, char operatorr)
    {
        removeLeadingZeroes(operand1);
        removeLeadingZeroes(operand2);
        
        if(operatorr == 'x')
            return multiplication(operand1, operand2);
        else  if(operatorr == '+')
            return addition(operand1, operand2);
        else
            return subtraction(operand1, operand2);
    }
    
    string readInfix(string &input)
    {
        if(input =="") return "";
        removeLeadingZeroes(input);
        string result{};
        
        string intermediary{};
        string operand1{}, operand2{}; // used for multiplication
        bool prevCopy = true; // if you need to copy previous string before ± (when there was no result of  multiplication to be added to the string
        bool lastCopy = true;
        int p1 = 0, p2 = 0;
        while(p2 < input.size())
        {
            if(!isOperator(input[p2]))
            {
                p2++;
                continue;
            }
            else if((input[p2] == '+') || (input[p2] == '-'))
            {
                if(prevCopy == true)
                {
                    string temp{};
                    while(p1 <= p2) // p1 should be at the start of the string digit.
                    {
                        
                        temp += input[p1];
                        p1++;
                    }
                    intermediary+=temp;
                    p2++; // ex - 123+456x789x987x546-32+89, at this point p1, p2 are at 4
                }
                else
                {
                    intermediary += input[p2];
                    p2++;
                    p1 = p2;
                    // now p1, p2 both point to the first digit of the next operand
                    // Now run the program as if you are reading the string for the first time
                    prevCopy = true;
                    
                }
            }
            else
            {
                while(p1 < p2)
                {
                    operand1+=input[p1++];
                }
                p1 ++; p2++; // p1, p2 are at 7, ie, the first digit of the next operand
                while(p2 < input.size() && !isOperator(input[p2])) p2++;
                while(p1 < p2)
                {
                    operand2 += input[p1++];
                }
                // p1 and p2 point to the next operator (x in this example)
                string tempRes = multiplication(operand1, operand2);
                operand1 = tempRes;
                if(p2 >= input.size()) lastCopy = false; // ie, multiplication result will be added as the last operand.
                while(p2 < input.size() && input[p2] == 'x')
                {
                    operand2 = "";
                    // p2 currently points to the next x.
                    p1++; p2++; // p1, p2 point to the start of the digit after multiplicatiom
                    while(p2 < input.size() && !isOperator(input[p2])) p2++;
                    while(p1 < p2)
                    {
                        operand2 += input[p1++];
                    }
                    // p1, p2  points to the next operator
                    
                    tempRes = multiplication(operand1, operand2);
                    operand1 = tempRes;
                }
                // p2 now points to + or - or the end of the input
                intermediary += tempRes;
                p1++; // p1 points to the first next operand after ± or end of the input
                operand1 = ""; operand2 = "";tempRes = "";
                prevCopy = false;
                // means ± did not occur for the first time, so just paste the operator and copy the आगे वाली string
            }
        }
        // to copy the last operand
        if(lastCopy == true)
        {
            while(p1 < p2)
            {
                intermediary += input[p1++];
            }
        }
        // INTERMEDIARY STRING IS READY - ex = 123+456+789-987-654
        p1 = p2 = 0;
        operand1=""; operand2="";
        
        while(p2 < intermediary.size() && !isOperator(intermediary[p2])) p2++;
        if(p2 == intermediary.size()) // this means that intermediary has only one number, input string was like 3213x354
            return intermediary;
        // p2 is at +
        char op = intermediary[p2];
        while(p1 < p2)
        {
            operand1 += intermediary[p1++];
        }
        p2++; p1++; //both are at 4
        while(p2 < intermediary.size() && !isOperator(intermediary[p2])) p2++;
        // p2 is at + or out of bound
        while(p1 < p2)
        {
            operand2 += intermediary[p1++];
        }
        // p1, p2 point to the + or end of the input
        result = operate(operand1, operand2, op);
        operand1 = result;
        while(p2 < intermediary.size())
        {
            op = intermediary[p2];
            operand2 = "";
            p2++; p1 = p2; // both at 7
            while(p2 < intermediary.size() && !isOperator(intermediary[p2])) p2++;
            while(p1 < p2)
            {
                operand2 += intermediary[p1++];
            }
            result = operate(operand1, operand2, op);
            operand1 = result;
        }
//        123+456+789-987-654
        return result;
    }
    
    string gcd(string &m, string &n)
    {
        removeLeadingZeroes(m);
        removeLeadingZeroes(n);
        if(m == "1" || n == "1")
            return "1";
        
        if(lessThan(m, n))
            swap(m, n);
        
        string diff = "";
        while(diff != "0")
        {
            diff = subtraction(m, n);
            if(lessThan(diff, n))
            {
                m = n;
                n = diff;
            }
            else
                m = diff;
        }
        return m;
    }

    // NOTE 
    // m % n, the code is unstable, hence commented
    // the code works correctly most of the times, but gives error in few cases.
    // hence gcd using modulus is being commented and instead gcd is being performed using subtraction
//    string modulus(string &n, string &m)
//    {
//        if(lessThan(n, m))
//        {
//            return n;
//        }
//        if(equalTo(n, m))
//        {
//            return "0";
//        }
//        string remainder{}, subDividend{};
//        int p2 = 0;
//        while(true)
//        {
//            if(p2 >= n.size() && lessThan(subDividend, m))
//                break;
//
//            while(subDividend.size() < m.size())
//            {
//                subDividend += n[p2];
//                p2++;
//            }
//            if(!lessThan(m, subDividend) && !equalTo(m, subDividend)) // ie, greater than
//                subDividend += n[p2++];
//
//            int times{}; // m * times is less than subdividend
//            for(times = 2; times <= 9; times++) // 8* 9 = 72 => times will be 10
//            {
//                string temp1 = to_string(times);
//                string temp2 = multiplication(m, temp1);
//                if(!lessThan(temp2, subDividend) && !equalTo(temp2, subDividend))
//                {
//                    times--;
//                    break;
//                }
//                if(equalTo(temp2, subDividend))
//                    break;
//            }
//            string temp1 = to_string(times);
//            string temp2 = multiplication(m, temp1);
//            string subtractedValue = subtraction(subDividend, temp2);
//            subtractedValue = (subtractedValue == "0") ? "" : subtractedValue;
//            while(subtractedValue.size() < m.size())
//            {
//                if(p2 >= n.size())
//                    break;
//
//                subtractedValue += n[p2++];
//            }
//            subDividend = subtractedValue;
//            remainder = subtractedValue;
//        }
//
//
//        return (remainder == "") ? "0" : remainder;
//    }
//
//    string gcd2(string &m, string &n)
//    {
//        string result{};
//        if(lessThan(m, n))
//        {
//            swap(m, n);
//        }
//        while(true)
//        {
//            string mod = modulus(m, n);
//            if(mod == "0")
//            {
//                result = n;
//                break;
//            }
//            m = n;
//            n = mod;
//        }
//
//        return result;
//    }

};

int main()
{
//    string input;
//    cin >> input;
    
    ManualBigInteger b;
    string s1 = "15", s2 = "2";
    string s = "0022+0654-96+300450x0503405x20034x00234-0000+0003";

    cout << b.subtraction(s2, s2) << endl;
    
//    int count{};
//    string s1 = "1564564564", s2 = "2";
//    while(b.subtraction(s1, s2) != "0")
//    {
//        s1 = b.subtraction(s1, s2);
//        cout << count++ << endl;
//    }
    
    
    
}

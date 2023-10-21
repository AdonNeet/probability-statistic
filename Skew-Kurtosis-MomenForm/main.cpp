#pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma") // if the machine use intel
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <iomanip>  
 
using namespace std;

typedef long long ll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


void recurData(vector<int>& rdA, vector<int>& rdB, vector<int>& freq, int pos) {
    if(pos != rdA.size()) {
            cout << "| " << rdA[pos] << "-" << rdB[pos] << " | " << freq[pos] << " |  \n";
            recurData(rdA, rdB, freq, pos+1);
    } else {
        cout << endl;
    }
}

void dataTable(vector<int>& rdA, vector<int>& rdB, vector<int>& freq) {
    cout << "| Data Range | Frequency |  \n";
    cout << "| :--------: | :-------: |  \n";

    recurData(rdA, rdB, freq, 0);    
}

int recFreq(vector<int>& freq, int pos) {
    if(pos != freq.size()-1) {
        return (freq[pos] + recFreq(freq, pos+1));
    } else {
        return freq[pos];
    }
}

int getN(vector<int>& freq) {
    int ans = recFreq(freq, 0);
    return ans;
}

void recurMed(vector<int>& rdA, vector<int>& rdB, vector<long double>& med, vector<int>& freq, int pos) {
    if(pos != rdA.size()) {
            med.push_back((static_cast<double>(rdA[pos]+rdB[pos]))/2);
            
            cout << "| " << rdA[pos] << "-" << rdB[pos] << " | " << med[pos] <<  " | " << freq[pos] << " |  \n";
            recurMed(rdA, rdB, med, freq, pos+1);
    } else {
        cout << "  \n";
    }
}

void medTable(vector<int>& rdA, vector<int>& rdB, vector<long double>& med, vector<int>& freq) {
    cout << "| Data Range | Median | Frequency |  \n";
    cout << "| :--------: | :----: | :-------: |  \n";

    recurMed(rdA, rdB, med, freq, 0);    
}

tuple<long double, long double, long double, long double, long double> sumAll(vector<long double>& xBar, vector<long double>& abst, vector<long double>& pwTwo, vector<long double>& pwThree, vector<long double>& pwFour) {
    long double sumBar = 0, sumAbs = 0, sumTwo = 0, sumThree = 0, sumFour = 0; 

    for(int i = 0; i < xBar.size(); i++) {
        sumBar += xBar[i];
        sumAbs += abst[i];
        sumTwo += pwTwo[i];
        sumThree += pwThree[i];
        sumFour += pwFour[i];
    }

    cout << "| $$\\sum total$$ | " << setprecision(10) << sumBar << " | " << setprecision(10) << sumAbs << " | " << setprecision(10) << sumTwo << " | " << setprecision(10) << sumThree << " | " << setprecision(10) << sumFour << " |  \n\n";
    return make_tuple(sumBar, sumAbs, sumTwo, sumThree, sumFour);
}

tuple<long double, long double, long double, long double, long double>  recurCore(vector<int>& freq, vector<long double>& xBar, vector<long double>& abst, vector<long double>& pwTwo, vector<long double>& pwThree, vector<long double>& pwFour, double rate, int pos) {
    if(pos != freq.size()){
        abst.push_back((static_cast<double>(freq[pos])) * xBar[pos]);
        if(abst[pos] < 0) abst[pos] *= -1;

        pwTwo.push_back((static_cast<double>(freq[pos])) * xBar[pos] * xBar[pos]);
        pwThree.push_back((static_cast<double>(freq[pos])) * xBar[pos] * xBar[pos] * xBar[pos]);
        pwFour.push_back((static_cast<double>(freq[pos])) * xBar[pos] * xBar[pos] * xBar[pos] * xBar[pos]);

        cout << "| " << freq[pos] << " | " << setprecision(10) << xBar[pos] << " | " << setprecision(10) << abst[pos] << " | " << setprecision(10) << pwTwo[pos] << " | " << setprecision(10) << pwThree[pos] << " | " << setprecision(10) << pwFour[pos] << " |  \n";
        return recurCore(freq, xBar, abst, pwTwo, pwThree, pwFour, rate, pos+1);
    } else {
        return sumAll(xBar, abst, pwTwo, pwThree, pwFour);
    }
}

tuple<long double, long double, long double, long double, long double>  coreTable(vector<int>& freq, vector<long double>& xBar, vector<long double>& abst, vector<long double>& pwTwo, vector<long double>& pwThree, vector<long double>& pwFour, double rate) {
    cout << "| Frequency | $$x-\\bar{x}$$ | $$F\\|x-\\bar{x}\\|$$ | $$F(x-\\bar{x})^2$$ | $$F(x-\\bar{x})^3$$ | $$F(x-\\bar{x})^4$$ |  \n";
    cout << "| :-------: | :----: | :-------: | :---------: | :---------: | :---------: |  \n";

    return recurCore(freq, xBar, abst, pwTwo, pwThree, pwFour, rate, 0); 
}

void getSkew(long double sumTwo, long double sumThree){
    cout << "<h2>Skewness</h2>  \n\n" 
         << "| Math Operation | Formula | Calculation Steps |  \n"
         << "| :------------: | :-----: | :---------------: |  \n";
    cout << "| $$M_2$$ | $$\\frac{1}{100}\\times\\sum F(x-\\bar{x})^2$$ | $$ \\frac{1}{100}\\times (" << sumTwo << ") \\\\  " << sumTwo/100 << " $$ |  \n";
    cout << "| $$M_3$$ | $$\\frac{1}{100}\\times\\sum F(x-\\bar{x})^3$$ |$$ \\frac{1}{100}\\times (" << sumThree << ") \\\\  " << sumThree/100 << " $$ |  \n";
    cout << "| $$S$$ | $$\\sqrt(M_2)$$ |$$ \\sqrt(" << sumTwo/100 << ") \\\\  "<< setprecision(10) << sqrt(sumTwo/100) << " $$ |  \n";
    cout << "| $$S^3$$ | $$(\\sqrt(M_2))^3$$ |$$ (\\sqrt(" << sumTwo/100 << "))^3 \\\\  " << setprecision(10) << pow(sqrt(sumTwo/100), 3) << " $$ |  \n";
    cout << "| $$\\alpha_3$$ | $$\\frac{M_3}{S^3}$$ |$$ \\frac{" << sumThree/100  <<"}{"<< pow(sqrt(sumTwo/100), 3) <<"}  \\\\  " << (sumThree/100)/(pow(sqrt(sumTwo/100), 3)) << " $$ |  \n";
}

int main() 
{
    #ifndef input_data
    freopen("input.in", "r", stdin);
    freopen("output.md", "w", stdout);
    #endif

    vector<int> rdA, rdB, freq; 
    vector<long double> med, xBar, abst, pwTwo, pwThree, pwFour;
    long double sumBar, sumAbs, sumTwo, sumThree, sumFour;
    string temp[2]; double tempe;

    // int post = 0; // to safe post, or to know how much the data
    fast_cin();
    while (true) {
        getline(cin, temp[0]);

        if (temp[0].empty() || temp[0] == temp[1]) {
            break; // Stop when the input is empty or same with before
        }
        // else if(post > 10) {
        //     break;
        // }

        int number = 0; bool nmA = false, nmB = false, nmF = false;
        for(char c : temp[0]) {
            if (isdigit(c)) {
                number = number * 10 + (c - '0');
            } else if(nmA == false) {
                rdA.push_back(number);
                number = 0;
                nmA = true;
            } else if(nmB == false) {
                rdB.push_back(number);
                number = 0;
                nmB = true;
            } 
        }
        freq.push_back(number);
        // F += number;    // alter to efficiency problem
        number = 0;
        nmF = true;

        // post++;
        temp[1] = temp[0];
    }

    cout << "The source data:  \n";
    dataTable(rdA, rdB, freq);

    int F = 0;
    F = getN(freq);
    cout << "Population = " << F << "  \n\n";
    
    medTable(rdA, rdB, med, freq);

    long double rate;
    for(int i = 0; i < rdA.size(); i++) {
        tempe += freq[i] * med[i];
    }
    rate = tempe/F;
    cout << "Mean = " << tempe << "/" << F << " = " << rate << "  \n\n";

    for(int i = 0; i < med.size(); i++) {
        xBar.push_back(med[i] - rate);
    }

    tie(sumBar, sumAbs, sumTwo, sumThree, sumFour) = coreTable(freq, xBar, abst, pwTwo, pwThree, pwFour, rate);
    // cout << "Check the return -> " << setprecision(10) << sumBar << " " << setprecision(10) << sumAbs << " " << setprecision(10) << sumTwo << " " << setprecision(10) << sumThree << " " << setprecision(10) << sumFour << "  \n";

    getSkew(sumTwo, sumThree);
    return 0;
}
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

void recurMeanMed(vector<int>& rdA, vector<int>& rdB, vector<long double>& med, vector<int>& freq, int F, long double tempe, int pos) {
    if(pos != rdA.size()) { 
            tempe += med[pos]*static_cast<double>(freq[pos]);           
            cout << "| " << rdA[pos] << "-" << rdB[pos] << " | " << med[pos] <<  " | " << freq[pos] << " | " << setprecision(10) << med[pos]*static_cast<double>(freq[pos]) << " |  \n";
            recurMeanMed(rdA, rdB, med, freq, F, tempe, pos+1);
    } else {
        
        cout << "| $$\\sum total$$ | | "<< F <<" | " << setprecision(10) << tempe << " |  \n\n";
        cout << "$$\\bar{X} = \\frac{\\sum{fX}}{\\sum{f}} = \\frac{" << setprecision(10) << tempe << "}{" << F << "} = " << setprecision(10) << tempe/static_cast<double>(F) <<"$$  \n\n";
    }
}

void meanMed(vector<int>& rdA, vector<int>& rdB, vector<long double>& med, vector<int>& freq, int F) {
    cout << "| Data Range | Median | Frequency | fX  |  \n";
    cout << "| :--------: | :----: | :-------: | :-: | \n";

    recurMeanMed(rdA, rdB, med, freq, F, 0, 0);    
}

void recurMeanU(vector<int>& rdA, vector<int>& rdB, vector<long double>& med, vector<int>& freq, int F, long double tempe, long double Xo, int pos) {
    if(pos != rdA.size()) { 
            int medF = floor(rdA.size()/2);
            int u = pos-medF;
            if(u==0) {
                Xo = med[pos];
            } 
            tempe += u*static_cast<double>(freq[pos]);           
            cout << "| " << rdA[pos] << "-" << rdB[pos] << " | " << med[pos] << " | " << u <<  " | " << freq[pos] << " | " << setprecision(10) <<  u*static_cast<double>(freq[pos]) << " |  \n";
            recurMeanU(rdA, rdB, med, freq, F, tempe, Xo, pos+1);
    } else {
        
        cout << "| $$\\sum total$$ | | | "<< F <<" | " << setprecision(10) << tempe << " |  \n\n";
        cout << "$$\\bar{X} = X_0 + c(\\frac{\\sum{fU}}{\\sum{f}}) = "<< Xo << "+" << rdB[pos-1]-rdA[pos-1]+1 << " (\\frac{" << setprecision(10) << tempe << "}{" << F << "}) = " << setprecision(10) << Xo+(static_cast<long double>(rdB[pos-1]-rdA[pos-1]+1)*(tempe/static_cast<double>(F)))<<"$$  \n\n";
    }
}

void meanU(vector<int>& rdA, vector<int>& rdB, vector<long double>& med, vector<int>& freq, int F) {
    cout << "| Data Range | Median |  U  | Frequency|  fU  |  \n";
    cout << "| :--------: | :----: | :-: |:-------: | :--: | \n";

    recurMeanU(rdA, rdB, med, freq, F, 0, 0, 0);    
}


void getMed(vector<int>& rdA, vector<int>& rdB, vector<int>& freq, int F, int tempf, int pos) {
    if(pos < rdA.size()) {
        long double medF;
        if(F%2==0){
            medF = F/2 + 0.5;
        }else {
            medF = (F+1)/2;
        }
        tempf += freq[pos];

        if(medF <= tempf){
            cout << "Median Pos = " << medF << " ; Median in range "<< rdA[pos] << "-" << rdB[pos] << "  \n";
            cout << "$$L_0 = " << rdA[pos] - 0.5 << "$$  \n";
            cout << "c = " << rdB[pos]-rdA[pos]+1 << " ; " << "F = " << tempf-freq[pos] << " ; f = " << freq[pos] << " ; n = " << F << "  \n";
            cout << "$$Med = " <<  rdA[pos] - 0.5 << " + " << rdB[pos]-rdA[pos]+1 << "(\\frac{\\frac{" << F << "}{2}-"<< tempf-freq[pos]  <<"}{" << freq[pos] << "}) = " << setprecision(10) << static_cast<long double>(rdA[pos] - 0.5) + (static_cast<long double>(rdB[pos]-rdA[pos]+1) * (static_cast<long double>(static_cast<long double>(F/2)-static_cast<long double>(tempf-freq[pos])) / static_cast<long double>(freq[pos]))) << "$$  \n\n";
            pos = rdA.size();
        }
        getMed(rdA, rdB, freq, F, tempf, pos+1);
    }     
}

// void getMod

int main() {
    #ifndef input_data
    freopen("input.in", "r", stdin);
    freopen("output.md", "w", stdout);
    #endif

    vector<int> rdA, rdB, freq; 
    vector<long double> med, xBar, abst, pwTwo, pwThree, pwFour;
    long double sumBar, sumAbs, sumTwo, sumThree, sumFour;
    string temp[2]; double tempe;

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

    cout << "<h1>Size of Data Centering and Location</h1>  \n\n";
    dataTable(rdA, rdB, freq);

    int F = 0;
    F = getN(freq);
    cout << "Population = " << F << "  \n\n";

    medTable(rdA, rdB, med, freq);

    cout << "<h2>Mean</h2>  \n\n";
    meanMed(rdA, rdB, med, freq, F);
    meanU(rdA, rdB, med, freq, F);

    cout << "<h2>Median</h2>  \n\n";
    getMed(rdA, rdB, freq, F, 0, 0);

    cout << "<h2>Modus</h2>  \n\n";

}
//
//  main.cpp
//  Final4
//
//  Created by Andrey Styskin on 23.02.2019.
//  Copyright © 2019 Andrey Styskin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef pair<string, int> si;
typedef vector<si> vsi;
typedef vector<string> vs;

vs CODON_A({"GCT", "GCC", "GCA", "GCG"});
vs CODON_R({"CGT", "CGC", "CGA", "CGG", "AGA", "AGG"});
vs CODON_N({"AAT", "AAC"});
vs CODON_D({"GAT", "GAC"});
vs CODON_C({"TGT", "TGC"});
vs CODON_Q({"CAA", "CAG"});
vs CODON_E({"GAA", "GAG"});
vs CODON_G({"GGT", "GGC", "GGA", "GGG"});
vs CODON_H({"CAT", "CAC"});
vs CODON_I({"ATT", "ATC", "ATA"});
vs CODON_L({"TTA", "TTG", "CTT", "CTC", "CTA", "CTG"});
vs CODON_K({"AAA", "AAG"});
vs CODON_M({"ATG"});
vs CODON_F({"TTT", "TTC"});
vs CODON_P({"CCT", "CCC", "CCA", "CCG"});
vs CODON_S({"TCT", "TCC", "TCA", "TCG", "AGT", "AGC"});
vs CODON_T({"ACT", "ACC", "ACA", "ACG"});
vs CODON_W({"TGG"});
vs CODON_Y({"TAT", "TAC"});
vs CODON_V({"GTT", "GTC", "GTA", "GTG"});
vs CODON_STOP({"TAA", "TGA", "TAG"});


unordered_map<char, vs> m;

void init() {
    m['A'] = CODON_A;
    m['R'] = CODON_R;
    m['N'] = CODON_N;
    m['D'] = CODON_D;
    m['C'] = CODON_C;
    m['Q'] = CODON_Q;
    m['E'] = CODON_E;
    m['G'] = CODON_G;
    m['H'] = CODON_H;
    m['I'] = CODON_I;
    m['L'] = CODON_L;
    m['K'] = CODON_K;
    m['M'] = CODON_M;
    m['F'] = CODON_F;
    m['P'] = CODON_P;
    m['S'] = CODON_S;
    m['T'] = CODON_T;
    m['W'] = CODON_W;
    m['Y'] = CODON_Y;
    m['V'] = CODON_V;
    m['$'] = CODON_STOP;
}

/*
Ala / A                                     Leu / L    TTA, TTG, CTT, CTC, CTA, CTG    YTR, CTN
Arg / R        CGN, MGR                     Lys / K    AAA, AAG    AAR
Asn / N    AAT, AAC    AAY                  Met / M    ATG
Asp / D    GAT, GAC    GAY                  Phe / F    TTT, TTC    TTY
Cys / C    TGT, TGC    TGY                  Pro / P    CCT, CCC, CCA, CCG    CCN
Gln / Q    CAA, CAG    CAR                  Ser / S    TCT, TCC, TCA, TCG, AGT, AGC    TCN, AGY
Glu / E    GAA, GAG    GAR                  Thr / T    ACT, ACC, ACA, ACG    ACN
Gly / G    GGT, GGC, GGA, GGG    GGN        Trp / W    TGG
His / H    CAT, CAC    CAY                  Tyr / Y    TAT, TAC    TAY
Ile / I    ATT, ATC, ATA    ATH             Val / V    GTT, GTC, GTA, GTG    GTN
START    ATG                                STOP    TAA, TGA, TAG    TAR, TRA
*/


string realization(const string& p) {
    stringstream ss;
    for (int i = 0; i < p.length(); ++i) {
        ss << m[p[i]][0];
    }
    return ss.str();
}

int byLength(const si& a, const si& b) {
    return a.first.length() > b.first.length();
}

int main(int argc, const char * argv[]) {
    init();
    
    for (int T = 3; T <= 6; ++T) {
        string path("/Users/styskin/bio2019/Final4/");
        ifstream in;
        in.open(path + to_string(T) + ".txt");
        ofstream out;
        out.open(path + to_string(T) + ".out");
        int N;
        in >> N;
        
        
        vsi proteins;
        string ans;
        vector<int> pos(N);
        for (int i = 0; i < N; ++i) {
            string s;
            in >> s;
            proteins.push_back(pair<string, int>(s, i));
        }
        
        sort(proteins.begin(), proteins.end(), byLength);

        for (int i = 0; i < N; ++i) {
            string r = realization(proteins[i].first);
    //        out << proteins[i].first << " " << r << endl;
            if (ans.find(r) != string::npos) {
                pos[proteins[i].second] = ans.find(r) + 1;
            } else {
                pos[proteins[i].second] = ans.length() + 1;
                ans += r;
            }
        }
        out << ans << endl;
        for (int i = 0; i < pos.size(); ++i) {
            out << pos[i] << " +" << endl;
        }
        in.close();
        out.close();
    }
    return 0;
}

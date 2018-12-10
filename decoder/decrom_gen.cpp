#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define MAR_I       (int)pow(2,0)
#define MAR_O       (int)pow(2,1)

#define RAM_I       (int)pow(2,2)
#define RAM_O       (int)pow(2,3)

#define ACC_IH      (int)pow(2,4)
#define ACC_IL      (int)pow(2,5)
#define ACC_O       (int)pow(2,6)

#define RA_I        (int)pow(2,7)
#define RA_O        (int)pow(2,8)

#define RB_I        (int)pow(2,9)
#define RB_O        (int)pow(2,10)

#define ALU_I       (int)pow(2,11)
#define ALU_O       (int)pow(2,12)
#define SUB         (int)pow(2,13)

#define PC_I        (int)pow(2,14)
#define PC_INC      (int)pow(2,15)
#define PC_O        (int)pow(2,16)

#define RO_I        (int)pow(2,17)
#define RO_O        (int)pow(2,18)

#define DEC_I       (int)pow(2,19)

#define SCREEN_CLR  (int)pow(2,20)

#define RSTF        (int)pow(2,21)
#define REFF        (int)pow(2,22)


using namespace std;

int main() {

int nop[8]   = {          0,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int nop3[8]  = {          0,                   0,           0,                   0,                PC_INC,      PC_INC,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int lda[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I,  RAM_O+RA_I,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int ldb[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I,  RAM_O+RB_I,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int ldo[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I,  RAM_O+RO_I,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int sta[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I,  RA_O+RAM_I,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int stb[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I,  RB_O+RAM_I,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int sto[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I,  RO_O+RAM_I,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int awb[8]   = {  RA_I+RB_O,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int awo[8]   = {  RO_I+RA_O,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int aluwa[8] = { RA_I+ALU_O,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int aluwb[8] = { RB_I+ALU_O,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int aluwo[8] = { RO_I+ALU_O,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int add[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC,           ACC_O+MAR_I, ALU_O+RAM_I, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int addwa[8] = {      ALU_I,          ALU_O+RA_I,           0,                   0,                     0,           0, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int addwb[8] = {      ALU_I,          ALU_O+RB_I,           0,                   0,                     0,           0, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int addwo[8] = {      ALU_I,          ALU_O+RO_I,           0,                   0,                     0,           0, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int sub[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I, RAM_O+ACC_IL+PC_INC, ACC_O+MAR_I+SUB+ALU_I, ALU_O+RAM_I, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int subwa[8] = {  SUB+ALU_I,          ALU_O+RA_I,           0,                   0,                     0,           0, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int subwb[8] = {  SUB+ALU_I,          ALU_O+RB_I,           0,                   0,                     0,           0, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };
int subwo[8] = {  SUB+ALU_I,          ALU_O+RO_I,           0,                   0,                     0,           0, REFF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int jmp[8]   = { MAR_I+PC_O, RAM_O+ACC_IH+PC_INC,  PC_O+MAR_I,        RAM_O+ACC_IL,            ACC_O+PC_I,           0, RSTF+MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

int sclr[8]  = { SCREEN_CLR,                   0,           0,                   0,                     0,           0,      MAR_I+PC_O, RAM_O+DEC_I+PC_INC  };

    vector<int*> microcode;
    microcode.push_back(nop);           // nop      00
    microcode.push_back(lda);           // lda      01
    microcode.push_back(ldb);           // ldb      02
    microcode.push_back(ldo);           // ldo      03
    microcode.push_back(sta);           // sta      04
    microcode.push_back(stb);           // stb      05
    microcode.push_back(sto);           // sto      06
    microcode.push_back(awb);           // awb      07
    microcode.push_back(awo);           // awo      08
    microcode.push_back(aluwa);         // aluwa    09
    microcode.push_back(aluwb);         // aluwb    0a
    microcode.push_back(aluwo);         // aluwo    0b
    microcode.push_back(add);           // add      0c
    microcode.push_back(addwa);         // addwa    0d
    microcode.push_back(addwb);         // addwb    0e
    microcode.push_back(addwo);         // addwo    0f
    microcode.push_back(sub);           // sub      10
    microcode.push_back(subwa);         // subwa    11
    microcode.push_back(subwb);         // subwb    12
    microcode.push_back(subwo);         // subwo    13
    microcode.push_back(jmp);           // jmp      14
    microcode.push_back(nop3);          // jc       15
    microcode.push_back(jmp);           // jcn      16
    microcode.push_back(nop3);          // jz       17
    microcode.push_back(jmp);           // jzn      18
    microcode.push_back(nop3);          // jcz      19
    microcode.push_back(jmp);           // jczn     1a
    microcode.push_back(sclr);          // sclr     1b

    vector<int*> microcode_zf(microcode);
    microcode_zf[23] = jmp;
    microcode_zf[24] = nop3;
    vector<int*> microcode_cf(microcode);
    microcode_cf[21] = jmp;
    microcode_cf[22] = nop3;
    vector<int*> microcode_zcf(microcode);
    microcode_zcf[21] = jmp;
    microcode_zcf[22] = nop3;
    microcode_zcf[23] = jmp;
    microcode_zcf[24] = nop3;
    microcode_zcf[25] = jmp;
    microcode_zcf[26] = nop3;

    cout << std::hex ;
    for (int i(0); i < 8; i++) {

        for (int j(0); j < microcode.size(); j++) {

            for (int flags(0); flags < 4; flags++) {
    
                switch (flags) {
                    case 0:
                        cout << std::setfill('0') << std::setw(8) << microcode[j][i] << " ";
                        break;
                    case 1:
                        cout << std::setfill('0') << std::setw(8) << microcode_zf[j][i] << " ";
                        break;
                    case 2:
                        cout << std::setfill('0') << std::setw(8) << microcode_cf[j][i] << " ";
                        break;
                    case 3:
                        cout << std::setfill('0') << std::setw(8) << microcode_zcf[j][i] << " ";
                        break;
                        
                };
            }

        }

        for (int j(0); j < 4*(256-microcode.size()); j++) {
            cout << "00000000 ";
        }
    }

    return 0;
}

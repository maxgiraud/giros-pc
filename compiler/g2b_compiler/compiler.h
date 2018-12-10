#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cmath>

#define _NOFILE_ -1

#define _NOP_           "00"
#define _LDA_           "01"
#define _LDB_           "02"
#define _LDO_           "03"
#define _STA_           "04"
#define _STB_           "05"
#define _STO_           "06"
#define _AWB_           "07"
#define _AWO_           "08"
#define _ALUWA_         "09"
#define _ALUWB_         "0a"
#define _ALUWO_         "0b"
#define _ADD_           "0c"
#define _ADDWA_         "0d"
#define _ADDWB_         "0e"
#define _ADDWO_         "0f"
#define _SUB_           "10"
#define _SUBWA_         "11"
#define _SUBWB_         "12"
#define _SUBWO_         "13"
#define _JMP_           "14"
#define _JC_            "15"
#define _JCN_           "16"
#define _JZ_            "17"
#define _JZN_           "18"
#define _JCZ_           "19"
#define _JCZN_          "1a"
#define _SCLR_          "1b"


class Compiler {

    private:
        bool _debug;
        int _error;

        std::string _filename;
		std::string _bin;

        int _wcount;
        int _icount;
        std::string _inst_adr;
        std::map< std::string, int> _vars;

    public:
        Compiler(char* filename);
        int Run();

        int V_Assign(std::string instruction, std::string operand);
        
        int I_JMP(std::string operand);
        int I_JC(std::string operand);
        int I_JCN(std::string operand);
        int I_JZ(std::string operand);
        int I_JZN(std::string operand);
        int I_JCZ(std::string operand);
        int I_JCZN(std::string operand);
        int I_LD(std::string operand);
        int I_MOV(std::string operand);
        int I_STR(std::string operand);
        int I_ADD(std::string operand);
        int I_SUB(std::string operand);

        std::string itoxs(int value, int span=4);
};

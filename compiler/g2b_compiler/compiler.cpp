#include "compiler.h"

using namespace std;


Compiler::Compiler(char* filename) {

    _error = 0;
    _filename = filename;
    _debug = false;
}

int Compiler::Run() {

	ifstream code(_filename.c_str());

	if (!code.is_open()) return _NOFILE_;

    // Map instructions adresses for labels and variables
    string instruction, operand;
    stringstream _wcount_hex;
    _wcount = 0;

    while (code >> instruction >> operand) {
        _icount++;

        if (operand[0]=='"' && (operand.size()==1 || operand[operand.size()-1]!='"')) {
            char c; code.get(c); operand+=c; while (operand[operand.size()-1]!='"') { code.get(c); operand+=c; }
        }

        if (instruction.find(":")!=string::npos && operand[0]=='"')   {
            if (operand[operand.size()-1]=='"') {
                _vars[instruction.substr(0,instruction.size()-1)] = operand.size()-2;
            }
        } else if (instruction.find(":")!=string::npos && operand[0]!='"') {
            _vars[instruction.substr(0,instruction.size()-1)] = 1;
        } else if (instruction == "jmp") {
            _vars[instruction.substr(0,instruction.size()-1)] = 1;
        }
	}

    code.close();
    code.open(_filename.c_str());

    // Transcript instructions
    _icount = 0;
    while (code >> instruction >> operand) {
        _icount++;

        if (operand[0]=='"' && (operand.size()==1 || operand[operand.size()-1]!='"')) {
            char c; code.get(c); operand+=c; while (operand[operand.size()-1]!='"') { code.get(c); operand+=c; }
        }

        if (instruction.find(":")!=string::npos)    { V_Assign(instruction,operand);   }
		else if (instruction == "ld")               { I_LD(operand);                   }
		else if (instruction == "mov")              { I_MOV(operand);                  }
		else if (instruction == "str")              { I_STR(operand);                  }
		else if (instruction == "add")              { I_ADD(operand);                  }
		else if (instruction == "sub")              { I_SUB(operand);                  }
		else if (instruction == "jmp")              { I_JMP(operand);                  }
		else if (instruction == "jc")               { I_JC(operand);                   }
		else if (instruction == "jcn")              { I_JCN(operand);                  }
		else if (instruction == "jz")               { I_JZ(operand);                   }
		else if (instruction == "jzn")              { I_JZN(operand);                  }
		else if (instruction == "jcz")              { I_JCZ(operand);                  }
		else if (instruction == "jczn")             { I_JCZN(operand);                 }
		else if (instruction == "sclr")             { _bin += _SCLR_;                  }
        else {
            cout << "command \"" << instruction << "\" not known\n";
        }
	}

    code.close();

    // Transcript instructions
    string bin_temp(_bin);
    bool rlabel(false);
    string label;
    bool rvalue(false);
    string value;
    bool found(false);
    double adr(0);
    string label_temp;
    int pos_value;

    for (int i(0); i < _bin.size(); i++) {

        if (_bin[i] == '$' && !rlabel) { rlabel = true; }

        else if (rlabel) {
            if (_bin[i] != '$') { label += _bin[i]; }
            else {
                for (int j(0); j < bin_temp.size() && !found; j++) {
                    if (bin_temp[j] == '#' && !rvalue) { rvalue = true; }
                    else if (rvalue) {
                        if (bin_temp[j] != '#') { value += bin_temp[j]; }
                        else {
                            if (value == label) { found = true; pos_value = j-value.size()-1; }
                            else { value = ""; }
                            rvalue = false;
                        }
                    } else if (bin_temp[j] == '$' && !rvalue) {
                        int k(j+1);
                        while (bin_temp[k]!='$' && k<bin_temp.size()) { k++; }
                        j=k;
                        adr+=2;
                    } else { adr += 0.5; }
                }


                if (_debug) { cerr << bin_temp << endl; }

                bin_temp.replace(bin_temp.find("$"+label+"$"), label.size()+2, itoxs((int)adr));

                adr = 0;
                label = "";
                value = "";
                rlabel = false;
                found = false;
            }
        }
    }

    for (int j(bin_temp.size()-1); j >= 0; j--) {
        if (bin_temp[j] == '#' && !rvalue) { rvalue = true; }
        else if (rvalue) {
            if (bin_temp[j] != '#') { value += bin_temp[j]; }
            else {
                    pos_value = j;
                    bin_temp.erase(pos_value, value.size()+2);
                    value = "";
                    rvalue = false;
            }
        } else { adr += 0.5; }
    }

    _bin = bin_temp;

    if (_error) {
        cerr << "Fatal error : compiler returned " << _error << endl;
        return _error;
    } else {
   
        cerr << (int)_bin.size()/2 << " octets" << endl;

        // format to logisim
        for (int i(_bin.size()-2); i > 0; i-=2) {
            _bin.insert(i,1,' ');
        }

        cerr << _bin << endl;
	cout << "v2.0 raw" << endl;
        cout << _bin << endl;
    }

    return 0;
}

string Compiler::itoxs(int value, int span) {

    stringstream ss;
    string out;
    ss << std::hex << value;
    out = ss.str();
    if (out.size() < span) {
        out.insert(out.begin(),span-out.size(),'0');
    }
    return out;
}

int Compiler::V_Assign(string instruction, string operand) {

    string label = instruction;
    label.pop_back();

    if (operand[0] == '"' && operand[operand.size()-1] == '"') {
        string value = operand.substr(1,operand.size()-2);
        stringstream ss_temp;
        string s_temp;

        if (value.size()>=2 && (value[0]!='\\' || value.size()>=3)) {
            for (int i(0); i < value.size(); i++) {
                _bin += "#"+label+"_"+to_string(i)+"#";
                if (value[i] == '\\' && value[i+1]=='n') {
                    s_temp = "0a";
                    i++;
                } else {
                    ss_temp << std::hex << (int)value[i];
                    s_temp = ss_temp.str();
                    ss_temp.str("");
                }
                _bin += s_temp;
            }
        } else {
            _bin += "#"+label+"#";
            if (value.size()==2 && value[0] == '\\' && value[1]=='n') {
                s_temp = "0a";
            } else {
                ss_temp << std::hex << (int)value[0];
                s_temp = ss_temp.str();
                ss_temp.str("");
            }
            _bin += s_temp;
        }
    } else if (operand == "@") {
        _bin += "#"+label+"#";

    } else {
        _bin += "#"+label+"#";
        _bin += operand;
    }
    return 0;
}


int Compiler::I_ADD(string operand)     {

    if      (operand == "ra") { _bin += _ADDWA_; }
    else if (operand == "rb") { _bin += _ADDWB_; }
    else if (operand == "ro") { _bin += _ADDWO_; }
    
    return 0;
}

int Compiler::I_SUB(string operand)     {

    if      (operand == "ra") { _bin += _SUBWA_; }
    else if (operand == "rb") { _bin += _SUBWB_; }
    else if (operand == "ro") { _bin += _SUBWO_; }
    
    return 0;
}

int Compiler::I_JMP(string operand)     { _bin += _JMP_;  _bin += operand+"$"; return 0; }

int Compiler::I_JC(string operand)      { _bin += _JC_;   _bin += operand+"$"; return 0; }

int Compiler::I_JCN(string operand)     { _bin += _JCN_;  _bin += operand+"$"; return 0; }

int Compiler::I_JZ(string operand)      { _bin += _JZ_;   _bin += operand+"$"; return 0; }

int Compiler::I_JZN(string operand)     { _bin += _JZN_;  _bin += operand+"$"; return 0; }

int Compiler::I_JCZ(string operand)     { _bin += _JCZ_;  _bin += operand+"$"; return 0; }

int Compiler::I_JCZN(string operand)    { _bin += _JCZN_; _bin += operand+"$"; return 0; }

int Compiler::I_LD(string operand) {

	string reg(operand.substr(0,operand.find(",")));
	string adr(operand.substr(operand.find(",")+1));
    int array_size(_vars[adr.substr(1,adr.size()-1)]);

	if (reg == "ra") {
		_bin += _LDA_;
		_bin += adr+"$";

	} else if (reg == "rb") {
		_bin += _LDB_;
		_bin += adr+"$";

	} else if (reg == "ro") {
        if (array_size > 1) {
            for (int i(0); i < array_size; i++) {
                _bin += _LDO_;
		        _bin += adr+"_"+to_string(i)+"$";
            }
        } else {
            _bin += _LDO_;
		    _bin += adr+"$";
        }

    } else {
        cerr << "Error in \"ld " << operand << "\" (" << _icount <<") : register \"" << reg << "\" does not exist." << endl;
        _error = -1;
    }

	return 0;
}

int Compiler::I_MOV(string operand) {

	string rego(operand.substr(0,operand.find(",")));
	string regi(operand.substr(operand.find(",")+1));

	if (rego == "ra") {
        if (regi == "rb") { _bin += _AWB_; }
        if (regi == "ro") { _bin += _AWO_; }
        
    } else if (rego == "ralu") {
        if (regi == "ra") { _bin += _ALUWA_; }
        if (regi == "rb") { _bin += _ALUWB_; }
        if (regi == "ro") { _bin += _ALUWO_; }

    } else {
        cerr << "Error in \"mov " << operand << "\" (" << _icount <<") : register \"" << rego << "\" does not exist." << endl;
        _error = -1;
    }

	return 0;
}

int Compiler::I_STR(string operand) {

	string reg(operand.substr(0,operand.find(",")));
	string adr(operand.substr(operand.find(",")+1));

	if (reg == "ra") {
		_bin += _STA_;
		_bin += adr+"$";

	} else if (reg == "rb") {
		_bin += _STB_;
		_bin += adr+"$";

	} else if (reg == "ro") {
        _bin += _STO_;
		_bin += adr+"$";

    } else {
        cerr << "Error in \"ld " << operand << "\" (" << _icount <<") : register \"" << reg << "\" does not exist." << endl;
        _error = -1;
    }

    _wcount += 3;

	return 0;
}



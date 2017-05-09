#include<iostream>
#include<stdlib.h>
#include<vector>
#include<bitset>
#include<map>
using namespace std;

string to_low(string &a)
{
  string ret = a;
  for(int i = 0;i < ret.size();i++)
  {
    if(ret[i] >= 'A' and ret[i] <= 'Z')
    {
      ret[i] = ret[i] - 'A' + 'a';
    }
  }
  return ret;
}

class Swombat{
  private:

    map<string,int> index_of_registers;//cada registrador tem um indice correspondente (uso geral de 0 a 7)
    vector<int> memory;//conteudo da memoria
    vector<bool> free_memory;//posicoes livres da memoria
    int mem_size;//tamanho da memoria
    vector<int> stack;//pilha
    vector<int> content_of_registers;//conteudo dos registradores
    map<string,int> data_to_pos;
    map<string,int> label_to_pos;

  public:

    void generate_indexes()
    {
      for(int i = 0;i <= 7;i++)
      {
        string tmp = "R";
        tmp.push_back('0' + i);
        index_of_registers[tmp] = index_of_registers[to_low(tmp)] = i;
      }
    }

    void get_started()
    {
      mem_size = 256;
      generate_indexes();
      memory.resize(mem_size,0);
      stack.resize(127,0);
      content_of_registers.resize(8,0);
      free_memory.resize(mem_size,1);
    }
    
    int get_reg_index(string &s)
    {
      return index_of_registers[s];
    }

    int get_addr_from_data(string &s)
    {
      return data_to_pos[s];
    }

    int get_addr_from_label(string &s)
    {
      return label_to_pos[s];
    }

    void store_instruction(string &label, int graphic)
    {
      if(!label.empty())
      {
          
      }
    }

    void allocate(string label, int num_bytes, int value)
    {
      
    }
};

bool is_label(string &label){ return (label[0] == '_');}

void read_comments()
{
  string tmp;
  getline(cin,tmp);
  cerr<<"removendo comentario : "<<tmp<<endl;
}

bool numerical(string &s)
{ 
  for(int i = 0;i < s.size();i++)
  {
    if(s[i] < '0' or s[i] > '9') return false; 
  }
  return true;
}

int string_to_int(string &s)
{
  int ret = 0;
  for(int i = 0;i < s.size();i++)
  {
    ret *= 10;
    ret += s[i] - '0';
  }
  return ret;
}

void assemble(Swombat &OurMachine, string &label, string &instr)
{
  int graphic,op;
  if(instr == "exit") graphic = 0;
  else if(instr == "loadi" or instr == "storei" or instr == "jmpz" or instr == "jmpn")
  {
    string tmp,reg;
    int addr;
    op = 1;

    if(instr == "storei") op = 2;
    else if(instr == "jmpz") op = 7;
    else if(instr == "jmpn") op = 8;

    cin>>reg;
    cin>>tmp;

    if(numerical(tmp)) addr = string_to_int(tmp);
    else addr = OurMachine.get_addr_from_data(tmp);

    graphic = op<<11 + OurMachine.get_reg_index(reg)<<8 + addr;
  }
  else if(instr == "add" or instr == "subtract" or instr == "multiply" or instr == "divide" or instr == "move" or instr == "load" or instr == "store" or instr == "negate")
  {
    string reg1,reg2;
    op = 3;
    if(instr == "subtract") op = 4;
    else if(instr == "multiply") op = 5;
    else if(instr == "divide") op = 6;
    else if(instr == "move") op = 10;
    else if(instr == "load") op = 11;
    else if(instr == "store") op = 12;
    else if(instr == "negate") op = 15;

    cin>>reg1>>reg2;

    graphic = op<<11 + OurMachine.get_reg_index(reg1)<<8 + OurMachine.get_reg_index(reg2)<<5;
  }
  else if(instr == "jump")
  {
    string tmp;
    int addr;
    op = 7;

    cin>>tmp;

    if(numerical(tmp)) addr = string_to_int(tmp);
    else addr = OurMachine.get_addr_from_data(tmp);

    graphic = op<<11 + addr;
  }
  else if(instr == "loadc" or instr == "addi")
  {
    int constant_value;
    string reg;
    op = 13;
    if(instr == "addi") op = 18;

    cin>>reg;
    cin>>constant_value;

    graphic = op<<11 + OurMachine.get_reg_index(reg)<<8 + constant_value;

  }
  else if(instr == "clear" or instr == "push" or instr == "pop")
  {
    string reg;
    op = 14;
    if(instr == "push") op = 16;
    else if(instr == "pop") op = 17;
    
    cin>>reg;

    graphic = op<<11 + OurMachine.get_reg_index(reg)<<8;
  }
  else if(instr == "call")
  {
    string label;
    op = 19;

    cin>>label;
    
    graphic = op<<11 + OurMachine.get_addr_from_label(label);
  }
  else if(instr == "return")
  {
    op = 20;
    graphic = op<<11;
  }
  else if(instr == ".data")
  {
    int num_bytes,value;
    cin>>num_bytes>>value;
    OurMachine.allocate(label,num_bytes,value);
    return;
  }
  else cerr<<instr<<" nao eh uma instrucao valida.\n";
  read_comments();
  OurMachine.store_instruction(label,graphic);
  
}

bool read_instruction(Swombat &OurMachine)
{
  string label,instr;
  cin>>label;
  if(cin.eof()) return false;
  if(is_label(label))
  {
    label = label.substr(1,label.size() - 2);//trata o label
    cin>>instr;
  }
  else
  {
    instr = label;//se nao houver label, a primeira palavra eh instrucao
    label.clear();
  }
  assemble(OurMachine,label,instr);
  return true;
}

int main()
{
  Swombat OurMachine;
  OurMachine.get_started();

  while(read_instruction(OurMachine));//le as instrucoes enquanto houver

  return 0;
}

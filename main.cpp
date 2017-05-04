#include<iostream>
#include<stdlib.h>
#include<vector>
#include<bitset>
#include<map>
using namespace std;

class Swombat{
  private:

    map<string,int> index_of_registers;//cada registrador tem um indice correspondente (uso geral de 0 a 7)
    vector<int> memory;//conteudo da memoria
    vector<bool> free_memory;//posicoes livres da memoria
    int mem_size;//tamanho da memoria
    vector<int> stack;//pilha
    vector<int> content_of_registers;//conteudo dos registradores

  public:

    void generate_indexes()
    {
      for(int i=0;i<=7;i++)
      {
        string tmp="R";
        tmp.push_back('0'+i);
        index_of_registers[tmp]=i;
      }
      index_of_registers["stackpt"]=8;
      index_of_registers["sdr"]=9;
      index_of_registers["pc"]=10;
      index_of_registers["buffer1"]=11;
      index_of_registers["buffer2"]=12;
      index_of_registers["ir"]=13;
      index_of_registers["mar"]=14;
      index_of_registers["mdr"]=15;
      index_of_registers["status"]=16;
    }
    void get_started()
    {
      mem_size=256;
      generate_indexes();
      memory.resize(mem_size,0);
      stack.resize(127,0);
      content_of_registers.resize(8,0);
      free_memory.resize(mem_size,1);
    }
};

bool is_label(string &label){ return (label[0]=='_');}

void assemble(Swombat &OurMachine, string &label, string &instr)
{
  if(instr=="exit")
  {

  }
  else if(instr=="loadi")
  {

  }
  else if(instr=="storei")
  {

  }
  else if(instr=="add")
  {
  }
  else if(instr=="subtract")
  {

  }
  else if(instr=="multiply")
  {

  }
  else if(instr=="divide")
  {

  }
  else if(instr=="jump")
  {

  }
  else if(instr=="jmpz")
  {

  }
  else if(instr=="jmpn")
  {

  }
  else if(instr=="move")
  {

  }
  else if(instr=="load")
  {

  }
  else if(instr=="store")
  {

  }
  else if(instr=="loade")
  {

  }
  else if(instr=="clear")
  {

  }
  else if(instr=="negate")
  {

  }
  else if(instr=="push")
  {

  }
  else if(instr=="pop")
  {

  }
  else if(instr=="addi")
  {

  }
  else if(instr=="call")
  {

  }
  else if(instr=="return")
  {

  }
}

bool read_instruction(Swombat &OurMachine)
{
  string label,instr;
  cin>>label;
  if(cin.eof()) return false;
  if(is_label(label))
  {
    label=label.substr(1,label.size()-2);//trata o label
    cin>>instr;
  }
  else
  {
    instr=label;//se nao houver label, a primeira palavra eh instrucao
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

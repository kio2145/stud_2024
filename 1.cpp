#include <iostream>
// тест системи контролю версій
// коментар 3
cout<<"Крута нова функція!";
import re
import tabulate

class Lexer:
    def __init__(self):
        self.tags=['body','p','img','a', 'h1','h2','table','tr','td']
        self.attribute=['align','width','img','border', 'src','alt']
        self.ids=r'[0-9A-Za-z_]+'
    def is_equel_symb(self,inpt_str):
        return inpt_str=='='
    def is_open_angle_braket(self,inpt_str):
        return inpt_str=='<'
    def is_close_angle_braket(self,inpt_str):
        return inpt_str=='>'
    def is_tag(self,inpt_str):
        return inpt_str.lower() in self.tags
    def is_attribute(self,inpt_str):
        return inpt_str in self.attribute
    def is_quotes(self,inpt_str):
        return inpt_str=="\'" or inpt_str=="\""
    def is_val_name(self,inpt_str):
        return re.fullmatch(self.ids,inpt_str) is not None and not (self.is_tag(inpt_str) or self.is_attribute(inpt_str))
class Parser:
    def __init__(self):
        self.lx=Lexer()
        self.lex_arrey=[]
        self.separete=[' ', '\"', '\'','<','>','=']
        self.inpt_str=''
        self.Error=''
    def set_inpt_str(self,inpt_str):
        self.inpt_str=inpt_str
    def get_print_step(self,last_step, curr_len):
        if last_step==0:
            return 0
        else:
            return (last_step+1)-curr_len
    def process_lex(self):
        TmpStr=''
        for step,str in enumerate(self.inpt_str):
            if str!=' ' and str not in self.separete:
                TmpStr+=str
            if str in self.separete or TmpStr in self.separete or step==len(self.inpt_str)-1:
                text_pos=step-1
                if self.lx.is_tag(TmpStr):
                    #self.add_lex_to_array('Tag',TmpStr,self.get_print_step(text_pos,len(TmpStr)),len(TmpStr))
                    self.add_lex_to_array(TmpStr.upper(),TmpStr,self.get_print_step(text_pos,len(TmpStr)),len(TmpStr))
                if self.lx.is_attribute(TmpStr):
                    #self.add_lex_to_array('Attribute',TmpStr,self.get_print_step(text_pos,len(TmpStr)),len(TmpStr))
                    self.add_lex_to_array(TmpStr.upper(),TmpStr,self.get_print_step(text_pos,len(TmpStr)),len(TmpStr)) 
                if self.lx.is_val_name(TmpStr):
                    self.add_lex_to_array('Value',TmpStr,self.get_print_step(text_pos,len(TmpStr)),len(TmpStr))
            if str in self.separete:
                if self.lx.is_equel_symb(str):
                    self.add_lex_to_array('Equel',str,self.get_print_step(step,len(str)),len(str))
                if self.lx.is_open_angle_braket(str):
                    self.add_lex_to_array('Open angle bracket',str,self.get_print_step(step,len(str)),len(str))
                if self.lx.is_close_angle_braket(str):
                    self.add_lex_to_array('Close angle bracket',str,self.get_print_step(step,len(str)),len(str))
                if self.lx.is_quotes(str):
                    self.add_lex_to_array('Quotes',str,self.get_print_step(step,len(str)),len(str))
                TmpStr=''
    def add_lex_to_array(self,type,text,start_pos,len_str):
        self.lex_arrey.append([])
        self.lex_arrey[-1].append(type)
        self.lex_arrey[-1].append(text)
        self.lex_arrey[-1].append(start_pos)
        self.lex_arrey[-1].append(len_str)
    def print_lex(self):
        print_list=self.lex_arrey.insert(0,["Type","Lexema","Position","length"])
        print_list=self.lex_arrey.insert(1,["----","-----","--------","--------"])
        results = tabulate.tabulate(self.lex_arrey)
        print(results)
        #print(self.lex_arrey)
if __name__ == "__main__":
   print("достпуні теги",['body','p','img','a', 'h1','h2','table','tr','td'])
   print("доступні атрибути", ['align','width','img','border', 'src','alt'])
   print("Приклад тегу з атрибутом", "<p align=\"left\">" )
   while True:
        Pr=Parser()
        inpt=input("Введіть тег: ")
        Pr.set_inpt_str(inpt)
        Pr.process_lex()
        Pr.print_lex()
  

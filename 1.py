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
   

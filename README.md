# simple_scanner
參考crafting a compiler with c 所實作的簡易scanner
主要功能為將一串字串切分成token，並且標示其為何種token
支援的語言結構如下

--------------------------------------------------
identifier命名規則:
1. 必須為英文字母開頭
2. 允許有數字和底線
3. 最長32個字元

* := assign operator
* '+'  plus operator
* '-'  minus operator
* -- comment opertor 在此符號後皆為comment應忽略不算在token
* begin,end,write,read 為保留字


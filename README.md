# OS  

os-simple-shell

操作說明:  
1. 把檔案(my_shell.c child.c 以及同名執行檔)放入linux環境  
2. 終端機進入到放檔案位置  
3. 終端機輸入  ./my_shell 執行程式  
4. 終端機畫面1092929_my_shell>  
  
功能:  
1. chid持續輸出，直到指令中斷   
2. 指令q中斷child程式   
3. 輸入 child & 之時 parent 不會等 child 結束  
   
增加的功能:  
1. 有部分指令可以直接在終端機使用(ex.ls'clear'exit'ps axe)   

os-share memory

1. 編譯 p1 輸入 gcc p1.c -o p1
2. 編譯 p2 輸入 gcc p2.c -o p2
3. 先執行有|IPC_CREAT 的 p2 輸入 ./p2 
4. 再執行p1 輸入 ./p1
5. 再 p1 視窗輸入兩數字(中間加入空格)
6. 在 p2 會接收並計算
7. 完成後會放在 share memory 而 p1 會將內容輸出
8. 在 p1 視窗中輸入 quit 會跳出程式 

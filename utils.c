
/************************************************************************
函数名：Delay
功能  ：Delay延时约1ms
参数  ：无
返回值：无
注意  ：
************************************************************************/
void Delay(int times){
    int i=0;
    
    for(;times>0;times--)
      	for(i=0;i<10000;i++);
}

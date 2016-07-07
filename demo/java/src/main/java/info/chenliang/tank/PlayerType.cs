namespace info.chenliang.tank{
public class PlayerType{
public const int PT_AI=0;
public const int PT_HUMAN=1;
public const int MAX_VALUE=2;
public static string ToString(byte value){
if(value == PT_AI){
return "PT_AI";
}
if(value == PT_HUMAN){
return "PT_HUMAN";
}
return null;
}
public static int ToValue(string name){
if(name == "PT_AI")){
return PT_AI;
}
if(name == "PT_HUMAN")){
return PT_HUMAN;
}
return -1;
}
}
}

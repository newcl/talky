package info.chenliang.tank;
public class PlayerType{
public final static int PT_AI=0;
public final static int PT_HUMAN=1;
public final static int MAX_VALUE=2;
public static String toString(byte value){
if(value == PT_AI){
return "PT_AI";
}
if(value == PT_HUMAN){
return "PT_HUMAN";
}
return null;
}
public static int toValue(String name){
if(name.equals("PT_AI")){
return PT_AI;
}
if(name.equals("PT_HUMAN")){
return PT_HUMAN;
}
return -1;
}
}

int main(){
    int x = 3;
    for(int i=0; i<10; i++){
    	if(i == 2){
    		continue;
    	}
        x = x + 1;
    }
    return x;
}


int x = 5;
int y;

int positive( int x){
	if (0<x){
		return 1;
	}
	else{
		return 0;
	}
}


void main() {
    y = !positive(x);
}

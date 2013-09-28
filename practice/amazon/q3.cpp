public:
	Stream():index(0){};
	char getNext() {
		return s[index++];
	}
	bool hasNext() {
		if (s[index] != '\0') return true;
		return false;
	}
};

char firstChar ( Stream &input ) {

	long count[256];
	unsigned long first[256];
	for(int i = 0 ; i < 256; i++){
		count[i] = 0; //Never occurred
		first[i] = 0; //If occurred, when
	}

	for(unsigned long l = 0; input.hasNext(); l++){
		char c = input.getNext();
		count[c]++;
		if(count[c] == 1){
			first[c] = l;
		}
	}

	char firstOccurred = '#';
	unsigned long f1 = -1;
	for(int i = 0 ; i < 256; i++){
		if (count[i] == 1) {
			if (first[i] < f1) {
				f1 = first[i];
				firstOccurred = (char)i;
			}
		}
	}
	return firstOccurred;
}

int main( int argc, char ** argv ) {
	Stream s1;

	printf("first = %c\n", firstChar(s1));
//	cout << "working.cpp" << endl;
	return 0;
}

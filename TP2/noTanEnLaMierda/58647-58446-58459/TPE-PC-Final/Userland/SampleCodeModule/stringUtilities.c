

int strlen(char* str){
	int i=0;
	while(str[i]!= '\0'){
		i++;
	}
	return i;
}

int strcmp(char* str1, char* str2){
	int i =0;
	while(str1[i]==str2[i]){
		if(str1[i]=='\0'&&str2[i]!='\0'){
			return 0;
		}
		else if(str1[i]!='\0'&&str2[i]=='\0'){
			return 0;
		}
		else if(str1[i]=='\0'&&str2[i]=='\0'){
			return 1;
		}
		i++;
	}
	return 0;
}


int uintToBase(int value, char * buffer, int base)
{
	char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	//Calculate characters for each digit
	do
	{
		int remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


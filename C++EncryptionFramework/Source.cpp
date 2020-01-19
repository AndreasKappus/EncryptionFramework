#include<iostream>
#include<fstream>

using namespace std;

class Encryption
{
protected:
	ifstream input_file;
	ofstream output_file;
public:
	Encryption(char* input_name, char* output_name);
	~Encryption();

	virtual char transform(char ch) = 0;
	void encrypt();
};

Encryption::Encryption(char* input_name, char* output_name)
{
	input_file.open(input_name);
	output_file.open(output_name);
	if (!input_file) {
		cout << "input file can't be opened";
		exit(1);
	}
	if (!output_file) {
		cout << "Output file can't be opened";
		exit(1);
	}
}

Encryption::~Encryption()
{
	input_file.close();
	output_file.close();
}

void Encryption::encrypt()
{
	char ch;
	char transform_ch;
	input_file.get(ch);

	while (!input_file.fail()) {
		transform_ch = transform(ch);
		output_file.put(transform_ch);
		input_file.get(ch);
	}


}

class SimpleEncryption : public Encryption
{
public:
	char transform(char ch)
	{
		return ch + 1;
	}

	SimpleEncryption(char* inFileName, char* outFileName) : Encryption(inFileName, outFileName) { }
	
};

int main()
{
	char input_name[80], output_name[80];
	cout << "Enter name of file to encrypt: ";
	cin >> input_name;
	cout << "Enter name of file to receive encrypted text: ";
	cin >> output_name;
	SimpleEncryption obfuscate(input_name, output_name);
	obfuscate.encrypt();
	return 0;
}
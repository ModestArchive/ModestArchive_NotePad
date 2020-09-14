//File.cpp

#include"File.h"



File::File() {

	this->notePadForm = 0;

}

File::File(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;

}

File::~File() {


}

//¸Þ¼Òµå

string File::Load(char(*fileName)) {
	
	ifstream in(fileName);
	string rowBuffer="";
	string notePadBuffer = "";
	

	while (!in.eof()) {
		getline(in, rowBuffer,'\0');
		notePadBuffer += rowBuffer;
	}
	
	in.close();

	return notePadBuffer;

}


void File::Save(char(*fileName), string contents) {

	ofstream out(fileName);
	
	
	if(out.is_open()){
		
		out << contents;
	}
	
	out.close();
}

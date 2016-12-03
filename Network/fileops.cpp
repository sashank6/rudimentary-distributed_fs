#include"fileops.h"
#include "types.h"
#include "globals.h"
#include "errors.h"

//Creates a file in data directory
void create_file(FileData filedata) {
	STRING filename = filedata.filename();
	STRING data = filedata.data();
	filename = CLIENT_DATA_PATH + filename;

	FILE *fp = fopen(filename.c_str(),"w");
	if(fp==NULL)
		handle_error("File creation error");
	fprintf(fp,"%s",data.c_str());
	fclose(fp);
}

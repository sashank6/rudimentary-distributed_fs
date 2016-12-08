#include"fileops.h"
#include "types.h"
#include "globals.h"
#include "errors.h"
#include "../Apps/localfileops.h"
#include "Packet.pb.h"
#include "packet.h"
#include "connections.h"
#include <sys/types.h>
#include <dirent.h>
#include<iostream>

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

std::string read_file(std::string filename){
	filename = CLIENT_DATA_PATH + filename;
	std::string data=readFile(filename);
	return data;
}
void send_file(std::string filename,std::string data){
	Packet packet;
	FileData *filedata(new FileData);
	filedata->set_filename(filename);
	filedata->set_data(data);
	packet.set_flag(CLIENT_FILE);
	packet.set_allocated_filedata(filedata);
	send_message("192.168.1.115",34343,packet);
}

Packet getFileList(){
	std::vector<std::string> v;
	DIR *dp;
	  struct dirent *ep;
	  dp = opendir ("../filedata");

	  if (dp != NULL)
	  {
	    while (ep = readdir (dp)){
	    	std::string filename=std::string(ep->d_name);
	    	if(filename[0]!='.')
	      v.push_back(filename);
	    }

	    (void) closedir (dp);
	  }
	  else
	    perror ("Couldn't open the directory");

	  FileList *files(new FileList);
	  for(int i=0;i<v.size();i++){
		  std::cout<<v[i]<<std::endl;
		  files->add_filename(v[i]);
	  }
	  Packet packet;
	  packet.set_flag(UPDATE_FILE_LIST);
	  packet.set_allocated_filelist(files);
	  return packet;

}
std::set<std::string> getLocalFileList(){
	std::set<std::string> s;
		DIR *dp;
		  struct dirent *ep;
		  dp = opendir ("../filedata");

		  if (dp != NULL)
		  {
		    while (ep = readdir (dp)){
		    	std::string filename=std::string(ep->d_name);
		    	if(filename[0]!='.')
		      s.insert(filename);
		    }

		    (void) closedir (dp);
		  }
		  else
		    perror ("Couldn't open the directory");

		  return s;
}


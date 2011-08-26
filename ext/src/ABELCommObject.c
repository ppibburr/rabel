/* Wrap allen bradley ethernet library (abel)
 * as a 'object' that can attach to and read data from a SLC5/05 logic controller
 * in a manner that provides OOP idioms suited to wrap with foriegn function interface (FFI)
 * targeting the language Ruby.
 * 
 * Matt Mesanko 07282011, tulnor@linuxwaves.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "./libabplc5.h"
#include "./ABELCommObject.h"

ABELCommObject*
abel_comm_object_new(char *host)
{
    static ABELCommObject obj;
    memset(&obj, 0, sizeof(obj));
    abel_comm_object_set_host(&obj,host);
    return &obj;
}

void
abel_comm_object_set_host(ABELCommObject* obj, char* host)
{
    strcpy(obj->host, host);
}

short abel_comm_object_get_error(ABELCommObject* obj) {
	short err;
	err = obj->comm1.error;
	return err;
}

char* abel_comm_object_get_host(ABELCommObject* obj)
{
	return obj->host;
}

short abel_comm_object_get_tns(ABELCommObject* obj)
{
	return obj->comm1.tns;
}

long abel_comm_object_get_commid(ABELCommObject* obj)
{
	return obj->comm1.commid;	
}

byte abel_comm_object_get_mode(ABELCommObject* obj)
{
	return obj->comm1.mode;	
}

short abel_comm_object_get_handle(ABELCommObject* obj)
{
	return obj->comm1.handle;
}

// connects to logic controller
// TODO: assert member host !NULL 
void abel_comm_object_attach(ABELCommObject* obj) {
  struct _comm	comm1;
  comm1 = attach(abel_comm_object_get_host(obj),1);
  obj->comm1 = comm1;
}

// disconnects from the controller
// TODO assert connected
void abel_comm_object_close(ABELCommObject* obj) {
  short handle;
  handle = abel_comm_object_get_handle(obj);	
  close(handle);
}

// returns the type of controller (1 PLC5, 2 PLC5250, 3 SLC5, 4 MICRO)
int abel_comm_object_get_device_type(ABELCommObject* obj)
{
  struct plc5stat status;
  status = getstatus(obj->comm1,FALSE);
  if (status.type == 0xee)
	return 3;
  if (status.type == 0xeb)
	return 1;
  if (status.type == 0xde)
	return 2;
}

// reads register(s) from controller at address to len
// abel_comm_object_read(obj,"n7:90",4)
// will return a ABELDataReturn 
//   with type 0, len 4
//   with num of values at n7:90,n7:91,n7:92,n7:93
ABELDataReturn* abel_comm_object_read(ABELCommObject* obj,char* addr,int len)
{
    ABELDataReturn* out;
    out = abel_data_return_new();
	int type;
	type = abel_comm_object_get_device_type(obj);
	int x,sts,extsts;
	unsigned int temp1, temp2;
	struct _data data;
    out->len=len;
    obj->comm1.tns = obj->comm1.tns + 4;
	data=protread3(obj->comm1,addr,len,type,FALSE);
    if (data.len == -1)
		{
		sts = data.data[0];
		extsts = data.data[1];
		printf ("An error occured.  The PLC STS byte is %d, the EXT STS byte is %d\n",sts,extsts);
		if (sts != 0xf0)
			printf ("Primary Error code is %s\n",errors[(sts/16)]);
		if (extsts != 0)
			printf ("Extended error code is %s\n",ext_errors[extsts]);
		close (obj->comm1.handle);
		}
	switch (data.name.section)
		{
		case 0:
			if (data.name.floatdata == TRUE)
				{
				out->type=1;
				for (x=0;x<data.len;x=x+2)
					{
					temp1 = (data.data[x]);
					temp2 = (data.data[x+1]);
					out->flt[x]=itof(temp1,temp2);
					}
				}
			if (data.name.floatdata == FALSE)
				{
				out->type=0;
				for (x=0;x<(data.len);x++)
					out->num[x]=(int)data.data[x];
				}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		    for (x=0;x<data.len;x++)
				printf ("%02X  ",(byte)data.data[x]);
			printf ("\n");
		}	
  return out;
}

// make a new data rerturn value
// reads from proccessor are stored here
ABELDataReturn* abel_data_return_new()
{
	static ABELDataReturn rv;
	memset(&rv,0,sizeof(rv));
	return &rv;
}

// returns an integer at position x
// in the num member of an ABELDataReturn
int abel_data_return_integer_at(ABELDataReturn* rv,int x) {
	     return rv->num[x];
}

// returns an float at position x
// in the flt member of an ABELDataReturn
float abel_data_return_float_at(ABELDataReturn* rv,int x) {
	     return rv->flt[x];
}

int abel_data_return_is_float(ABELDataReturn* rv)
{
	return rv->type == 1;
}

int abel_data_return_is_integer(ABELDataReturn* rv)
{
	return rv->type == 0;
}

int abel_data_return_get_type(ABELDataReturn* rv)
{
	return rv->type;
}

int abel_data_return_get_length(ABELDataReturn* rv)
{
	return rv->len;
}

int main() {
  ABELCommObject* obj;
  obj = abel_comm_object_new("192.1.168.20");	
  printf("""ABELCommObject's host is %s\n""",abel_comm_object_get_host(obj));
  abel_comm_object_attach(obj);

  short err;
  err = abel_comm_object_get_error(obj);
  printf("""the comm objects error is %d\n""",err);
  
  short tns;
  tns = abel_comm_object_get_tns(obj);
  printf("""the comm objects tns is %d\n""",tns);
  
  long commid;
  commid = abel_comm_object_get_commid(obj);
  printf("""the comm objects commid is %ld\n""",commid);
  
  int type;
  type = abel_comm_object_get_device_type(obj);
  
  printf("""The device is of type %d (1 = PLC5, 2 = PLC5250, 3 = SLC5)\n""",type);
  
  ABELDataReturn* rv;
  rv = abel_comm_object_read(obj,"n7:90",2);
  printf("""%d read\n""",abel_data_return_integer_at(rv,1));
  abel_comm_object_close(obj);
  exit(0);
}


/* Wrap allen bradley ethernet library (abel)
 * as a 'object' that can attach to and read data from a SLC5/05 logic controller
 * in a manner that provides OOP idioms suited to wrap with foriegn function interface (FFI)
 * targeting the language Ruby.
 * 
 * Matt Mesanko 07282011, tulnor@linuxwaves.com
 */

/* ABELDataReturn */

// used to store the return and information about the return from
// abel_comm_object_read();
// type if 0 is holding a int
//      if 1 is holding a float
// len  amount of data types stored
// num  where integers are stored
// flt  where floats are stored
typedef struct {
	int type;
	int len;
	int num[10];
	float flt[1];
} ABELDataReturn;

/* ABELCommObject */

// primary object when using library
// abel_comm_object_new(char *host)
typedef struct {
    struct _comm comm1;
    char host[32];
} ABELCommObject;


/*
 * DataReturn functions 
 */

ABELDataReturn*
abel_comm_object_read(ABELCommObject* obj, char* address, int len);

ABELDataReturn*
abel_data_return_new();

int 
abel_data_return_integer_at(ABELDataReturn* rv,int x);

float
abel_data_return_float_at(ABELDataReturn* rv,int x);

int
abel_data_return_is_float(ABELDataReturn* rv);

int
abel_data_return_is_integer(ABELDataReturn* rv);

int
abel_data_return_get_length(ABELDataReturn* rv);

int
abel_data_return_get_type(ABELDataReturn* rv);


/*
 * CommObject functions 
 */

ABELCommObject*
abel_comm_object_new(char *host);

void
abel_comm_object_set_host(ABELCommObject* obj, char* host);


short
abel_comm_object_get_error(ABELCommObject* obj);

char*
abel_comm_object_get_host(ABELCommObject* obj);

void
abel_comm_object_attach(ABELCommObject* obj);

short
abel_comm_object_get_tns(ABELCommObject* obj);

long 
abel_comm_object_get_commid(ABELCommObject* obj);

byte
abel_comm_object_get_mode(ABELCommObject* obj);

short 
abel_comm_object_get_handle(ABELCommObject* obj);

void 
abel_comm_object_close(ABELCommObject* obj);

int 
abel_comm_object_get_device_type(ABELCommObject* obj);



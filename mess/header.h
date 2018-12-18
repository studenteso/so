#define CTOB 1
#define BTOS1 2
#define BTOS2 3
#define BTOS3 4
#define STOB 5
#define BTOC 6

#define NUM_MSG 15
#define NUM_CLIENT 8

#define FTOK_PATH_CLIENT_OP "."
#define FTOK_PATH_SERVER_RIS "."

#define FTOK_CHAR_CLIENT_OP 'C'
#define FTOK_CHAR_SERVER_RIS 'S'

struct MSGClient{
	long process;
	int operation;
};

struct MSGServer{
	long process;
	int operation;
	
};



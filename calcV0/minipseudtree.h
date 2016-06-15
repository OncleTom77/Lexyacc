#ifndef MINIPSEUDTREE
# define MINIPSEUDTREE
    
enum NodeType {
	NTEMPTY 	= 0,
	NTINSTLIST 	= 1,
	NTINST 		= 2,
	
	NTSI 		= 10,
	NTALORS		= 11,
	NTSINON		= 12,

	NTTANTQUE	= 20,

	NTNUM   	= 201,
    NTVAR 		= 202,
	

	NTPLUS  	= 321,
	NTMIN   	= 322,
	NTMULT  	= 323,
	NTDIV   	= 324,
	NTPOW   	= 325,
    NTPARG 		= 326,
    NTPARD 		= 327,

    NTEGAL 		= 328,

    NTCOMPEGAL	= 350,
    NTCOMPDIFF	= 351,
    NTCOMPINF	= 352,
    NTCOMPSUP	= 353,

    NTPRINT		= 400
};
   
typedef struct Node {
	enum NodeType type;
	union { 
		double val;
		char* var;
		struct Node** children;
	} ;
} Node;

Node* createNode(int type);

Node* nodeChildren(Node* father, Node *child1, Node *child2);

const char* node2String(Node *node);

void printGraph(Node *root);

#endif

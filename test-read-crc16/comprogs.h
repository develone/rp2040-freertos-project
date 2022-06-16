static void echo_key(char c);
static void parse_cmd(void);
char* full_path(const char* name);
static void xmodem_cb(uint8_t* buf, uint32_t len);
static bool check_mount(bool need);
static bool check_name(void);
static void put_cmd(void);
int check_cp_parms(char** from, char** to, int copy);
static void mv_cmd(void);
static void cp_cmd(void);
static void get_cmd(void);

#define imgsize 4096
//#define imgsize 512
struct PTRs
{
  /*This is the buffer for inp & output
     2048 x 2048 = 4194304
     256 x 256 = 65536
     64 x 64 = 4096
   */
  short int inpbuf[imgsize * 2];
  short int *inp_buf;
  short int *out_buf;
  short int flag;
  short int w;
  short int h;
  short int *fwd_inv;
  short int fwd;
  short int *red;
  char *head;
  char *tail;
  char *topofbuf;
  char *endofbuf;
} ptrs;

unsigned char *img1, *img2;
int ncols, nrows, i;
unsigned char tt[128];
const char src[] = "Hello, world! ";
const short int a[];
int nFeatures = 3;
KLT_TrackingContext tc;
KLT_FeatureList fl;
//const unsigned char CRC7_POLY = 0x91;
unsigned char CRCTable[256];


static size_t f_get_len(FILE* fptr);

static int16_t f_fetch_sample(FILE* fptr);

static void bufndif(FILE* fptr,size_t len, int16_t* buf);

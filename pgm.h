struct pgmImage{
	int tipo; //P2 or P5
	int c; //column
	int r; //row
	int mv; // max value
	int *pData; //pixels
};

void readPGMImg(struct pgm *, char *);
void writePGMImg(struct pgm *, char *);
void viewPGMImg(struct pgm *);
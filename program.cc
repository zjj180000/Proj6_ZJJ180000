#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include "cdk.h"
#include <stdint.h>
#include <sstream>
#include "program.h"

#define MATRIX_HEIGHT 5
#define MATRIX_WIDTH 3
#define BOX_WIDTH 21
#define MATRIX_NAME "Matrix"

using namespace std;

class BinaryFileHeader
{  
public:   
  uint32_t magicNumber;         /* Should be 0xFEEDFACE */    
  uint32_t versionNumber;   
  uint64_t numRecords;
}; 

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


int main()
{
  string filename = "/scratch/perkins/cs3377.bin";
  BinaryFileHeader* myHeader = new BinaryFileHeader;
  memset(myHeader, 0, sizeof(BinaryFileHeader));

  ifstream in (filename, ios::in | ios::binary);  
  in.read((char *) myHeader, sizeof(BinaryFileHeader));
  
  ostringstream out;

  out << std::hex << std::uppercase << myHeader->magicNumber;
  string magic = out.str();

  out.str("");
  out.clear();

  out << std::dec << myHeader->versionNumber;
  string version = out.str();

  out.str("");
  out.clear();
  
  int num = myHeader->numRecords;
  out << num;
  string records = out.str();
  
  out.str("");
  out.clear();

  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *matrix;  
  
  const char *rowTitles[MATRIX_HEIGHT+1] = {"0", "a", "b", "c", "d", "e"};
  const char *columnTitles[MATRIX_WIDTH+1] = {"0", "a", "b", "c"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  matrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_NAME, (char **) rowTitles, (char **) columnTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

  if(matrix == NULL)
    {
      cout << "error creating matrix" << endl;
      _exit(1);
    }

  drawCDKMatrix(matrix, true);

  magic = "Magic: 0x" + magic;
  version = "Version: " + version;
  records = "NumRecords: " + records;

  setCDKMatrixCell(matrix, 1, 1, magic.c_str());
  setCDKMatrixCell(matrix, 1, 2, version.c_str());
  setCDKMatrixCell(matrix, 1, 3, records.c_str());

  for(int i = 2; i <= MATRIX_HEIGHT; i++)
    {
      BinaryFileRecord *myRecord = new BinaryFileRecord();
      in.read((char *) myRecord, sizeof(BinaryFileRecord));

      int leng = myRecord->strLength;
      string len = "strlen: " + intToString(leng);

      out.str("");
      out.clear();

      out << myRecord->stringBuffer;
      string word = out.str();

      out.str("");
      out.clear();
      
      setCDKMatrixCell(matrix, i, 1, len.c_str());
      setCDKMatrixCell(matrix, i, 2, word.c_str());

      delete myRecord;
    }

  in.close();

  drawCDKMatrix(matrix, true);

  char holder;
  cin >> holder;

  endCDK();
}

/*
 ----------------------------------------------------------
|
| Software Name :HEC-MW Ver 4.0beta
|
|   ../src/FileReaderMaterial.h
|
|                     Written by T.Takeda,    2011/06/01
|                                Y.Sato       2011/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "FileReader.h"
#include "MatrialPropType.h"
#include "FileReaderBinCheck.h" 
namespace FileIO{
#ifndef _FILEREADERMATERIAL_H_
#define	_FILEREADERMATERIAL_H_
class CFileReaderMaterial:public CFileReader{
public:
    CFileReaderMaterial();
    virtual ~CFileReaderMaterial();
public:
    virtual bool Read(ifstream& ifs, string& sline);
    virtual bool Read_bin(ifstream& ifs);
};
#endif	/* _FILEREADERMATERIAL_H */
}
